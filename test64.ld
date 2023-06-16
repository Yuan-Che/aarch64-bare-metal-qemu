ENTRY(_startup)
SECTIONS
{
	. = 0x00080000000;
	.startup . : { startup64.o(.text) }
	.text.boot : { *(.text.boot) }
	.text : { *(.text) }
	.data : { *(.data) }
	.rodata : { *(.rodata) }
	.bss : { *(.bss COMMON) }
	. = ALIGN(8);
	. = . + 0x4000; /* 16 kB of stack memory */
	LD_STACK_PTR = .;
}
