#include "rtc.h"
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>
#include "utils.h"

static int rtc_hook_id;
bool rtc_alarm_occurred = false;

int(rtc_subscribe_int)(uint8_t *bit_no)
{
  rtc_hook_id = *bit_no;
  return sys_irqsetpolicy(IRQ_8, IRQ_REENABLE, &rtc_hook_id);
}

int(rtc_unsubscribe_int)()
{
  return sys_irqrmpolicy(&rtc_hook_id);
}

int rtc_read_register(uint8_t reg, uint8_t *data)
{
  if (sys_outb(RTC_ADDR_REG, reg))
    return 1;
  if (util_sys_inb(RTC_DATA_REG, data))
    return 1;
  return 0;
}

int rtc_write_register(uint8_t reg, uint8_t data)
{
  if (sys_outb(RTC_ADDR_REG, reg))
    return 1;
  if (sys_outb(RTC_DATA_REG, data))
    return 1;
  return 0;
}

int rtc_set_alarm(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
  if (rtc_write_register(RTC_REG_S_A, seconds))
    return 1;
  if (rtc_write_register(RTC_REG_M_A, minutes))
    return 1;
  if (rtc_write_register(RTC_REG_H_A, hours))
    return 1;
  return 0;
}

int rtc_read_time(uint8_t *hours, uint8_t *minutes, uint8_t *seconds)
{
  uint8_t regA = 0;
  do
  {
    if (rtc_read_register(RTC_REG_A, &regA))
      return 1;
  } while (regA & RTC_UIP);

  if (rtc_read_register(RTC_REG_H, hours))
    return 1;
  if (rtc_read_register(RTC_REG_M, minutes))
    return 1;
  if (rtc_read_register(RTC_REG_S, seconds))
    return 1;
  return 0;
}

int rtc_set_periodic(uint8_t delta_t)
{
  uint8_t regA = 0;
  if (rtc_read_register(RTC_REG_A, &regA))
    return 1;
  regA = (regA & 0xF0) | (delta_t & 0x0F);
  if (rtc_write_register(RTC_REG_A, regA))
    return 1;
  return 0;
}

int rtc_set_alarm_delta_s(uint8_t delta_seconds)
{
  uint8_t hours, minutes, seconds;
  uint8_t delta_hours, delta_minutes;
  if (rtc_read_time(&hours, &minutes, &seconds))
    return 1;
  bcd_to_binary(&seconds);
  seconds += delta_seconds;
  delta_minutes = seconds / 60;
  seconds %= 60;
  if (delta_minutes)
  {
    bcd_to_binary(&minutes);
    minutes += delta_minutes;
    delta_hours = minutes / 60;
    minutes %= 60;
    if (delta_hours)
    {
      bcd_to_binary(&hours);
      hours += delta_hours;
      hours %= 24;
      binary_to_bcd(&hours);
    }
    binary_to_bcd(&minutes);
  }
  binary_to_bcd(&seconds);
  if (rtc_set_alarm(hours, minutes, seconds))
    return 1;
  return 0;
}

int bcd_to_binary(uint8_t* val)
{
  *val = (*val >> 4) * 10 + (*val & 0x0F);
  return 0;
}

int binary_to_bcd(uint8_t* val)
{
  if (*val >= 100)
    return 1;
  *val = ((*val / 10) << 4) | (*val % 10);
  return 0;
}

void(rtc_ih)(void)
{
  uint8_t regC = 0;
  uint8_t seconds = 0;
  uint8_t minutes = 0;
  uint8_t hours = 0;

  rtc_alarm_occurred = false;

  rtc_read_register(RTC_REG_C, &regC);

  if(regC & RTC_UF)
  {
    rtc_read_time(&hours, &minutes, &seconds);
    //printf("%x : %x : %x \n", hours, minutes, seconds);
  }
  if(regC & RTC_AF)
  {
    rtc_alarm_occurred = true;
    printf("ALARME\n");
  }
}
