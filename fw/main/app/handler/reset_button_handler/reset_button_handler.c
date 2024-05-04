#include <stdint.h>

#include <zephyr/kernel.h>

#include "zbrstbtn/zbrstbtn.h"

#include "reset_button_handler.h"

#include "zigbee.h"

typedef struct {
  struct k_work work;
} module_data_t;
static module_data_t module_data;

static void s_reset_button_work(struct k_work *work) {
  zigbee_reset();
}

static void s_reset_button_handler(uint8_t clicked_time) {
  if (clicked_time >= 5) {
    k_work_submit(&module_data.work);
  }
}

bool reset_button_handler_init(void) {
  k_work_init(&module_data.work, s_reset_button_work);

  zbrstbtn_set_callback(s_reset_button_handler);

  return true;
}
