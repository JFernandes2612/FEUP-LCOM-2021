#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>
#include <minix/sysutil.h>

#define IRQ_1 0x01

#define KBC_OUT_BUF 0x60
#define KBC_ST_REG 0x64

#define KBC_TO_ERR BIT(7)
#define KBC_PAR_ERR BIT(6)
#define KBC_ST_IBF BIT(1)
#define KBC_OBF BIT(0)

#define TWO_BYTE_SC 0xE0
#define BREAKC BIT(7)
#define ESC 0x01

#define KBC_READ 0x20
#define KBC_WRITE 0x60
#define KBC_SELFCHECK 0xAA
#define KBC_KICHECK 0xAB
#define KBC_DISABLE 0xAD
#define KBC_ENABLE 0xAE

#define KBC_CMB_DIS_M BIT(5)
#define KBC_CMB_DIS_K BIT(4)
#define KBC_CMB_ENI_M BIT(1)
#define KBC_CMB_ENI_K BIT(0)

#define TIMER0_IRQ 0

#define DELAY_US    20000

#endif /* _LCOM_I8042_H_*/
