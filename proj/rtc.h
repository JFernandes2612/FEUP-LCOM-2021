#ifndef RTC_H
#define RTC_H

#include <minix/sysutil.h>

#define IRQ_8 0x08        /**<@brief RTC IRQ line */
#define RTC_ADDR_REG 0x70 /**<@brief RTC address register */
#define RTC_DATA_REG 0x71 /**<@brief RTC data register */
#define RTC_UF BIT(4)     /**<@brief Update interrupt pending */
#define RTC_AF BIT(5)     /**<@brief Alarm interrupt pending */
#define RTC_PF BIT(6)     /**<@brief Periodic interrupt pending */
#define RTC_UIP BIT(7)    /**<@brief Update in progress */
#define RTC_REG_A 10      /**<@brief RTC register A */
#define RTC_REG_B 11      /**<@brief RTC register B */
#define RTC_REG_C 12      /**<@brief RTC register C */

#define RTC_REG_H_A 5     /**<@brief RTC alarm hours register */
#define RTC_REG_H 4       /**<@brief RTC hours register */
#define RTC_REG_M_A 3     /**<@brief RTC alarm minutes register */
#define RTC_REG_M 2       /**<@brief RTC minutes register */
#define RTC_REG_S_A 1     /**<@brief RTC alarm seconds register */
#define RTC_REG_S 0       /**<@brief RTC seconds register */

#define RTC_UIE BIT(4)    /**<@brief Enable update interrupts */
#define RTC_AIE BIT(5)    /**<@brief Enable alarm interrupt */
#define RTC_PIE BIT(6)    /**<@brief Enable periodic interrupts */

/**
 * @brief Subscribes the RTC interrupts
 *
 * @return 1 if it fails, 0 otherwise
 */
int(rtc_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes the RTC interrupts
 *
 * @return 1 if it fails, 0 otherwise
 */
int(rtc_unsubscribe_int)();

/**
 * @brief Reads the Register @p reg of the RTC
 *
 * @param reg register number
 * @param data return data
 * @return int 1 if it fails, 0 otherwise
 */
int rtc_read_register(uint8_t reg, uint8_t *data);

/**
 * @brief Writes to the Register @p reg of the RTC @p data
 *
 * @param reg register number
 * @param data writing data
 * @return int 1 if it fails, 0 otherwise
 */
int rtc_write_register(uint8_t reg, uint8_t data);

/**
 * @brief Sets an alarm at @p hours : @p minutes : @p seconds
 *
 * @param hours hour to set the alarm to
 * @param minutes minute to set the alarm to
 * @param seconds second to set the alarm to
 * @return int 1 if it fails, 0 otherwise
 */
int rtc_set_alarm(uint8_t hours, uint8_t minutes, uint8_t seconds);

/**
 * @brief Reads the time from the RTC
 *
 * @param hours address where the current hours will be written
 * @param minutes address where the current minutes will be written
 * @param seconds address where the current seconds will be written
 * @return int 1 if it fails, 0 otherwise
 */
int rtc_read_time(uint8_t *hours, uint8_t *minutes, uint8_t *seconds);

/**
 * @brief Sets the periodic interrupts time to send interrupts every @p delta_t
 *
 * @param delta_t time corresponding to the periodic interrupt specifications
 * @return int 1 if it fails, 0 otherwise
 */
int rtc_set_periodic(uint8_t delta_t);

/**
 * @brief Sets an alarm at current_time + @p delta_seconds
 *
 * @param delta_seconds the number of seconds before the alarm will trigger
 * @return int 1 if it fails, 0 otherwise
 */
int rtc_set_alarm_delta_s(uint8_t delta_seconds);

/**
 * @brief Converts a number in BCD to binary
 *
 * @param val the value which is to be converted; also a return value
 * @return int 1 if it fails, 0 otherwise
 */
int bcd_to_binary(uint8_t* val);

/**
 * @brief Converts a number in binary to BCD
 *
 * @param val the value which is to be converted; also a return value
 * @return int 1 if the number has more than 2 digits, 0 otherwise
 */
int binary_to_bcd(uint8_t* val);

/**
 * @brief RTC interrupt handler
 */
void(rtc_ih)(void);

#endif
