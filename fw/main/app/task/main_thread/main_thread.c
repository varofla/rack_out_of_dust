#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "am2320/am2320.h"
#include "fan4p/fan4p.h"
#include "pms7003/pms7003.h"
#include "stled/stled.h"

#include "zigbee.h"

LOG_MODULE_REGISTER(main_thread, LOG_LEVEL_WRN);

K_THREAD_STACK_DEFINE(main_thread_stack_area, 800);
struct k_thread main_thread_data;

typedef struct {
  zigbee_tz_data_t tz_data;

  struct sht_data_t {
    float temperature;
    float humidity;
  } sht_data;
  pms7003_data_t pms_data;
} thread_data_t;

static void s_main_thread(void *, void *, void *) {
  LOG_INF("main thread started");

  thread_data_t data = {0};
  for (;;) {
    am2320_read(&data.sht_data.temperature, &data.sht_data.humidity);
    data.tz_data.temperature = data.sht_data.temperature;
    LOG_INF("temperature: %f", data.sht_data.temperature);
    zigbee_tz_set(ZIGBEE_TZ_TEMPERATURE, data.tz_data);
    data.tz_data.humidity = data.sht_data.humidity;
    LOG_INF("humidity: %f", data.tz_data.humidity);
    zigbee_tz_set(ZIGBEE_TZ_HUMIDITY, data.tz_data);

    data.tz_data.fan_speed = fan4p_get_rpm();
    LOG_INF("fan speed: %u", data.tz_data.fan_speed);
    zigbee_tz_set(ZIGBEE_TZ_FAN_SPEED, data.tz_data);

  reread:
    pms7003_get(&data.pms_data);
    data.tz_data.pm10 = data.pms_data.pm_10;

    if (data.pms_data.pm_10 > 500 || data.pms_data.pm_10 > 500) { // 왜 데이터가 이상하지..?
      k_msleep(100);
      goto reread;
    }
    LOG_INF("pm10: %u", data.tz_data.pm10);
    zigbee_tz_set(ZIGBEE_TZ_PM10, data.tz_data);
    data.tz_data.pm2_5 = data.pms_data.pm_2_5;
    LOG_INF("pm2.5: %u", data.tz_data.pm2_5);
    zigbee_tz_set(ZIGBEE_TZ_PM2_5, data.tz_data);

    k_msleep(5000); // 센서 데이터 5초마다 업데이트
  }
}

bool main_thread_init(void) {
  k_thread_create(&main_thread_data, main_thread_stack_area,
                  K_THREAD_STACK_SIZEOF(main_thread_stack_area),
                  s_main_thread,
                  NULL, NULL, NULL,
                  5, 0, K_NO_WAIT);

  return true;
}
