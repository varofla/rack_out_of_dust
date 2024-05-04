
#include "hw.h"
#include "driver.h"

bool hw_init(void) {
  bool ret = true;
  ret &= driver_init() == true;

  return ret;
}