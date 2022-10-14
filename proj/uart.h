#ifndef UART_H
#define UART_H

#include <lcom/lcf.h>

#define UART_COM1_BASE_ADDR 0x3F8 /**<@brief UART Serial Port COM 1 base address */

#define UART_DLL 0 /**<@brief UART divisor latch LSB */
#define UART_DLM 1 /**<@brief UART divisor latch MSB */

#define UART_RBR 0 /**<@brief UART Receiver Buffer Register */
#define UART_THR 0 /**<@brief UART Transmitter Holding Register */
#define UART_IER 1 /**<@brief UART Interrupt Enable Register */
#define UART_IIR 2 /**<@brief UART Interrupt Identification Register */
#define UART_FCR 2 /**<@brief UART FIFO Control Register */
#define UART_LCR 3 /**<@brief UART Line Control Register */
#define UART_MCR 4 /**<@brief UART Modem Control Register */
#define UART_LSR 5 /**<@brief UART Line Status Register*/
#define UART_MSR 6 /**<@brief UART Modem Status Register */
#define UART_SR 7 /**<@brief UART Scratchpad Register */

#define UART_INT_NOT_PEND BIT(0) /**<@brief UART Interruption not pending flag */
#define UART_INT_ID ( BIT(1) | BIT(2) | BIT(3) ) /**<@brief UART Interruption ID */

#define UART_RDA_INT BIT(2) /**<@brief UART Received data Interrupt */
#define UART_THRE_INT BIT(1) /**<@brief UART Transmitter Holding register empty interrupt */

#define UART_LSR_RECEIVER BIT(0) /**<@brief UART LSR received data */
#define UART_LSR_OVERRUN BIT(1) /**<@brief UART LSR Overrun error */
#define UART_LSR_PARITY BIT(2) /**<@brief UART LSR Parity error */
#define UART_LSR_FRAME BIT(3) /**<@brief UART LSR Framing error */
#define UART_LSR_FIFO BIT(7) /**<@brief UART LSR FIFO Error */
#define UART_LSR_THRE BIT(5) /**<@brief UART LSR Transmitter holding register empty */
#define UART_LSR_TER BIT(6) /**<@brief UART LSR Transmitter Empty register */

#define UART_COM1_IRQ 4 /**<@brief UART Serial Port COM 1 IRQ line */

/**
 * @brief Enumerator that represents the player number (1 or 2)
 * @enum Player
 */
enum Player
{
  PLAYER_1, /**<@brief Player 1 */
  PLAYER_2 /**<@brief Player 2 */
};

/**
 * @brief Enumerator that represents the current syncing step/state
 * @enum SyncState
 */
enum SyncState
{
  FIRST_STEP, /**<@brief Syncing step 1 */
  SECOND_STEP /**<@brief Syncing step 2 and final */
};

/**
 * @brief Subscribes the interrupts for the UART COM1 serial port
 *
 * @param bit_no id of the subscription
 * @return int 1 if it fails, 0 otherwise
 */
int uart_com1_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubscribes the interrupts for the UART COM1 serial port
 *
 * @return int 1 if it fails, 0 otherwise
 */
int uart_com1_unsubscribe_int();

/**
 * @brief UART's interrupt handler
 */
void uart_ih();

/**
 * @brief Sends a byte to the UART
 *
 * @param data data byte
 */
void send_data_uart(const uint8_t data);

/**
 * @brief First step of syncing the players in COOP mode
 *
 * @param player_num player number (1 or 2)
 * @param uart_com1_data Data that came from the UART
 * @return int 1 if the first step has been completed, 0 otherwise
 */
int sync_first_step(enum Player *player_num, const uint8_t uart_com1_data);

/**
 * @brief Second step of syncing the player in COOP mode
 *
 * @param player_num player number (1 or 2)
 * @param uart_com1_data Data that came from the UART
 * @return int 1 if the syncing has been completed, 0 otherwise
 */
int sync_second_step(const enum Player player_num, const uint8_t uart_com1_data);

/**
 * @brief
 *
 * @param player_num player number (1 or 2)
 * @param sync_state Current sync state
 * @param uart_com1_data Data that came from the UART
 * @return int 1 if the syncing has been completed, 0 otherwise
 */
int sync_players(enum Player *player_num, enum SyncState* sync_state, const uint8_t uart_com1_data);

#endif
