
ENTRY(Reset_Handler)

MEMORY{
	FLASH(rx):ORIGIN = 0x08000000, LENGTH = 1024K
	SRAM(rwx):ORIGIN = 0x20000000, LENGTH = 128K
}

__max_heap_size	= 0x400;	/* A symbol declaration . Not a variable */
__max_stack_size = 0x200;	/* A symbol declaration . Not a variable */

SECTIONS
{
	.text :{
							/* The linker assumed a location counter */
		*(.isr_vector)
		*(.text)
		*(.text.*)
		*(.init)
		*(.fini)
		*(.rodata)
		*(.rodata.*)
		. = ALIGN(4);
		_etext = .;			/* Store the updated location counter value in to a symbol */
	}> FLASH
	
	_la_data = LOADADDR(.data);
	
	.data :{
		_sdata = .; 		
		*(.data)
		*(.data.*)
		. = ALIGN(4);
		_edata = .;
	}> SRAM AT> FLASH
	

	
	.bss :{
		_sbss = .;
		__bss_start__ = _sbss;
		*(.bss)
		*(.bss.*)
		. = ALIGN(4);
		_ebss = .;
		__bss_end__ = _ebss;
		. = ALIGN(4);
		end = .;
		__end__ = .;
	}> SRAM
}