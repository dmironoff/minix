# Makefile for arch-dependent kernel code
.include <bsd.own.mk>

HERE=${.CURDIR}/arch/${MACHINE_ARCH}
.PATH:	${HERE}

# LSC: putchar and kputc have the same signature. A bit hackish.
CPPFLAGS.subr_prf.c+= -Dputchar=kputc

# Activate optional support, may be deactivated.
CPPFLAGS.subr_prf.c+= -DLIBSA_PRINTF_LONGLONG_SUPPORT -DLIBSA_PRINTF_WIDTH_SUPPORT

.include "bsp/ti/Makefile.inc"

SRCS+=	head.c pre_init.c  \
    mpx.S arch_clock.c arch_do_vmctl.c arch_system.c do_padconf.c \
	exception.c hw_intr.c klib.S memory.c \
	protect.c direct_tty_utils.c arch_reset.c \
	pg_utils.c phys_copy.S phys_memset.S exc.S

klib.o mpx.o head.o: procoffsets.h

SRCS+= procoffsets.h

PROCOFFSETSCF=procoffsets.cf

.PATH: ${NETBSDSRCDIR}/minix/include/arch/${MACHINE_ARCH}/include

procoffsets.h: ${PROCOFFSETSCF} kernel.h proc.h stackframe.h archtypes.h
	${_MKTARGET_CREATE}
	${TOOL_CAT} ${HERE}/${PROCOFFSETSCF} | \
		${TOOL_GENASSYM} -- ${CC} ${CFLAGS:N-Wa,*} \
		${CPPFLAGS} ${PROF} ${${USE_BITCODE:Uno} == "yes":? -fno-lto:} \
		${GENASSYM_CPPFLAGS} >$@.tmp && \
	  mv -f $@.tmp $@ 

sconst.h: procoffsets.h
apic_asm.o head.o klib.o mpx.o: sconst.h

