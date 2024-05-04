#include "app.h"

#include "handler/handler.h"
#include "task/task.h"

bool app_init(void) {
  bool ret = true;

  ret &= handler_init();
  ret &= task_init();

  return ret;
}

void app_main(void) {
  return;
}