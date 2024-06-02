#ifndef MAIN_HW_DRIVER_SHT4X_SHT4X
#define MAIN_HW_DRIVER_SHT4X_SHT4X

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  double temperature;
  double humidity;
} sht4x_data_t;

bool sht4x_init(void);
sht4x_data_t *sht4x_get(sht4x_data_t *data_buff);

#endif /* MAIN_HW_DRIVER_SHT4X_SHT4X */
