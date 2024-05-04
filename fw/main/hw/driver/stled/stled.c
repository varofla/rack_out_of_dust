#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "stled.h"

LOG_MODULE_REGISTER(stled, LOG_LEVEL_INF);

typedef struct {
  bool is_init;

  k_tid_t thread_id;
  struct k_thread thread_data;

  stled_pattern_t current_pattern;

  bool is_brightness_increasing;
  uint16_t last_brightness;
} module_data_t;
static module_data_t module_data;

static const struct pwm_dt_spec s_stled_dt = PWM_DT_SPEC_GET(DT_ALIAS(stled));

K_THREAD_STACK_DEFINE(s_stled_stack_area, 300);

#define PWM_PERIOD_25KHZ PWM_KHZ(25) // fan4p와 같은 pwm0을 사용하기 때문에 주파수 맞춰줌

#define DELAY_SLOW_US 1500
#define DELAY_MEDIUM_US 500
#define DELAY_FAST_US 100

/**
 * @brief 밝기 설정
 *
 * @param power 밝기 (0~1000)
 */
void s_set_brightness(uint16_t power) {
  uint32_t speed = (PWM_PERIOD_25KHZ * power) / 1000;
  speed = speed > PWM_PERIOD_25KHZ ? PWM_PERIOD_25KHZ : speed;

  pwm_set_pulse_dt(&s_stled_dt, speed);
}

static void s_change_brightness_target(void) {
  if (module_data.last_brightness == 1000) {
    module_data.is_brightness_increasing = false;
  } else if (module_data.last_brightness == 0) {
    module_data.is_brightness_increasing = true;
  }

  switch (module_data.current_pattern) {
  case STLED_PATTERN_BLINK_SLOW:
  case STLED_PATTERN_BLINK_MEDIUM:
  case STLED_PATTERN_BLINK_FAST:
    module_data.last_brightness = module_data.is_brightness_increasing ? 1000 : 0;
    break;

  case STLED_PATTERN_BREATH_SLOW:
  case STLED_PATTERN_BREATH_MEDIUM:
  case STLED_PATTERN_BREATH_FAST:
    module_data.last_brightness += module_data.is_brightness_increasing ? 1 : -1;
    break;

  default:
    break;
  }

  s_set_brightness(module_data.last_brightness);
}

static void s_thread_sleep(void) {
  switch (module_data.current_pattern) {
  case STLED_PATTERN_BLINK_SLOW:
    k_usleep(DELAY_SLOW_US * 2000);
    break;
  case STLED_PATTERN_BLINK_MEDIUM:
    k_usleep(DELAY_MEDIUM_US * 2000);
    break;
  case STLED_PATTERN_BLINK_FAST:
    k_usleep(DELAY_FAST_US * 2000);
    break;

  case STLED_PATTERN_BREATH_SLOW:
    k_usleep(DELAY_SLOW_US);
    break;
  case STLED_PATTERN_BREATH_MEDIUM:
    k_usleep(DELAY_MEDIUM_US);
    break;
  case STLED_PATTERN_BREATH_FAST:
    k_usleep(DELAY_FAST_US);
    break;

  default:
    break;
  }
}

static void s_stled_thread(void *, void *, void *) {
  for (;;) {
    s_change_brightness_target();

    s_thread_sleep();
  }
}

bool stled_init(void) {
  if (!pwm_is_ready_dt(&s_stled_dt)) {
    LOG_ERR("Error: PWM device %s is not ready", s_stled_dt.dev->name);
    return false;
  }

  pwm_set_dt(&s_stled_dt, PWM_PERIOD_25KHZ, 0);

  stled_set(STLED_PATTERN_OFF);

  module_data.is_init = true;

  return true;
}

/**
 * @brief 심신삐약상태에서 작성함. 문제 있을수도 있음. 아니 문제있을듯;;;
 *
 * @param pattern
 * @return true
 * @return false
 */
bool stled_set(stled_pattern_t pattern) {
  if (!module_data.is_init) {
    return false;
  }

  module_data.current_pattern = pattern;
  if (pattern == STLED_PATTERN_ON ||
      pattern == STLED_PATTERN_OFF) {
    if (module_data.thread_id != 0) {
      k_thread_abort(module_data.thread_id);
      module_data.thread_id = 0;
    }
    s_set_brightness(pattern ? 1000 : 0);
  } else if (module_data.thread_id == 0) {
    module_data.thread_id = k_thread_create(&module_data.thread_data, s_stled_stack_area,
                                            K_THREAD_STACK_SIZEOF(s_stled_stack_area),
                                            s_stled_thread,
                                            NULL, NULL, NULL,
                                            5, 0, K_NO_WAIT);
  }

  return true;
}
