#include <stdint.h>

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "zigbee_fz_handler.h"

#include "fan4p/fan4p.h"
#include "stled/stled.h"

#include "zigbee.h"

LOG_MODULE_REGISTER(zigbee_fz_handler, LOG_LEVEL_INF);

#define FAN_SPEED_LOW 33
#define FAN_SPEED_MEDIUM 66
#define FAN_SPEED_HIGH 100

typedef struct {
  struct k_work work;

  uint16_t fan_speed;
  bool is_fan_on;
} module_data_t;
static module_data_t module_data;

static void s_flash_led_work_hd(struct k_work *) {
  stled_set(STLED_PATTERN_OFF);
  k_msleep(100);
  stled_set(STLED_PATTERN_ON);
  k_msleep(50);
  stled_set(STLED_PATTERN_OFF);
}

static void s_fz_hd(zigbee_fz_data_flag_t data_flag, zigbee_fz_data_t *data) {
  k_work_submit(&module_data.work);
  switch (data->fan_mode) {
  case FAN_MODE_OFF:
    module_data.is_fan_on = false;
    break;

  case FAN_MODE_LOW:
    module_data.is_fan_on = true;
    module_data.fan_speed = FAN_SPEED_LOW;
    break;

  case FAN_MODE_MEDIUM:
    module_data.is_fan_on = true;
    module_data.fan_speed = FAN_SPEED_MEDIUM;
    break;

  case FAN_MODE_HIGH:
    module_data.is_fan_on = true;
    module_data.fan_speed = FAN_SPEED_HIGH;
    break;

  case FAN_MODE_ON:
    module_data.is_fan_on = true;
    break;

  default:
    break;
  }

  if (module_data.is_fan_on) {
    fan4p_set_power(module_data.fan_speed);
  } else {
    fan4p_set_power(0);
  }
}

bool zigbee_fz_handler_init(void) {
  k_work_init(&module_data.work, s_flash_led_work_hd);

  zigbee_fz_set_callback(s_fz_hd);
  return true;
}
