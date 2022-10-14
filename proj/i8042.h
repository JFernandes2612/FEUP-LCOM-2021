#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>
#include <minix/sysutil.h>

#define IRQ_1 0x01  /**< @brief IRQ line 1 for the Keyboard */
#define IRQ_12 0x0C /**< @brief IRQ line 12 for the PS/2 Mouse */

#define KBC_OUT_BUF 0x60 /**< @brief KBC output buffer */
#define KBC_IN_BUF 0x60
#define KBC_ST_REG 0x64 /**< @brief KBC status register */
#define KBC_CTRL_REG 0x64

#define KBC_TO_ERR BIT(7)  /**< @brief KBC timeout error */
#define KBC_PAR_ERR BIT(6) /**< @brief KBC parity error */
#define KBC_AUX BIT(5)     /**< @brief KBC mouse data */

#define KBC_IBF BIT(1) /**< @brief KBC input buffer full */
#define KBC_OBF BIT(0) /**< @brief KBC output buffer full */

#define TWO_BYTE_SC 0xE0 /**< @brief Keyboard 2 byte starter byte */
#define BREAKC BIT(7)    /**< @brief Keyboard break code most significant bit */
#define ESC_MAKE 0x01    /**< @brief Keyboard ESC make code */
#define S_MAKE 0x1F      /**< @brief Keyboard ESC make code */
#define D_MAKE 0x20      /**< @brief Keyboard D make code */
#define W_MAKE 0x11      /**< @brief Keyboard W make code */
#define A_MAKE 0x1E      /**< @brief Keyboard A make code */
#define SP_MAKE 0x39     /**< @brief Keyboard Space make code */
#define Q_MAKE 0x10      /**< @brief Keyboard Q make code */

/* KBC COMMANDS */
#define KBC_READ 0x20      /**< @brief KBC write command byte */
#define KBC_WRITE 0x60     /**< @brief KBC read command byte */
#define KBC_SELFCHECK 0xAA /**< @brief KBC checks it self */
#define KBC_KICHECK 0xAB   /**< @brief KBC checks the keyboard interface */
#define KBC_DISABLE 0xAD   /**< @brief KBC disables the keyboard interface */
#define KBC_ENABLE 0xAE    /**< @brief KBC enables the keyboard interface */

/* KBC COMMAND BYTE VALUES */
#define KBC_CMB_DIS_M BIT(5) /**< @brief KBC disable mouse interface */
#define KBC_CMB_DIS_K BIT(4) /**< @brief KBC disable keyboard interface */
#define KBC_CMB_EIN_M BIT(1) /**< @brief KBC enable mouse interrupts */
#define KBC_CMB_EIN_K BIT(0) /**< @brief KBC enable keyboard interrupts */

#define KBC_WRITE_M 0xD4        /**< KBC write command to Mouse */
#define MOUSE_EN_DATA_REP 0xF4  /**< Mouse Enable data reporting command */
#define MOUSE_DIS_DATA_REP 0xF5 /**< Mouse disable data reporting */
#define MOUSE_STREAM 0xEA       /**< Mouse enable stream mode */
#define MOUSE_SET_DEFAULTS 0xF6 /**< Mouse se to default settings */
#define MOUSE_RESET 0xFF        /**< Mouse Reset */

#define MOUSE_ACK 0xFA /**< Mouse Ackowledge */

#define DELAY_US 20000 /**< @brief delay */

#endif /* _LCOM_I8042_H_*/
