#ifndef MAIN_HW_DRIVER_PMS7003_PMS7003
#define MAIN_HW_DRIVER_PMS7003_PMS7003

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  int32_t pm_1_0;
  int32_t pm_2_5;
  int32_t pm_10;
} pms7003_data_t;

bool pms7003_init(void);
pms7003_data_t *pms7003_get(pms7003_data_t *data_buff);

#endif /* MAIN_HW_DRIVER_PMS7003_PMS7003 */
