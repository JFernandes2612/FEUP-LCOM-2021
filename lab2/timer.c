#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

static int hook_id;
unsigned counter = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  //no start up freq é igual a 60 (HRz)
  if (freq < 19 || freq > TIMER_FREQ)//max freq = TIMER_FREQ
  {                                  //min freq = 19 (from testing)
    printf("%dHz frequence is not possible.\n", freq);
    return 1;
  }
  uint8_t status = 0;
  uint8_t rbcw = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  sys_outb(TIMER_CTRL, rbcw); //escreve read-back command para o status
  util_sys_inb(TIMER_0 + timer, &status); //le e guarda o status do timer na variavel status
  printf("status = %d\n", status);
  sys_outb(TIMER_CTRL, (timer << 6) | TIMER_LSB_MSB | status & 0x0F); //escreve no controlador que vamos escrever o LSB e depois o MSB do timer escolhido mantendo o byte mais significativo do control
  uint16_t dif = TIMER_FREQ/freq; //calcula a diferenca da frequencia normal do timer - wikipedia Mode2 (rate generator for i8253/4)
  sys_outb(TIMER_0 + timer, (uint8_t)dif); //escreve o LSB
  sys_outb(TIMER_0 + timer, (uint8_t)(dif >> 8)); //escreve o MSB
  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  hook_id = *bit_no;
  sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id);
  return 0;
}

int (timer_unsubscribe_int)() {
  sys_irqrmpolicy(&hook_id);
  return 0;
}

void (timer_int_handler)() {
  counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t rbcw = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer); //escreve read-back command para o status
  sys_outb(TIMER_CTRL, rbcw); //escreve o read-back command
  util_sys_inb(TIMER_0 + timer, st); //le o status do timer selecionado
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  union timer_status_field_val info;
  switch (field){
    case tsf_all:
      info.byte = st;
      break;
    case tsf_initial:
      info.in_mode = (st & (BIT(5)|BIT(4))) >> 4;
      break;
    case tsf_mode:
      info.count_mode = (st & (BIT(3)|BIT(2)|BIT(1))) >> 1;
      break;
    case tsf_base:
      info.bcd = st & BIT(0);
      break;
  }
  return timer_print_config(timer, field, info);
}
