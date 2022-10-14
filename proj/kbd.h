#ifndef _LCOM_KBD_
#define _LCOM_KBD_

/**
 * @brief Enumerator that indicates the status of the current data read from the KBC (keyboard)
 * @enum kbd_data_status
 */
enum kbd_data_status
{
    SINGLE_READY, /**<@brief Single byte data available */
    DOUBLE_READY, /**<@brief Dual byte data available */
    NOT_READY /**<@brief data not available */
};

/**
 * @brief Subscribes the interrupts for the Keyboard at IRQ 1
 *
 * @param bit_no id of the subscription
 *
 * @return int 1 if it fails 0 otherwise
 */
int kbd_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubscribes the interrupts for the Keyboard at IRQ 1
 *
 * @return int 1 if it fails 0 otherwise
 */
int kbd_unsubscribe_int();

/**
 * @brief Keyboard interrupt handler
 */
void (kbd_ih)(void);

/**
 * @brief Parses the KBC keyboard data
 *
 * @return enum kbd_data_status parsed data information
 */
enum kbd_data_status kbd_parse_data();

#endif
