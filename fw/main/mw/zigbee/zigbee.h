#ifndef MAIN_MW_ZIGBEE_ZIGBEE
#define MAIN_MW_ZIGBEE_ZIGBEE

#include <stdbool.h>
#include <stdint.h>

typedef enum {
  ZIGBEE_TZ_NONE = 0x00,
  ZIGBEE_TZ_FAN_SPEED,
  ZIGBEE_TZ_PM10,
  ZIGBEE_TZ_PM2_5,
  ZIGBEE_TZ_TEMPERATURE,
  ZIGBEE_TZ_HUMIDITY,
} zigbee_tz_data_flag_t;

typedef union {
  uint16_t fan_speed; // ZIGBEE_TZ_FAN_SPEED
  uint16_t pm10;      // ZIGBEE_TZ_PM10
  uint16_t pm2_5;     // ZIGBEE_TZ_PM2_5
  float temperature;  // ZIGBEE_TZ_TEMPERATURE
  float humidity;     // ZIGBEE_TZ_HUMIDITY
} zigbee_tz_data_t;

typedef enum {
  ZIGBEE_FZ_NONE = 0x00,
  ZIGBEE_FZ_FAN_MODE,
} zigbee_fz_data_flag_t;

typedef union {
  enum fan_mode_t {
    FAN_MODE_OFF = 0x00,
    FAN_MODE_LOW = 0x01,
    FAN_MODE_MEDIUM = 0x02,
    FAN_MODE_HIGH = 0x03,
    FAN_MODE_ON = 0x04,
    FAN_MODE_AUTO = 0x05,
    FAN_MODE_SMART = 0x06,
    FAN_MODE_RESERVED = 0x07,
  } fan_mode; // ZIGBEE_FZ_FAN_MODE
} zigbee_fz_data_t;

typedef void (*zigbee_fz_callback_t)(zigbee_fz_data_flag_t data_flag, zigbee_fz_data_t *data);

bool zigbee_init_(void);

void zigbee_reset(void);

void zigbee_fz_set_callback(zigbee_fz_callback_t handler);
bool zigbee_tz_set(zigbee_tz_data_flag_t data_flag, zigbee_tz_data_t data);

#endif /* MAIN_MW_ZIGBEE_ZIGBEE */
