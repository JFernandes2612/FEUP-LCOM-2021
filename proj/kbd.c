#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>
#include "i8042.h"
#include "kbd.h"

static int kbd_hook_id;
static bool read_error = false;
uint8_t kbd_data;
static bool make;
static uint8_t bytes[2];
static bool double_byte = false;

int(kbd_subscribe_int)(uint8_t *bit_no)
{
  kbd_hook_id = *bit_no;
  return sys_irqsetpolicy(IRQ_1, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbd_hook_id);
}

int(kbd_unsubscribe_int)()
{
  return sys_irqrmpolicy(&kbd_hook_id);
}


void(kbd_ih)(void)
{
  uint8_t stat;
  while (1)
  {
    if (util_sys_inb(KBC_ST_REG, &stat))
      break;
    /* loop while 8042 output buffer is empty */
    if (stat & KBC_OBF && !(stat & KBC_AUX))
    {
      if (util_sys_inb(KBC_OUT_BUF, &kbd_data))
        break;
      if ((stat & (KBC_PAR_ERR | KBC_TO_ERR)) == 0)
      {
        read_error = false;
      }
      else
      {
        read_error = true;
      }
      break;
    }
    tickdelay(micros_to_ticks(DELAY_US)); // e.g. tickdelay()
  }
}

enum kbd_data_status kbd_parse_data()
{
  if (!read_error)
  {
    make = !(kbd_data & BREAKC);
    if (double_byte)
    {
      bytes[1] = kbd_data;
      double_byte = false;
      //process dual byte (we think we dont need it)
      return DOUBLE_READY;
    }
    else
    {
      bytes[0] = kbd_data;
      if (kbd_data == TWO_BYTE_SC)
      {
        double_byte = true;
        return NOT_READY;
      }
      else //process single byte
      {
        return SINGLE_READY;
      }
    }
  }
  return NOT_READY;
}
