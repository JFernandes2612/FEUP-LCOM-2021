PROG=proj

VPATH = .:./sprites
SRCS = graphics.c LCOM.c player.c utils.c kbd.c entities.c timer.c enemies.c sprites.c mouse.c rtc.c uart.c game_helper.c

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!) (-D __LCOM_OPTIMIZED__)
CPPFLAGS += -pedantic -D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
