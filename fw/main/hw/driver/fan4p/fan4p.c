#include <zephyr/kernel.h>

#include <zephyr/device.h>

#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>

#include <zephyr/sys/printk.h>

#include "fan4p.h"

#define PWM_PERIOD_25KHZ PWM_KHZ(25)
#define SPEED_FEEDBACK_TIMEOUT_SEC 1

typedef struct {
  struct k_timer feedback_timeout_timer;

  struct gpio_callback feedback_gpio_cb_data;
  uint32_t feedback_last_tick;

  uint16_t rpm;

} module_data_t;
static module_data_t module_data;

#define ZEPHYR_USER_NODE DT_PATH(zephyr_user)
static const struct gpio_dt_spec s_speed_feedback_gpio_dt = GPIO_DT_SPEC_GET(ZEPHYR_USER_NODE, fan4p_speed_feedback_gpios);
static const struct pwm_dt_spec s_pwm_dt = PWM_DT_SPEC_GET(DT_PATH(zephyr_user));

// TODO: PWM capture 에라이 왜 이제봤지
// https://docs.zephyrproject.org/latest/hardware/peripherals/pwm.html#c.pwm_enable_capture
static void s_speed_feedback_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
  uint32_t curr_tick = k_cycle_get_32();
  double period = (double)(curr_tick - module_data.feedback_last_tick) / sys_clock_hw_cycles_per_sec();
  module_data.feedback_last_tick = curr_tick;

  module_data.rpm = (1 / period) / 2 * 60;
}

void s_speed_timeout_timer_function(struct k_timer *timer_id) {
  if ((k_cycle_get_32() - module_data.feedback_last_tick) / sys_clock_hw_cycles_per_sec() >= SPEED_FEEDBACK_TIMEOUT_SEC) {
    module_data.rpm = 0;
  }
}

bool fan4p_init(void) {
  bool ret = true;

  k_timer_init(&module_data.feedback_timeout_timer, s_speed_timeout_timer_function, NULL);
  k_timer_start(&module_data.feedback_timeout_timer, K_SECONDS(1), K_SECONDS(1));

  ret &= gpio_pin_interrupt_configure_dt(&s_speed_feedback_gpio_dt, GPIO_INT_EDGE_TO_ACTIVE) == 0;
  gpio_init_callback(&module_data.feedback_gpio_cb_data, s_speed_feedback_callback, BIT(s_speed_feedback_gpio_dt.pin));
  ret &= gpio_add_callback_dt(&s_speed_feedback_gpio_dt, &module_data.feedback_gpio_cb_data) == 0;

  ret &= fan4p_set_power(0) == true;

  if (ret != true) {
    printk("fan4p init error!!");
  }

  return ret;
}

/**
 * @brief 속도 설정
 *
 * @param power 0~100
 * @return true
 * @return false
 */
bool fan4p_set_power(uint8_t power) {
  uint32_t speed = (PWM_PERIOD_25KHZ * power) / 100;
  speed = speed > PWM_PERIOD_25KHZ ? PWM_PERIOD_25KHZ : speed;

  return pwm_set_pulse_dt(&s_pwm_dt, speed) == 0;
}

/**
 * @brief 속도 출력
 *
 * @return uint16_t
 */
uint16_t fan4p_get_rpm(void) {
  return module_data.rpm;
}
