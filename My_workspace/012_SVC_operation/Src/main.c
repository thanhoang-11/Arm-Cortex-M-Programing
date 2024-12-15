
#include <stdint.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	uint32_t data1, data2;
	printf("Enter data1 & data2:\n");
	scanf("%u %u", &data1, &data2);
	__asm("MOV R0, %0" : "=r"(data1));
	__asm("MOV R1, %0" : "=r"(data2));
	uint8_t option;
	printf("Enter the option: \n");
	scanf("%u", &option);
	__asm ("SVC #36");

	uint32_t result;
	__asm volatile("MOV %0, R0" : "=r"(result));
	printf("Result is: %u\n", result);
    /* Loop forever */
	for(;;);
}

__attribute__((naked)) void SVC_Handler(void){
	__asm("MRS R0, MSP");
	__asm("B SVC_Handler_c");
}

void SVC_Handler_c(uint32_t *pBaseOfStackFrame){
	uint8_t *pReturn_Address = (uint8_t*)pBaseOfStackFrame[6];

	pReturn_Address -= 2;

	uint8_t SVC_number = *pReturn_Address;

	uint32_t data1, data2, result;
	data1 = *pBaseOfStackFrame;
	data2 = pBaseOfStackFrame[1];

	switch(SVC_number){
		case 36:
			result = data1 + data2;
			break;
		case 37:
			result = data1 - data2;
			break;
		case 38:
			result = data1 * data2;
			break;
		case 39:
			result = data1 / data2;
			break;
	}
	*pBaseOfStackFrame = result;
}
