#ifndef _LCOM_KBD_M
#define _LCOM_KBD_M
#include <lcom/lcf.h>
#include "i8042.h"

/**
 * @brief Subscribes interrupts for the mouse
 *
 * @return 1 if it fails, 0 otherwise
 */
int(mouse_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes interrupts for the mouse
 *
 * @return 1 if it fails, 0 otherwise
 */
int(mouse_unsubscribe_int)();

/**
 * @brief Writes @p cmd to the KBC
 *
 * @param cmd command to be writen
 */
int(kbc_write_command)(uint8_t cmd);

/**
 * @brief Writes @p cmd to the mouse
 *
 * @param cmd command to be writen
 */
int(mouse_write_command)(uint8_t cmd);

/**
 * @brief Mouse interrupt handler
 */
void(mouse_ih)(void);

/**
 * @brief Parses the data into a @p packet
 *
 * @return int 1 if it fails or the packet is not complete, 0 otherwise
 */
int mouse_parse_data();

#endif
