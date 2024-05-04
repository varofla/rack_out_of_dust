#include <stdbool.h>

#include "driver.h"

#include "am2320/am2320.h"
#include "fan4p/fan4p.h"
#include "pms7003/pms7003.h"
#include "stled/stled.h"
#include "zbrstbtn/zbrstbtn.h"

bool driver_init(void) {
  bool ret = true;

  ret &= am2320_init();
  ret &= fan4p_init();
  ret &= pms7003_init();
  ret &= stled_init();
  ret &= zbrstbtn_init();

  return ret;
}