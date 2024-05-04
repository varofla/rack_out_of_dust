#include <zephyr/kernel.h>

#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#include "zbrstbtn.h"

LOG_MODULE_REGISTER(zbrstbtn, LOG_LEVEL_INF);

static const struct gpio_dt_spec s_reset_button_dt = GPIO_DT_SPEC_GET(DT_ALIAS(btn), gpios);

typedef struct {
  struct k_timer reset_button_timeout_timer;
  struct gpio_callback reset_button_cb_data;
  uint8_t reset_button_click_cnt;
  uint32_t reset_button_clicked_cycle;

  zbrstbtn_callback_t handler;
} module_data_t;
static module_data_t module_data;

static void s_reset_button_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
  k_timer_start(&module_data.reset_button_timeout_timer, K_MSEC(500), K_NO_WAIT);
  if ((double)(k_cycle_get_32() - module_data.reset_button_clicked_cycle) / sys_clock_hw_cycles_per_sec() < 0.1) {
    module_data.reset_button_clicked_cycle = k_cycle_get_32();
    return;
  }
  module_data.reset_button_clicked_cycle = k_cycle_get_32();
  module_data.reset_button_click_cnt++;
}

static void s_reset_button_timeout_callback(struct k_timer *timer_id) {
  if (module_data.handler != 0) {
    module_data.handler(module_data.reset_button_click_cnt);
  }

  module_data.reset_button_click_cnt = 0;
}

bool zbrstbtn_init(void) {
  k_timer_init(&module_data.reset_button_timeout_timer, s_reset_button_timeout_callback, NULL);

  gpio_pin_interrupt_configure_dt(&s_reset_button_dt, GPIO_INT_EDGE_TO_ACTIVE);
  gpio_init_callback(&module_data.reset_button_cb_data, s_reset_button_callback, BIT(s_reset_button_dt.pin));
  gpio_add_callback_dt(&s_reset_button_dt, &module_data.reset_button_cb_data);

  return true;
}

void zbrstbtn_set_callback(zbrstbtn_callback_t handler) {
  module_data.handler = handler;
}
