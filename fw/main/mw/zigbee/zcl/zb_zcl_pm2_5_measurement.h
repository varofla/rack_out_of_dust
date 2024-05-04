#ifndef MAIN_MW_ZIGBEE_ZCL_ZB_ZCL_PM2_5_MEASUREMENT
#define MAIN_MW_ZIGBEE_ZCL_ZB_ZCL_PM2_5_MEASUREMENT

#include "zcl/zb_zcl_common.h"

#include "zcl/zb_zcl_commands.h"

#define ZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT 0x042A

/*! @brief Dust Measurement cluster attribute identifiers
    @see None ZCL spec.
*/
enum zb_zcl_pm2_5_measurement_attr_e {
  ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MEASURED_VALUE_ID = 0x0000,     /*!< MeasuredValue attribute */
  ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MIN_MEASURED_VALUE_ID = 0x0001, /*!< MinMeasuredValue attribute */
  ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MAX_MEASURED_VALUE_ID = 0x0002, /*!< MaxMeasuredValue attribute */
  ZB_ZCL_ATTR_PM2_5_MEASUREMENT_TOLERANCE_ID = 0x0003,          /*!< Tolerance attribute */
};

#define ZB_ZCL_PM2_5_MEASUREMENT_CLUSTER_REVISION_DEFAULT ((zb_uint16_t)0x00002)

/** @brief Default value for MeasuredValue attribute */
#define ZB_ZCL_PM2_5_MEASUREMENT_MEASURED_VALUE_DEFAULT_VALUE (.0 / .0)

/** @brief Default value for MinMeasuredValue attribute */
#define ZB_ZCL_PM2_5_MEASUREMENT_MIN_MEASURED_VALUE_DEFAULT_VALUE (.0 / .0)

/** @brief Default value for MaxMeasuredValue attribute */
#define ZB_ZCL_PM2_5_MEASUREMENT_MAX_MEASURED_VALUE_DEFAULT_VALUE (.0 / .0)

/** @brief MeasuredValue attribute unknown */
#define ZB_ZCL_PM2_5_MEASUREMENT_MEASURED_VALUE_UNKNOWN (.0 / .0)

/** @brief MinMeasuredValue attribute undefined */
#define ZB_ZCL_PM2_5_MEASUREMENT_MIN_MEASURED_VALUE_UNDEFINED (.0 / .0)

/** @brief MaxMeasuredValue attribute undefined */
#define ZB_ZCL_PM2_5_MEASUREMENT_MAX_MEASURED_VALUE_UNDEFINED (.0 / .0)

/** @brief MinMeasuredValue attribute minimum value */
#define ZB_ZCL_PM2_5_MEASUREMENT_MIN_MEASURED_VALUE_MIN_VALUE 0.0

/** @brief MaxMeasuredValue attribute maximum value */
// #define ZB_ZCL_PM2_5_MEASUREMENT_MAX_MEASURED_VALUE_MAX_VALUE 1.0

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MEASURED_VALUE_ID(data_ptr) \
  {                                                                                      \
    ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MEASURED_VALUE_ID,                                     \
        ZB_ZCL_ATTR_TYPE_U16,                                                            \
        ZB_ZCL_ATTR_ACCESS_READ_ONLY | ZB_ZCL_ATTR_ACCESS_REPORTING,                     \
        (void *)data_ptr                                                                 \
  }
#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MIN_MEASURED_VALUE_ID(data_ptr) \
  {                                                                                          \
    ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MIN_MEASURED_VALUE_ID,                                     \
        ZB_ZCL_ATTR_TYPE_U16,                                                                \
        ZB_ZCL_ATTR_ACCESS_READ_ONLY,                                                        \
        (void *)data_ptr                                                                     \
  }
#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MAX_MEASURED_VALUE_ID(data_ptr) \
  {                                                                                          \
    ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MAX_MEASURED_VALUE_ID,                                     \
        ZB_ZCL_ATTR_TYPE_U16,                                                                \
        ZB_ZCL_ATTR_ACCESS_READ_ONLY,                                                        \
        (void *)data_ptr                                                                     \
  }
#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_PM2_5_MEASUREMENT_TOLERANCE_ID(data_ptr) \
  {                                                                                 \
    ZB_ZCL_ATTR_PM2_5_MEASUREMENT_TOLERANCE_ID,                                     \
        ZB_ZCL_ATTR_TYPE_U16,                                                       \
        ZB_ZCL_ATTR_ACCESS_READ_ONLY,                                               \
        (void *)data_ptr                                                            \
  }

/*! @internal Number of attributes mandatory for reporting in Dust Measurement cluster */
#define ZB_ZCL_PM2_5_MEASUREMENT_REPORT_ATTR_COUNT 1

/*! Write attribute hook is used to set min/max Dust values */
void zb_zcl_pm2_5_measurement_write_attr_hook(
    zb_uint8_t endpoint, zb_uint16_t attr_id, zb_uint8_t *new_value);

/** @brief Declare attribute list for Dust Measurement cluster - server side
    @param attr_list - attribute list name
    @param measured_value - pointer to variable to store MeasuredValue attribute
    @param min_value - pointer to variable to store MinMeasuredValue attribute
    @param max_value - pointer to variable to store MAxMeasuredValue attribute
    @param tolerance - pointer to variable to store Tolerance attribute
*/
#define ZB_ZCL_DECLARE_PM2_5_MEASUREMENT_ATTRIB_LIST(attr_list,                                                         \
                                                     measured_value, min_measured_value, max_measured_value, tolerance) \
  ZB_ZCL_START_DECLARE_ATTRIB_LIST_CLUSTER_REVISION(attr_list, ZB_ZCL_PM2_5_MEASUREMENT)                                \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MEASURED_VALUE_ID, (measured_value))                               \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MIN_MEASURED_VALUE_ID, (min_measured_value))                       \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MAX_MEASURED_VALUE_ID, (max_measured_value))                       \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_PM2_5_MEASUREMENT_TOLERANCE_ID, (tolerance))                                         \
  ZB_ZCL_FINISH_DECLARE_ATTRIB_LIST

void zb_zcl_pm2_5_measurement_init_server(void);
void zb_zcl_pm2_5_measurement_init_client(void);
#define ZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT_SERVER_ROLE_INIT zb_zcl_pm2_5_measurement_init_server
#define ZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT_CLIENT_ROLE_INIT zb_zcl_pm2_5_measurement_init_client

#endif /* MAIN_MW_ZIGBEE_ZCL_ZB_ZCL_PM2_5_MEASUREMENT */
