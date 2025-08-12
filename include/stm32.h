#define RCC_BASE 0x40021000
#define GPIOC_BASE 0x40011000
#define GPIOB_BASE 0x40010C00
#define GPIOA_BASE 0x40010800
#define GPIO_CRH_RR 0x44444444

/* APB2ENR: enable port to other GPIO */
#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE + 0x18)

/* GPIOC = {"CRL: 0 - 7", "CRH: 8 - 15"} */

#define GPIOA_CRL *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)
#define GPIOA_IDR *(volatile uint32_t *)(GPIOA_BASE + 0x08)
#define GPIOA_BSSR *(volatile uint32_t *)(GPIOA_BASE + 0x10)

#define GPIOB_CRL *(volatile uint32_t *)(GPIOB_BASE + 0x00)
#define GPIOB_CRH *(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_ODR *(volatile uint32_t *)(GPIOB_BASE + 0x0C)
#define GPIOB_IDR *(volatile uint32_t *)(GPIOB_BASE + 0x08)
#define GPIOB_BSSR *(volatile uint32_t *)(GPIOB_BASE + 0x10)

#define GPIOC_CRL *(volatile uint32_t *)(GPIOC_BASE + 0x00)
#define GPIOC_CRH *(volatile uint32_t *)(GPIOC_BASE + 0x04)
#define GPIOC_ODR *(volatile uint32_t *)(GPIOC_BASE + 0x0C)
#define GPIOC_IDR *(volatile uint32_t *)(GPIOC_BASE + 0x08)
#define GPIOC_BSSR *(volatile uint32_t *)(GPIOC_BASE + 0x10)

#define RCC_IOPAEN (1 << 2)
#define RCC_IOPBEN (1 << 3)
#define RCC_IOPCEN (1 << 4)
