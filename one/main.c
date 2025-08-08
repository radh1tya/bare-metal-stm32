#include <stdint.h>
#define RCC_BASE 0x40021000
#define GPIOC_BASE 0x40011000
#define GPIOB_BASE 0x40010C00
#define GPIOA_BASE 0x40010800
#define GPIO_CRH_RR 0x44444444

/* APB2ENR -> enable port to other GPIO */
#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE + 0x18)
#define GPIOC_CRH *(volatile uint32_t *)(GPIOC_BASE + 0x04)
#define GPIOC_ODR *(volatile uint32_t *)(GPIOC_BASE + 0x0C)
#define GPIOB_CRH *(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_ODR *(volatile uint32_t *)(GPIOB_BASE + 0x0C)
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)

#define RCC_IOPCEN (1 << 4)
#define RCC_IOPBEN (1 << 3)
#define RCC_IOPAEN (1 << 2)

#define GPIOC13 (1UL << 13)
#define GPIOA10 (1UL << 10)
#define GPIOA9 (1UL << 9)
#define GPIOB9 (1UL << 9)

void ilwir(void)
{
    for (unsigned int i = 0; i < 500000; ++i) 
        asm volatile ("nop");
}

void main(void)
{
    /* enable GPIO clocks */
    RCC_APB2ENR |= RCC_IOPCEN;
    RCC_APB2ENR |= RCC_IOPBEN;
    RCC_APB2ENR |= RCC_IOPAEN;
    
    /*
       some note you should to know
       0x4444 4444 = 0100 0100 0100 0100 0100 0100 0100 0100
       so, each port has 0100 which stands for CNF=01, MODE=00 (ref 171)
    */
    
    GPIOC_CRH = ((GPIO_CRH_RR & ~(0xfU << 20)) | (0x3U << 20));
    
    GPIOB_CRH = ((GPIO_CRH_RR & ~(0xFU << 4)) | (0x3U << 4));
    
    GPIOA_CRH = ((GPIO_CRH_RR & ~(0xfU << 4)) | (0x3U << 4));
	while(1) {
        GPIOC_ODR |= GPIOC13;
        ilwir();
        GPIOC_ODR &= ~GPIOC13;
        ilwir();
        
        GPIOB_ODR |= GPIOB9;
        ilwir();
        GPIOB_ODR &= ~GPIOB9;
        ilwir();
        
        GPIOA_ODR |= GPIOA9;
        ilwir();
        GPIOA_ODR &= ~GPIOA9;
        ilwir();
		/*
        GPIOA_ODR |= GPIOA10;
        ilwir();
        GPIOA_ODR &= ~GPIOA10;
        ilwir();
		*/
    }
}
