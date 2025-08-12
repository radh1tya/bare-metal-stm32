#include <stdint.h>
#include "../include/stm32.h"

#define GPIOB12 (1UL << 12)
#define GPIOA12 (1UL << 12)

void
hehe(void)
{
	for(unsigned int i = 0; i < 500000; ++i) {
		asm volatile ("nop");
	}
}

void
main(void)
{
	RCC_APB2ENR |= RCC_IOPAEN | RCC_IOPBEN;

	GPIOA_CRH = ((GPIO_CRH_RR & ~(0xFU << 16 )) | (0x3U << 16));
	
	GPIOB_CRH = ((GPIO_CRH_RR & ~(0xFU << 16 )) | (0x8U << 16));
	GPIOB_BSSR = GPIOB12;

	while(1) {
		if(!(GPIOB_IDR & GPIOB12)) {
			GPIOA_ODR |= GPIOA12;
		} else {
			GPIOA_ODR &= ~GPIOA12;
		}
	}
}
