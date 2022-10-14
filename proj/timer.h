#ifndef TIMER_H_
#define TIMER_H_

#include <lcom/lcf.h>

/**
 * @brief Subscribes the interrupts for the timer at IRQ 0
 *
 * @param bit_no id of the subscription
 *
 * @return int 1 if it fails 0 otherwise
 */
int(timer_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes the interrupts for the timer at IRQ 0
 *
 * @return int 1 if it fails 0 otherwise
 */
int(timer_unsubscribe_int)();

#endif
