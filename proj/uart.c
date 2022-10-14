#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>
#include "uart.h"

static int uart_com1_hook_id;
uint8_t uart_com1_data = 0;
bool uart_read_error = false;

int uart_com1_subscribe_int(uint8_t *bit_no)
{
    uart_com1_hook_id = *bit_no;
    if (sys_irqsetpolicy(UART_COM1_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &uart_com1_hook_id))
        return 1;
    return 0;
}

int uart_com1_unsubscribe_int()
{
    if (sys_irqrmpolicy(&uart_com1_hook_id))
        return 1;
    return 0;
}

void uart_ih()
{
  uint8_t iir;
  util_sys_inb(UART_COM1_BASE_ADDR + UART_IIR, &iir);
  if (!(iir & UART_INT_NOT_PEND))
  {
    switch (iir & UART_INT_ID)
    {
    case UART_RDA_INT:
    {
      /* read received character */
      uint8_t uart_lsr_data;
      util_sys_inb(UART_COM1_BASE_ADDR + UART_LSR, &uart_lsr_data);
      while (uart_lsr_data & UART_LSR_RECEIVER)
      {
        util_sys_inb(UART_COM1_BASE_ADDR + UART_RBR, &uart_com1_data);
        printf("R - %x\n", uart_com1_data);
        uart_read_error = uart_lsr_data & UART_LSR_FIFO;
        util_sys_inb(UART_COM1_BASE_ADDR + UART_LSR, &uart_lsr_data);
      }
      break;
    }
    default:
      break;
    }
  }
}

void send_data_uart(const uint8_t data)
{
  uint8_t uart_lsr_data;
  util_sys_inb(UART_COM1_BASE_ADDR + UART_LSR, &uart_lsr_data);
  while (1)
  {
    if (uart_lsr_data & (UART_LSR_THRE | UART_LSR_TER))
    {
      printf("S - %x\n", data);
      sys_outb(UART_COM1_BASE_ADDR + UART_THR, data);
      break;
    }
    util_sys_inb(UART_COM1_BASE_ADDR + UART_LSR, &uart_lsr_data);
  }
}

int sync_first_step(enum Player *player_num, const uint8_t uart_com1_data)
{
  if(uart_com1_data == 'R')
  {
    *player_num = PLAYER_2;
    send_data_uart('S');
    return 0;
  }
  else send_data_uart('R');
  return 1;
}

int sync_second_step(const enum Player player_num, const uint8_t uart_com1_data)
{
  if (player_num == PLAYER_1 && uart_com1_data == 'S')
  {
    send_data_uart('F');
    return 1;
  }
  if (player_num == PLAYER_2 && uart_com1_data == 'F')
  {
    return 1;
  }
  return 0;
}

int sync_players(enum Player *player_num, enum SyncState* sync_state, const uint8_t uart_com1_data)
{
  switch(*sync_state)
  {
    case FIRST_STEP:
      sync_first_step(player_num, uart_com1_data);
      (*sync_state)++;
      break;
    case SECOND_STEP:
      if (sync_second_step(*player_num, uart_com1_data))
        return 1;
      break;
  }
  return 0;
}
