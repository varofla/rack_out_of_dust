#ifndef MAIN_MW_ZIGBEE_ZIGBEE_CFG
#define MAIN_MW_ZIGBEE_ZIGBEE_CFG

#define ZIGBEE_ENDPOINT 1

// basic attr
#define ZIGBEE_INIT_BASIC_APP_VERSION 02
#define ZIGBEE_INIT_BASIC_STACK_VERSION 10
#define ZIGBEE_INIT_BASIC_HW_VERSION 02
#define ZIGBEE_INIT_BASIC_MANUF_NAME "VarOfLa"
#define ZIGBEE_INIT_BASIC_MODEL_ID "rack_out_of_dust_test"
#define ZIGBEE_INIT_BASIC_DATE_CODE "20240421"
#define ZIGBEE_INIT_BASIC_POWER_SOURCE ZB_ZCL_BASIC_POWER_SOURCE_DC_SOURCE
#define ZIGBEE_INIT_BASIC_LOCATION_DESC ""
#define ZIGBEE_INIT_BASIC_PH_ENV ZB_ZCL_BASIC_ENV_UNSPECIFIED

/** Device ID */
#define ZB_DEVICE_ID 0x0101

/** @cond internals_doc */

/** IN (server) clusters number */
#define ZB_IN_CLUSTER_NUM 10

/** OUT (client) clusters number */
#define ZB_OUT_CLUSTER_NUM 0

/** total (IN+OUT) cluster number */
#define ZB_CLUSTER_NUM (ZB_IN_CLUSTER_NUM + ZB_OUT_CLUSTER_NUM)

/** Number of attribute for reporting on device */
#define ZB_REPORT_ATTR_COUNT (ZB_ZCL_FAN_CONTROL_REPORT_ATTR_COUNT +       \
                              ZB_ZCL_MULTISTATE_OUTPUT_REPORT_ATTR_COUNT + \
                              ZB_ZCL_PM10_MEASUREMENT_REPORT_ATTR_COUNT +  \
                              ZB_ZCL_PM2_5_MEASUREMENT_REPORT_ATTR_COUNT + \
                              ZB_ZCL_TEMP_MEASUREMENT_REPORT_ATTR_COUNT +  \
                              ZB_ZCL_REL_HUMIDITY_MEASUREMENT_REPORT_ATTR_COUNT)

/** Continuous value change attribute count */
#define ZB_CVC_ATTR_COUNT 0

/** @endcond */ /* internals_doc */

#define ZB_DECLARE_CLUSTER_LIST(                                                    \
    cluster_list_name,                                                              \
    basic_attr_list,                                                                \
    identify_attr_list,                                                             \
    groups_attr_list,                                                               \
    scenes_attr_list,                                                               \
    fan_control_attr_list,                                                          \
    multistate_output_attr_list,                                                    \
    pm10_measurement_attr_list,                                                     \
    pm2_5_measurement_attr_list,                                                    \
    temp_measurement_attr_list,                                                     \
    rel_humidity_measurement_attr_list)                                             \
  zb_zcl_cluster_desc_t cluster_list_name[] =                                       \
      {                                                                             \
          ZB_ZCL_CLUSTER_DESC(                                                      \
              ZB_ZCL_CLUSTER_ID_IDENTIFY,                                           \
              ZB_ZCL_ARRAY_SIZE(identify_attr_list, zb_zcl_attr_t),                 \
              (identify_attr_list),                                                 \
              ZB_ZCL_CLUSTER_SERVER_ROLE,                                           \
              ZB_ZCL_MANUF_CODE_INVALID),                                           \
          ZB_ZCL_CLUSTER_DESC(                                                      \
              ZB_ZCL_CLUSTER_ID_BASIC,                                              \
              ZB_ZCL_ARRAY_SIZE(basic_attr_list, zb_zcl_attr_t),                    \
              (basic_attr_list),                                                    \
              ZB_ZCL_CLUSTER_SERVER_ROLE,                                           \
              ZB_ZCL_MANUF_CODE_INVALID),                                           \
          ZB_ZCL_CLUSTER_DESC(                                                      \
              ZB_ZCL_CLUSTER_ID_SCENES,                                             \
              ZB_ZCL_ARRAY_SIZE(scenes_attr_list, zb_zcl_attr_t),                   \
              (scenes_attr_list),                                                   \
              ZB_ZCL_CLUSTER_SERVER_ROLE,                                           \
              ZB_ZCL_MANUF_CODE_INVALID),                                           \
          ZB_ZCL_CLUSTER_DESC(                                                      \
              ZB_ZCL_CLUSTER_ID_GROUPS,                                             \
              ZB_ZCL_ARRAY_SIZE(groups_attr_list, zb_zcl_attr_t),                   \
              (groups_attr_list),                                                   \
              ZB_ZCL_CLUSTER_SERVER_ROLE,                                           \
              ZB_ZCL_MANUF_CODE_INVALID),                                           \
          ZB_ZCL_CLUSTER_DESC(                                                      \
              ZB_ZCL_CLUSTER_ID_FAN_CONTROL,                                        \
              ZB_ZCL_ARRAY_SIZE(fan_control_attr_list, zb_zcl_attr_t),              \
              (fan_control_attr_list),                                              \
              ZB_ZCL_CLUSTER_SERVER_ROLE,                                           \
              ZB_ZCL_MANUF_CODE_INVALID),                                           \
          ZB_ZCL_CLUSTER_DESC(                                                      \
              ZB_ZCL_CLUSTER_ID_MULTISTATE_OUTPUT,                                  \
              ZB_ZCL_ARRAY_SIZE(multistate_output_attr_list, zb_zcl_attr_t),        \
              (multistate_output_attr_list),                                        \
              ZB_ZCL_CLUSTER_SERVER_ROLE,                                           \
              ZB_ZCL_MANUF_CODE_INVALID),                                           \
          ZB_ZCL_CLUSTER_DESC(                                                      \
              ZB_ZCL_CLUSTER_ID_PM10_MEASUREMENT,                                   \
              ZB_ZCL_ARRAY_SIZE(pm10_measurement_attr_list, zb_zcl_attr_t),         \
              (pm10_measurement_attr_list),                                         \
              ZB_ZCL_CLUSTER_SERVER_ROLE,                                           \
              ZB_ZCL_MANUF_CODE_INVALID),                                           \
          ZB_ZCL_CLUSTER_DESC(                                                      \
              ZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT,                                  \
              ZB_ZCL_ARRAY_SIZE(pm2_5_measurement_attr_list, zb_zcl_attr_t),        \
              (pm2_5_measurement_attr_list),                                        \
              ZB_ZCL_CLUSTER_SERVER_ROLE,                                           \
              ZB_ZCL_MANUF_CODE_INVALID),                                           \
          ZB_ZCL_CLUSTER_DESC(                                                      \
              ZB_ZCL_CLUSTER_ID_TEMP_MEASUREMENT,                                   \
              ZB_ZCL_ARRAY_SIZE(temp_measurement_attr_list, zb_zcl_attr_t),         \
              (temp_measurement_attr_list),                                         \
              ZB_ZCL_CLUSTER_SERVER_ROLE,                                           \
              ZB_ZCL_MANUF_CODE_INVALID),                                           \
          ZB_ZCL_CLUSTER_DESC(                                                      \
              ZB_ZCL_CLUSTER_ID_REL_HUMIDITY_MEASUREMENT,                           \
              ZB_ZCL_ARRAY_SIZE(rel_humidity_measurement_attr_list, zb_zcl_attr_t), \
              (rel_humidity_measurement_attr_list),                                 \
              ZB_ZCL_CLUSTER_SERVER_ROLE,                                           \
              ZB_ZCL_MANUF_CODE_INVALID)}

#define ZB_ZCL_DECLARE_HA_SIMPLE_DESC(ep_name, ep_id, in_clust_num, out_clust_num) \
  ZB_DECLARE_SIMPLE_DESC(in_clust_num, out_clust_num);                             \
  ZB_AF_SIMPLE_DESC_TYPE(in_clust_num, out_clust_num)                              \
  simple_desc_##ep_name =                                                          \
      {                                                                            \
          ep_id,                                                                   \
          ZB_AF_HA_PROFILE_ID,                                                     \
          ZB_DEVICE_ID,                                                            \
          ZIGBEE_INIT_BASIC_HW_VERSION,                                            \
          0,                                                                       \
          in_clust_num,                                                            \
          out_clust_num,                                                           \
          {                                                                        \
              ZB_ZCL_CLUSTER_ID_BASIC,                                             \
              ZB_ZCL_CLUSTER_ID_IDENTIFY,                                          \
              ZB_ZCL_CLUSTER_ID_SCENES,                                            \
              ZB_ZCL_CLUSTER_ID_GROUPS,                                            \
              ZB_ZCL_CLUSTER_ID_FAN_CONTROL,                                       \
              ZB_ZCL_CLUSTER_ID_MULTISTATE_OUTPUT,                                 \
              ZB_ZCL_CLUSTER_ID_PM10_MEASUREMENT,                                  \
              ZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT,                                 \
              ZB_ZCL_CLUSTER_ID_TEMP_MEASUREMENT,                                  \
              ZB_ZCL_CLUSTER_ID_REL_HUMIDITY_MEASUREMENT,                          \
          }}

#define ZB_DECLARE_EP(ep_name, ep_id, cluster_list)                                                 \
  ZB_ZCL_DECLARE_HA_SIMPLE_DESC(ep_name, ep_id,                                                     \
                                ZB_IN_CLUSTER_NUM, ZB_OUT_CLUSTER_NUM);                             \
  ZBOSS_DEVICE_DECLARE_REPORTING_CTX(reporting_info##ep_name,                                       \
                                     ZB_REPORT_ATTR_COUNT);                                         \
  ZBOSS_DEVICE_DECLARE_LEVEL_CONTROL_CTX(cvc_alarm_info##ep_name,                                   \
                                         ZB_CVC_ATTR_COUNT);                                        \
  ZB_AF_DECLARE_ENDPOINT_DESC(ep_name, ep_id, ZB_AF_HA_PROFILE_ID,                                  \
                              0,                                                                    \
                              NULL,                                                                 \
                              ZB_ZCL_ARRAY_SIZE(cluster_list, zb_zcl_cluster_desc_t), cluster_list, \
                              (zb_af_simple_desc_1_1_t *)&simple_desc_##ep_name,                    \
                              ZB_REPORT_ATTR_COUNT,                                                 \
                              reporting_info##ep_name,                                              \
                              ZB_CVC_ATTR_COUNT,                                                    \
                              cvc_alarm_info##ep_name)

#endif /* MAIN_MW_ZIGBEE_ZIGBEE_CFG */
