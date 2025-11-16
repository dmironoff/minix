OUTPUT_ARCH("arm")
ENTRY(MINIX)

_kern_phys_base = 0x80200000;	/* phys 4MB aligned for convenient remapping */
_kern_vir_base =  0xF0400000;	/* map kernel high for max. user vir space */
_kern_offset = (_kern_vir_base - _kern_phys_base);

__k_unpaged__kern_offset = _kern_offset;
__k_unpaged__kern_vir_base = _kern_vir_base;
__k_unpaged__kern_phys_base = _kern_phys_base;

SECTIONS
{
	. = _kern_vir_base;
	.text             : AT(ADDR(.text)) { *(.startup); *(.text*) }
    _etext = .;

	. = ALIGN(4096); usermapped_start = .;
	.usermapped_glo : AT(ADDR(.usermapped_glo)) { *(.usermapped_glo) }
	. = ALIGN(4096); usermapped_nonglo_start = .;
	.usermapped : AT(ADDR(.usermapped)) { *(.usermapped) }
	. = ALIGN(4096); usermapped_end = .;
	.data ALIGN(4096) : AT(ADDR(.data)) { *(.data .rodata* ) }
	. = ALIGN(4096);
	_edata = .;
	.bss ALIGN(4096)  : AT(ADDR(.bss)) { *(.bss* COMMON)
		_kern_size = . - _kern_vir_base;

		. += 4096;
	}
	_end = .;

      /DISCARD/ :
       {
               *(.ARM.exidx*)
       }
}
