#include <stdint.h>

#define RCC_BASE 0x40021000

#define GPIOA_BASE 0x40010800
#define GPIOB_BASE 0x40010C00
#define GPIO_CRH_RR 0x44444444

#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE + 0x18)

#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_CRL *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)

#define GPIOB_CRH *(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_CRL *(volatile uint32_t *)(GPIOB_BASE + 0x00)
#define GPIOB_ODR *(volatile uint32_t *)(GPIOB_BASE + 0x0C)
#define GPIOB_IDR *(volatile uint32_t *)(GPIOB_BASE + 0x08)
#define GPIOB_BSSR *(volatile uint32_t *)(GPIOB_BASE + 0x10)

#define RCC_IOPAEN (1 << 2)
#define RCC_IOPBEN (1 << 3)

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
