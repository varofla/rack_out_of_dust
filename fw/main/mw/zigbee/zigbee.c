#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
#include <zephyr/settings/settings.h>

#include <zb_mem_config_med.h>
#include <zb_nrf_platform.h>
#include <zboss_api.h>
#include <zboss_api_addons.h>
#include <zigbee/zigbee_app_utils.h>
#include <zigbee/zigbee_error_handler.h>
#include <zigbee/zigbee_zcl_scenes.h>

#include "zcl/zb_zcl_fan_control_addons.h"
#include "zcl/zb_zcl_multistate_output_addons.h"
#include "zcl/zb_zcl_pm10_measurement_addons.h"
#include "zcl/zb_zcl_pm2_5_measurement_addons.h"
#include "zcl/zb_zcl_rel_humidity_measurement_addons.h"

#include "zcl/zb_zcl_multistate_output.h"
#include "zcl/zb_zcl_pm10_measurement.h"
#include "zcl/zb_zcl_pm2_5_measurement.h"

#include "zigbee_cfg.h"

#include "zigbee.h"

LOG_MODULE_REGISTER(zigbee, LOG_LEVEL_INF);

typedef struct {
  // zigbee attr
  zb_zcl_basic_attrs_ext_t basic_attr;
  zb_zcl_identify_attrs_t identify_attr;
  zb_zcl_scenes_attrs_t scenes_attr;
  zb_zcl_groups_attrs_t groups_attr;

  zb_zcl_fan_control_attrs_t fan_control_attr;
  zb_zcl_multistate_output_attrs_t multistate_output_attr; // fan speed
  zb_zcl_pm10_measurement_attrs_t pm10_measurement_attr;
  zb_zcl_pm2_5_measurement_attrs_t pm2_5_measurement_attr;
  zb_zcl_temp_measurement_attrs_t temp_measurement_attr;
  zb_zcl_rel_humidity_measurement_attrs_t rel_humidity_measurement_attr;

  zigbee_fz_callback_t fz_handler;
} module_data_t;
static module_data_t module_data;

ZB_ZCL_DECLARE_IDENTIFY_ATTRIB_LIST(
    identify_attr_list,
    &module_data.identify_attr.identify_time);

ZB_ZCL_DECLARE_GROUPS_ATTRIB_LIST(
    groups_attr_list,
    &module_data.groups_attr.name_support);

ZB_ZCL_DECLARE_SCENES_ATTRIB_LIST(
    scenes_attr_list,
    &module_data.scenes_attr.scene_count,
    &module_data.scenes_attr.current_scene,
    &module_data.scenes_attr.current_group,
    &module_data.scenes_attr.scene_valid,
    &module_data.scenes_attr.name_support);

ZB_ZCL_DECLARE_BASIC_ATTRIB_LIST_EXT(
    basic_attr_list,
    &module_data.basic_attr.zcl_version,
    &module_data.basic_attr.app_version,
    &module_data.basic_attr.stack_version,
    &module_data.basic_attr.hw_version,
    module_data.basic_attr.mf_name,
    module_data.basic_attr.model_id,
    module_data.basic_attr.date_code,
    &module_data.basic_attr.power_source,
    module_data.basic_attr.location_id,
    &module_data.basic_attr.ph_env,
    module_data.basic_attr.sw_ver);

ZB_ZCL_DECLARE_FAN_CONTROL_ATTRIB_LIST(
    fan_control_attr_list,
    &module_data.fan_control_attr.fan_mode,
    &module_data.fan_control_attr.fan_mode_sequence);

ZB_ZCL_DECLARE_MULTISTATE_OUTPUT_ATTRIB_LIST(
    multistate_output_attr_list,
    &module_data.multistate_output_attr.number_of_states,
    &module_data.multistate_output_attr.out_of_service,
    &module_data.multistate_output_attr.present_value,
    &module_data.multistate_output_attr.status_flags);

ZB_ZCL_DECLARE_PM10_MEASUREMENT_ATTRIB_LIST(
    pm10_measurement_attr_list,
    &module_data.pm10_measurement_attr.measured_value);

ZB_ZCL_DECLARE_PM2_5_MEASUREMENT_ATTRIB_LIST(
    pm2_5_measurement_attr_list,
    &module_data.pm2_5_measurement_attr.measured_value,
    &module_data.pm2_5_measurement_attr.min_measured_value,
    &module_data.pm2_5_measurement_attr.max_measured_value,
    &module_data.pm2_5_measurement_attr.tolerance);

ZB_ZCL_DECLARE_TEMP_MEASUREMENT_ATTRIB_LIST(
    temp_measurement_attr_list,
    &module_data.temp_measurement_attr.measure_value,
    &module_data.temp_measurement_attr.min_measure_value,
    &module_data.temp_measurement_attr.max_measure_value,
    &module_data.temp_measurement_attr.tolerance);

ZB_ZCL_DECLARE_REL_HUMIDITY_MEASUREMENT_ATTRIB_LIST(
    rel_humidity_measurement_attr_list,
    &module_data.rel_humidity_measurement_attr.measure_value,
    &module_data.rel_humidity_measurement_attr.min_measure_value,
    &module_data.rel_humidity_measurement_attr.max_measure_value);

ZB_DECLARE_CLUSTER_LIST(
    zigbee_clusters,
    basic_attr_list,
    identify_attr_list,
    groups_attr_list,
    scenes_attr_list,
    fan_control_attr_list,
    multistate_output_attr_list,
    pm10_measurement_attr_list,
    pm2_5_measurement_attr_list,
    temp_measurement_attr_list,
    rel_humidity_measurement_attr_list);

ZB_DECLARE_EP(
    zigbee_ep,
    ZIGBEE_ENDPOINT,
    zigbee_clusters);

ZBOSS_DECLARE_DEVICE_CTX_1_EP(
    zigbee_ctx,
    zigbee_ep);

/**
 * @brief Zigbee stack event handler.
 *
 * @param[in]   bufid   Reference to the Zigbee stack buffer
 *                      used to pass signal.
 */
void zboss_signal_handler(zb_bufid_t bufid) {
  /* No application-specific behavior is required.
   * Call default signal handler.
   */
  ZB_ERROR_CHECK(zigbee_default_signal_handler(bufid));

  /* All callbacks should either reuse or free passed buffers.
   * If bufid == 0, the buffer is invalid (not passed).
   */
  if (bufid) {
    zb_buf_free(bufid);
  }
}

static bool s_fan_control_handler(zb_zcl_set_attr_value_param_t *set_attr_param_data,
                                  zigbee_fz_data_flag_t *data_flag, zigbee_fz_data_t *data) {

  switch (set_attr_param_data->attr_id) {
  case ZB_ZCL_ATTR_FAN_CONTROL_FAN_MODE_ID:
    *data_flag = ZIGBEE_FZ_FAN_MODE;
    data->fan_mode = set_attr_param_data->values.data8;
    break;

  default:
    return false;
  }

  return true;
}

static void s_zcl_device_cb(zb_bufid_t bufid) {
  zb_zcl_device_callback_param_t *device_cb_param = ZB_BUF_GET_PARAM(bufid, zb_zcl_device_callback_param_t);

  /* Set default response value. */
  device_cb_param->status = RET_OK;

  bool ret = false;
  zigbee_fz_data_flag_t data_flag;
  zigbee_fz_data_t data;

  if (device_cb_param->device_cb_id == ZB_ZCL_SET_ATTR_VALUE_CB_ID) {
    zb_zcl_set_attr_value_param_t *set_attr_param_data = &(device_cb_param->cb_param.set_attr_value_param);

    switch (set_attr_param_data->cluster_id) {
    case ZB_ZCL_CLUSTER_ID_FAN_CONTROL:
      ret = s_fan_control_handler(set_attr_param_data, &data_flag, &data);
      break;

    default:
      LOG_INF("unexpected cluster id = 0x%x, attr id = 0x%x", set_attr_param_data->cluster_id, set_attr_param_data->attr_id);
      break;
    }
  }

  if (ret == true && module_data.fz_handler != 0) {
    module_data.fz_handler(data_flag, &data);
  }
}

static void clusters_attr_init(void) {
  /* Basic cluster attributes data */
  module_data.basic_attr.zcl_version = ZB_ZCL_VERSION;
  module_data.basic_attr.app_version = ZIGBEE_INIT_BASIC_APP_VERSION;
  module_data.basic_attr.stack_version = ZIGBEE_INIT_BASIC_STACK_VERSION;
  module_data.basic_attr.hw_version = ZIGBEE_INIT_BASIC_HW_VERSION;

  ZB_ZCL_SET_STRING_VAL(
      module_data.basic_attr.mf_name,
      ZIGBEE_INIT_BASIC_MANUF_NAME,
      ZB_ZCL_STRING_CONST_SIZE(ZIGBEE_INIT_BASIC_MANUF_NAME));

  ZB_ZCL_SET_STRING_VAL(
      module_data.basic_attr.model_id,
      ZIGBEE_INIT_BASIC_MODEL_ID,
      ZB_ZCL_STRING_CONST_SIZE(ZIGBEE_INIT_BASIC_MODEL_ID));

  ZB_ZCL_SET_STRING_VAL(
      module_data.basic_attr.date_code,
      ZIGBEE_INIT_BASIC_DATE_CODE,
      ZB_ZCL_STRING_CONST_SIZE(ZIGBEE_INIT_BASIC_DATE_CODE));

  module_data.basic_attr.power_source = ZIGBEE_INIT_BASIC_POWER_SOURCE;

  ZB_ZCL_SET_STRING_VAL(
      module_data.basic_attr.location_id,
      ZIGBEE_INIT_BASIC_LOCATION_DESC,
      ZB_ZCL_STRING_CONST_SIZE(ZIGBEE_INIT_BASIC_LOCATION_DESC));

  module_data.basic_attr.ph_env = ZIGBEE_INIT_BASIC_PH_ENV;

  /* Identify cluster attributes data. */
  module_data.identify_attr.identify_time =
      ZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE;

  module_data.fan_control_attr.fan_mode = ZB_ZCL_FAN_CONTROL_FAN_MODE_OFF;
  module_data.fan_control_attr.fan_mode_sequence = ZB_ZCL_FAN_CONTROL_FAN_MODE_SEQUENCE_LOW_MED_HIGH_AUTO;

  module_data.multistate_output_attr.number_of_states = 1;
  module_data.multistate_output_attr.out_of_service = ZB_FALSE;
  module_data.multistate_output_attr.present_value = 0;
  module_data.multistate_output_attr.status_flags = 0;

  module_data.pm10_measurement_attr.measured_value = 0;

  module_data.pm2_5_measurement_attr.measured_value = 0;
  module_data.pm2_5_measurement_attr.min_measured_value = 0;
  module_data.pm2_5_measurement_attr.max_measured_value = 999;
  module_data.pm2_5_measurement_attr.tolerance = 1;

  module_data.temp_measurement_attr.measure_value = 0;
  module_data.temp_measurement_attr.min_measure_value = -0xFA0; // SHT45 min offer temp = -40 -> -40 * 100
  module_data.temp_measurement_attr.max_measure_value = 0x30D4; // SHT45 max offer temp = 125 -> 125 * 100
  module_data.temp_measurement_attr.tolerance = 10;             // SHT45 tolerance = 0.1 -> 0.1 * 100

  module_data.rel_humidity_measurement_attr.measure_value = 0;
  module_data.rel_humidity_measurement_attr.min_measure_value = 0;
  module_data.rel_humidity_measurement_attr.max_measure_value = 0x2710; // 100 % -> 100 * 100

  ZB_ZCL_SET_ATTRIBUTE(
      ZIGBEE_ENDPOINT,
      ZB_ZCL_CLUSTER_ID_FAN_CONTROL,
      ZB_ZCL_CLUSTER_SERVER_ROLE,
      ZB_ZCL_ATTR_FAN_CONTROL_FAN_MODE_ID,
      (zb_uint8_t *)&module_data.fan_control_attr.fan_mode,
      ZB_FALSE);
  ZB_ZCL_SET_ATTRIBUTE(
      ZIGBEE_ENDPOINT,
      ZB_ZCL_CLUSTER_ID_FAN_CONTROL,
      ZB_ZCL_CLUSTER_SERVER_ROLE,
      ZB_ZCL_ATTR_FAN_CONTROL_FAN_MODE_SEQUENCE_ID,
      (zb_uint8_t *)&module_data.fan_control_attr.fan_mode_sequence,
      ZB_FALSE);

  ZB_ZCL_SET_ATTRIBUTE(
      ZIGBEE_ENDPOINT,
      ZB_ZCL_CLUSTER_ID_PM10_MEASUREMENT,
      ZB_ZCL_CLUSTER_SERVER_ROLE,
      ZB_ZCL_ATTR_PM10_MEASUREMENT_MEASURED_VALUE_ID,
      (zb_uint8_t *)&module_data.pm10_measurement_attr.measured_value,
      ZB_FALSE);

  ZB_ZCL_SET_ATTRIBUTE(
      ZIGBEE_ENDPOINT,
      ZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT,
      ZB_ZCL_CLUSTER_SERVER_ROLE,
      ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MEASURED_VALUE_ID,
      (zb_uint8_t *)&module_data.pm2_5_measurement_attr.measured_value,
      ZB_FALSE);
  ZB_ZCL_SET_ATTRIBUTE(
      ZIGBEE_ENDPOINT,
      ZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT,
      ZB_ZCL_CLUSTER_SERVER_ROLE,
      ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MIN_MEASURED_VALUE_ID,
      (zb_uint8_t *)&module_data.pm2_5_measurement_attr.min_measured_value,
      ZB_FALSE);
  ZB_ZCL_SET_ATTRIBUTE(
      ZIGBEE_ENDPOINT,
      ZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT,
      ZB_ZCL_CLUSTER_SERVER_ROLE,
      ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MAX_MEASURED_VALUE_ID,
      (zb_uint8_t *)&module_data.pm2_5_measurement_attr.max_measured_value,
      ZB_FALSE);
  ZB_ZCL_SET_ATTRIBUTE(
      ZIGBEE_ENDPOINT,
      ZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT,
      ZB_ZCL_CLUSTER_SERVER_ROLE,
      ZB_ZCL_ATTR_PM2_5_MEASUREMENT_TOLERANCE_ID,
      (zb_uint8_t *)&module_data.pm2_5_measurement_attr.tolerance,
      ZB_FALSE);

  ZB_ZCL_SET_ATTRIBUTE(
      ZIGBEE_ENDPOINT,
      ZB_ZCL_CLUSTER_ID_TEMP_MEASUREMENT,
      ZB_ZCL_CLUSTER_SERVER_ROLE,
      ZB_ZCL_ATTR_TEMP_MEASUREMENT_VALUE_ID,
      (zb_uint8_t *)&module_data.temp_measurement_attr.measure_value,
      ZB_FALSE);
  ZB_ZCL_SET_ATTRIBUTE(
      ZIGBEE_ENDPOINT,
      ZB_ZCL_CLUSTER_ID_TEMP_MEASUREMENT,
      ZB_ZCL_CLUSTER_SERVER_ROLE,
      ZB_ZCL_ATTR_TEMP_MEASUREMENT_MIN_VALUE_ID,
      (zb_uint8_t *)&module_data.temp_measurement_attr.min_measure_value,
      ZB_FALSE);
  ZB_ZCL_SET_ATTRIBUTE(
      ZIGBEE_ENDPOINT,
      ZB_ZCL_CLUSTER_ID_TEMP_MEASUREMENT,
      ZB_ZCL_CLUSTER_SERVER_ROLE,
      ZB_ZCL_ATTR_TEMP_MEASUREMENT_MAX_VALUE_ID,
      (zb_uint8_t *)&module_data.temp_measurement_attr.max_measure_value,
      ZB_FALSE);
  ZB_ZCL_SET_ATTRIBUTE(
      ZIGBEE_ENDPOINT,
      ZB_ZCL_CLUSTER_ID_TEMP_MEASUREMENT,
      ZB_ZCL_CLUSTER_SERVER_ROLE,
      ZB_ZCL_ATTR_TEMP_MEASUREMENT_TOLERANCE_ID,
      (zb_uint8_t *)&module_data.temp_measurement_attr.tolerance,
      ZB_FALSE);

  ZB_ZCL_SET_ATTRIBUTE(
      ZIGBEE_ENDPOINT,
      ZB_ZCL_CLUSTER_ID_REL_HUMIDITY_MEASUREMENT,
      ZB_ZCL_CLUSTER_SERVER_ROLE,
      ZB_ZCL_ATTR_REL_HUMIDITY_MEASUREMENT_VALUE_ID,
      (zb_uint8_t *)&module_data.rel_humidity_measurement_attr.measure_value,
      ZB_FALSE);
  ZB_ZCL_SET_ATTRIBUTE(
      ZIGBEE_ENDPOINT,
      ZB_ZCL_CLUSTER_ID_REL_HUMIDITY_MEASUREMENT,
      ZB_ZCL_CLUSTER_SERVER_ROLE,
      ZB_ZCL_ATTR_REL_HUMIDITY_MEASUREMENT_MIN_VALUE_ID,
      (zb_uint8_t *)&module_data.rel_humidity_measurement_attr.min_measure_value,
      ZB_FALSE);
  ZB_ZCL_SET_ATTRIBUTE(
      ZIGBEE_ENDPOINT,
      ZB_ZCL_CLUSTER_ID_REL_HUMIDITY_MEASUREMENT,
      ZB_ZCL_CLUSTER_SERVER_ROLE,
      ZB_ZCL_ATTR_REL_HUMIDITY_MEASUREMENT_MAX_VALUE_ID,
      (zb_uint8_t *)&module_data.rel_humidity_measurement_attr.max_measure_value,
      ZB_FALSE);
}

bool zigbee_init_(void) {
  int err;

  err = settings_subsys_init();
  if (err) {
    LOG_ERR("settings initialization failed");
  }

  ZB_ZCL_REGISTER_DEVICE_CB(s_zcl_device_cb);
  ZB_AF_REGISTER_DEVICE_CTX(&zigbee_ctx);

  clusters_attr_init();

  zcl_scenes_init();
  err = settings_load();
  if (err) {
    LOG_ERR("settings loading failed");
  }

  zigbee_enable();

  return true;
}

void zigbee_reset(void) {
  LOG_INF("zigbee reset");
  zb_bdb_reset_via_local_action(0);
}

void zigbee_fz_set_callback(zigbee_fz_callback_t handler) {
  module_data.fz_handler = handler;
}

bool zigbee_tz_set(zigbee_tz_data_flag_t data_flag, zigbee_tz_data_t data) {
  switch (data_flag) {
  case ZIGBEE_TZ_FAN_SPEED:
    module_data.multistate_output_attr.present_value = data.fan_speed;
    ZB_ZCL_SET_ATTRIBUTE(
        ZIGBEE_ENDPOINT,
        ZB_ZCL_CLUSTER_ID_MULTISTATE_OUTPUT,
        ZB_ZCL_CLUSTER_SERVER_ROLE,
        ZB_ZCL_ATTR_MULTISTATE_OUTPUT_PRESENT_VALUE_ID,
        (zb_uint8_t *)&module_data.multistate_output_attr.present_value,
        ZB_FALSE);
    break;

  case ZIGBEE_TZ_PM10:
    module_data.pm10_measurement_attr.measured_value = data.pm10;
    ZB_ZCL_SET_ATTRIBUTE(
        ZIGBEE_ENDPOINT,
        ZB_ZCL_CLUSTER_ID_PM10_MEASUREMENT,
        ZB_ZCL_CLUSTER_SERVER_ROLE,
        ZB_ZCL_ATTR_PM10_MEASUREMENT_MEASURED_VALUE_ID,
        (zb_uint8_t *)&module_data.pm10_measurement_attr.measured_value,
        ZB_FALSE);
    break;

  case ZIGBEE_TZ_PM2_5:
    module_data.pm2_5_measurement_attr.measured_value = data.pm2_5;
    ZB_ZCL_SET_ATTRIBUTE(
        ZIGBEE_ENDPOINT,
        ZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT,
        ZB_ZCL_CLUSTER_SERVER_ROLE,
        ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MEASURED_VALUE_ID,
        (zb_uint8_t *)&module_data.pm2_5_measurement_attr.measured_value,
        ZB_FALSE);
    break;

  case ZIGBEE_TZ_TEMPERATURE:
    module_data.temp_measurement_attr.measure_value = data.temperature * 100.0;
    ZB_ZCL_SET_ATTRIBUTE(
        ZIGBEE_ENDPOINT,
        ZB_ZCL_CLUSTER_ID_TEMP_MEASUREMENT,
        ZB_ZCL_CLUSTER_SERVER_ROLE,
        ZB_ZCL_ATTR_TEMP_MEASUREMENT_VALUE_ID,
        (zb_uint8_t *)&module_data.temp_measurement_attr.measure_value,
        ZB_FALSE);
    break;

  case ZIGBEE_TZ_HUMIDITY:
    module_data.rel_humidity_measurement_attr.measure_value = data.humidity * 100.0;
    ZB_ZCL_SET_ATTRIBUTE(
        ZIGBEE_ENDPOINT,
        ZB_ZCL_CLUSTER_ID_REL_HUMIDITY_MEASUREMENT,
        ZB_ZCL_CLUSTER_SERVER_ROLE,
        ZB_ZCL_ATTR_REL_HUMIDITY_MEASUREMENT_VALUE_ID,
        (zb_uint8_t *)&module_data.rel_humidity_measurement_attr.measure_value,
        ZB_FALSE);
    break;

  default:
    LOG_ERR("unexpected data flag %d", data_flag);
    break;
  }

  return true;
}
