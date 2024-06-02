#include "sht4x.h"

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/rtio/rtio.h>

const struct device *const s_sht4x_dt = DEVICE_DT_GET_ONE(sensirion_sht4x);

LOG_MODULE_REGISTER(sht4x, LOG_LEVEL_INF);

bool sht4x_init(void) {
  if (!device_is_ready(s_sht4x_dt)) {
    LOG_ERR("Device %s is not ready\n", s_sht4x_dt->name);
    return false;
  }
  return true;
}

/**
 * @brief SHT4x 센서 데이터 취득
 *
 * @note blocking!!
 *
 * @param data_buff
 * @return sht4x_data_t*
 */
sht4x_data_t *sht4x_get(sht4x_data_t *data_buff) {
  if (data_buff == NULL) {
    return NULL;
  }
  struct sensor_value temp;
  struct sensor_value humi;

  int ret = sensor_sample_fetch(s_sht4x_dt);
  if (ret == 0) {
    ret = sensor_channel_get(s_sht4x_dt, SENSOR_CHAN_AMBIENT_TEMP, &temp);
  }
  if (ret == 0) {
    ret = sensor_channel_get(s_sht4x_dt, SENSOR_CHAN_HUMIDITY, &humi);
  }
  if (ret == 0) {
    data_buff->temperature = sensor_value_to_double(&temp);
    data_buff->humidity = sensor_value_to_double(&humi);
  } else {
    LOG_ERR("sample fetch/get failed: %d\n", ret);

    return NULL;
  }

  return data_buff;
}