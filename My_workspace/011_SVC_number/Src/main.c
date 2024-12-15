

#include <stdint.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{

	__asm ("SVC #8");

	uint32_t data;

	__asm volatile ("MOV %0,R0": "=r"(data) ::);

	printf(" data = %ld\n",data);

	for(;;);
}

__attribute__((naked)) void SVC_Handler(void){
	__asm("MRS R0, MSP");
	__asm("B SVC_Handler_c");
}

void SVC_Handler_c(uint32_t *pBaseOfStackFrame){

	printf("in SVC handler\n");

	uint8_t *pReturn_addr = (uint8_t*)pBaseOfStackFrame[6];

	//2. decrement the return address by 2 to point to
	//opcode of the SVC instruction in the program memory
	pReturn_addr-=2;


	//3. extract the SVC number (LSByte of the opcode)
    uint8_t svc_number = *pReturn_addr;

    printf("Svc number is : %d\n",svc_number);

    svc_number += 4;

    pBaseOfStackFrame[0] = svc_number;

}
