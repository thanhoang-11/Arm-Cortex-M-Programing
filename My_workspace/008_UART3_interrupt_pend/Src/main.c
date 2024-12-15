
#include <stdint.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{

	uint32_t *pISPR1 = (uint32_t*)0XE000E204;
	*pISPR1 |= (1 << 7);

	uint32_t *pISER1 = (uint32_t*)0xE000E104;
	*pISER1 |= (1 << 7);

    /* Loop forever */
	for(;;);
}

void USART3_IRQHandler(void){
	printf("In USART3_IRQHandler\n");
}
