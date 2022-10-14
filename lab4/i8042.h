#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>
#include <minix/sysutil.h>

#define IRQ_12 0x0C

#define KBC_OUT_BUF 0x60
#define KBC_IN_BUF 0x60
#define KBC_ST_REG 0x64
#define KBC_CTRL_REG 0x64

#define KBC_FROM_M BIT(5)
#define KBC_TO_ERR BIT(7)
#define KBC_PAR_ERR BIT(6)
#define KBC_ST_IBF BIT(1)
#define KBC_OBF BIT(0)

#define KBC_READ 0x20
#define KBC_WRITE 0x60
#define KBC_WRITE_M 0xD4

#define MOUSE_EN_DATA_REP 0xF4
#define MOUSE_DIS_DATA_REP 0xF5
#define MOUSE_STREAM 0xEA
#define MOUSE_SET_DEFAULTS 0xF6
#define MOUSE_RESET 0xFF

#define MOUSE_ACK 0xFA

#define KBC_CMB_DIS_M BIT(5)
#define KBC_CMB_DIS_K BIT(4)
#define KBC_CMB_ENI_M BIT(1)
#define KBC_CMB_ENI_K BIT(0)

#define DELAY_US    20000

#endif /* _LCOM_I8042_H_*/
