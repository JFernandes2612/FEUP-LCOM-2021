#ifndef _LCOM_KBD_M
#define _LCOM_KBD_M
#include <lcom/lcf.h>
#include "i8042.h"

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

int (kbc_write_command)(uint8_t cmd);

int (mouse_write_command) (uint8_t cmd);

#endif
