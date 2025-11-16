#
# BSP for TI hardware
#

.PATH: ${.CURDIR}/arch/${MACHINE_ARCH}/bsp/ti

SRCS+=	omap_init.c omap_serial.c omap_timer.c omap_padconf.c omap_intr.c omap_rtc.c \
	omap_reset.c

