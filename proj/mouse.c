#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>
#include <stdint.h>
#include "mouse.h"

static int mouse_hook_id;
static bool read_error = false;
struct packet mouse_pack;
static uint8_t mouse_data;
static uint8_t mouse_byte = 0;

int(mouse_subscribe_int)(uint8_t *bit_no)
{
  mouse_hook_id = *bit_no;
  sys_irqsetpolicy(IRQ_12, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
  return 0;
}

int(mouse_unsubscribe_int)()
{
  sys_irqrmpolicy(&mouse_hook_id);
  return 0;
}

int(kbc_write_command)(uint8_t cmd)
{
  uint8_t stat;
  while (1)
  {
    util_sys_inb(KBC_ST_REG, &stat); /* assuming it returns OK */
    /* loop while 8042 input buffer is not empty */
    if (!(stat & KBC_IBF))
    {
      sys_outb(KBC_CTRL_REG, cmd); /* no args command */
      return 0;
    }
    tickdelay(micros_to_ticks(DELAY_US)); // e.g. tickdelay()
  }
}

int(mouse_write_command)(uint8_t cmd)
{
  uint8_t stat;
  uint8_t response = 0;
  kbc_write_command(KBC_WRITE_M);
  while (response != MOUSE_ACK)
  {
    util_sys_inb(KBC_ST_REG, &stat); // assuming it returns OK
    // loop while 8042 input buffer is not empty
    if (!(stat & KBC_IBF))
    {
      sys_outb(KBC_IN_BUF, cmd); // no args command
      util_sys_inb(KBC_OUT_BUF, &response);
    }
    tickdelay(micros_to_ticks(DELAY_US)); // e.g. tickdelay()
  }
  return 0;
}

void(mouse_ih)(void)
{
  uint8_t stat;
  while (1)
  {
    util_sys_inb(KBC_ST_REG, &stat); /* assuming it returns OK */
    /* loop while 8042 output buffer is empty */
    if (stat & (KBC_OBF | KBC_AUX))
    {
      if (util_sys_inb(KBC_OUT_BUF, &mouse_data))
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
    tickdelay(micros_to_ticks(DELAY_US));
  }
}

int mouse_parse_data()
{
  if (read_error)
  {
    return 1;
  }
  mouse_pack.bytes[mouse_byte] = mouse_data;
  switch (mouse_byte)
  {
  case 0:
    mouse_pack.y_ov = mouse_data & BIT(7);
    mouse_pack.x_ov = mouse_data & BIT(6);
    mouse_pack.delta_y = (mouse_data & BIT(5)) << 9;
    mouse_pack.delta_x = (mouse_data & BIT(4)) << 9;
    mouse_pack.mb = mouse_data & BIT(2);
    mouse_pack.rb = mouse_data & BIT(1);
    mouse_pack.lb = mouse_data & BIT(0);
    mouse_byte++;
    return 1;
  case 1:
    mouse_pack.delta_x |= mouse_pack.delta_x ? (mouse_data - 256) : mouse_data;
    mouse_byte++;
    return 1;
  case 2:
    mouse_pack.delta_y |= mouse_pack.delta_y ? (mouse_data - 256) : mouse_data;
    mouse_byte = 0;
    return 0;
  }
  return 1;
}
