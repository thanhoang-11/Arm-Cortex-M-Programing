
#include <stdint.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define SRAM_START			0x20000000U
#define SRAM_SIZE			(128 * 1024)
#define SRAM_END			((SRAM_START) + (SRAM_SIZE))

#define STACK_START			SRAM_START
#define STACK_MSP_START		STACK_START
#define STACK_MSP_END		(STACK_MSP_START - 512)
#define STACK_PSP_START		(STACK_MSP_END)

__attribute__((naked)) void change_sp_2_psp(void){
	__asm volatile(".equ SRAM_END, (0X20000000 + (128 * 1024))");
	__asm volatile(".equ PSP_START, (SRAM_END - 512)");
	__asm volatile("LDR R0, =PSP_START");
	__asm volatile("MSR PSP, R0");
	__asm volatile("MOV R0, #0x00000002");
	__asm volatile("MSR CONTROL, R0");
	__asm volatile("BX LR");

}

void generate_exception(){
	__asm volatile("SVC #0X2");
}

uint8_t func_add(uint8_t a, uint8_t b, uint8_t c, uint8_t d){
	return a + b + c + d;
}

int main(void)
{

	change_sp_2_psp();

	uint8_t result;
	result = func_add(1,2,3,4);

	printf("Result = %hhu", result);

	generate_exception();
    /* Loop forever */
	for(;;);
}

void SVC_Handler(void){
	printf("in SVC_Handler\n");
}
