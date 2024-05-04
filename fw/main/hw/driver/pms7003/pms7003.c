#include "pms7003.h"

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/rtio/rtio.h>

const struct device *const s_pms7003_dt = DEVICE_DT_GET_ONE(plantower_pms7003);

LOG_MODULE_REGISTER(pms7003, LOG_LEVEL_INF);

bool pms7003_init(void) {
  if (!device_is_ready(s_pms7003_dt)) {
    LOG_ERR("Device %s is not ready\n", s_pms7003_dt->name);
    return false;
  }
  return true;
}

/**
 * @brief 미세먼지 센서 데이터 취득
 *
 * @note blocking!!
 *
 * @param data_buff
 * @return pms7003_data_t*
 */
pms7003_data_t *pms7003_get(pms7003_data_t *data_buff) {
  if (data_buff == NULL) {
    return NULL;
  }
  struct sensor_value pm_1_0;
  struct sensor_value pm_2_5;
  struct sensor_value pm_10;

  int ret = sensor_sample_fetch(s_pms7003_dt);
  if (ret == 0) {
    ret = sensor_channel_get(s_pms7003_dt, SENSOR_CHAN_PM_1_0, &pm_1_0);
  }
  if (ret == 0) {
    ret = sensor_channel_get(s_pms7003_dt, SENSOR_CHAN_PM_2_5, &pm_2_5);
  }
  if (ret == 0) {
    ret = sensor_channel_get(s_pms7003_dt, SENSOR_CHAN_PM_10, &pm_10);
  }
  if (ret == 0) {
    LOG_DBG("pm10: %d \t pm2.5: %d \t pm1.0: %d", pm_10.val1, pm_2_5.val1, pm_1_0.val1);
    data_buff->pm_10 = pm_10.val1;
    data_buff->pm_2_5 = pm_2_5.val1;
    data_buff->pm_1_0 = pm_1_0.val1;
  } else {
    LOG_ERR("sample fetch/get failed: %d\n", ret);
  }

  return data_buff;
}