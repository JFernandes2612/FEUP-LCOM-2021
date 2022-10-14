#include <lcom/lcf.h>
#include "utils.h"
#include <stdint.h>

int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t val = 0;
  sys_inb(port, &val);
  *value = (uint8_t) val;
  return 0;
}
