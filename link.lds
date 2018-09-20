ENTRY(_start)

SECTIONS
{
	. = 0x30000000;
	code_start = .;
	.init	:
	{
		start.o(.text)
		board.o(.text)
		s3c24xx.o(.text)
		nand.o(.text)
	}
	.text	:
	{
		*(.text)
	}
	__fstart = .;
	func	:
	{
		*(func)
	}
	__fend = .;
	.rodata	:	{*(.rodata)}
	.data	:
	{
		*(.data)
	}
	__bss_start = .;
	.bss	:
	{
		*(.bss)
	}
	__bss_end = .;
}

