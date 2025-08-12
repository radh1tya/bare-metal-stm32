#include <stdint.h>

#define RCC_BASE 0x40021000

#define GPIOA_BASE 0x40010800
#define GPIOB_BASE 0x40010C00
#define AFIO_BASE 0x40010000
#define EXTI_BASE 0x40010400

#define GPIO_CRH_RR 0x44444444
#define NVIC_ISER0 *(volatile uint32_t *)(0xE000E100)

#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE + 0x18)
#define AFIO_EXTICR4 *(volatile uint32_t *)(AFIO_BASE + 0x14)

#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_CRL *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)

#define GPIOB_CRH *(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_CRL *(volatile uint32_t *)(GPIOB_BSAE + 0x00)
#define GPIOB_ODR *(volatile uint32_t *)(GPIOB_BASE + 0x0C)
#define GPIOB_IDR *(volatile uint32_t *)(GPIOB_BASE + 0x08)

#define RCC_IOPAEN (1 << 2)
#define RCC_IOPBEN (1 << 3)
#define RCC_AFIOEN (1 << 0)

#define GPIOB12 (1UL << 12)
#define GPIOA12 (1UL << 12)

#define EXTI_IMR *(volatile uint32_t *)(EXTI_BASE + 0x00)
#define EXTI_RTSR *(volatile uint32_t *)(EXTI_BASE + 0x08)
#define EXTI_FTSR *(volatile uint32_t *)(EXTI_BASE + 0x0C)
#define EXTI_PR *(volatile uint32_t *)(EXTI_BASE + 0x14)

void
hehe(void)
{
	for(unsigned int i = 0; i < 500000; ++i) {
		asm volatile ("nop");
	}
}

void
exti_irqhandler(void) {
	if (EXTI_PR & GPIOB12) {
		EXTI_PR |= GPIOB12;
		GPIOA_ODR &= ~GPIOA12;
	}
}
	void
main(void)
{
	RCC_APB2ENR |= RCC_IOPAEN | RCC_IOPBEN | RCC_AFIOEN;

	GPIOA_CRH &= ~(0xF << 16);
	GPIOA_CRH |= (0x2 << 16);

	GPIOB_CRH &= ~(0xF << 16);
	GPIOB_CRH |= (0x4 << 16);

	AFIO_EXTICR4 &= ~(0xF << 0);
	AFIO_EXTICR4 |= (0x1 << 0);

	EXTI_IMR |= GPIOB12;
	EXTI_FTSR |= GPIOB12;

	NVIC_ISER0 |= (1 << 40 - 32);
	GPIOA_ODR |= GPIOA12;
	while(1)
	{
		exti_irqhandler();
	}

}
