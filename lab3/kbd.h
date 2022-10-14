#ifndef _LCOM_KBD_
#define _LCOM_KBD_
#include <lcom/lcf.h>

int (kbd_subscribe_int)(uint8_t *bit_no);

int (kbd_unsubscribe_int)();

int (kbd_write_command)(uint8_t cmd);

int (timer_subscribe_int)(uint8_t *bit_no);

int (timer_unsubscribe_int)();

#endif
