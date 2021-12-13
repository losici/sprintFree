#include "gpio.h"

void gpioConfig(void)
{
//  RCC->AHBENR |= (1<<17);  // Enable the GPIOA clock IOPAEN: I/O port A clock enable
//  GPIOA->MODER |= (1<<0);  // pin PA5(bits 11:10) as Output (01)
//  GPIOA->OTYPER &= ~(1<<0);  // bit 5=0 --> Output push pull
//  GPIOA->OSPEEDR &= ~ (1<<1);  // Pin PA5 (bits 11:10) as Fast Speed (1:0)
//  GPIOA->PUPDR &= ~((1<<0) | (1<<1));  // Pin PA5 (bits 11:10) are 0:0 --> no pull up or pulldown

  GPIOA->MODER &= ~GPIO_MODER_MODER5;
  GPIOA->MODER |= GPIO_MODER_MODER5_0;
  GPIOA->MODER &= ~GPIO_MODER_MODER0;
  //GPIOA->MODER |= GPIO_MODER_MODER0_0;
  GPIOA->MODER &= ~GPIO_MODER_MODER1;
  GPIOA->MODER |= GPIO_MODER_MODER0_1;
  
}

void gpioSetPin(uint16_t pin)
{
	GPIOA->BSRR &= ~pin;
	GPIOA->BSRR |= pin;
  	//GPIOA->ODR |= pin;
}

void gpioClearPin(uint16_t pin)
{
  	GPIOA->BSRR &= ~pin;
	GPIOA->BSRR |= ((pin )<<16)& 0xFFFF0000;
	//GPIOA->ODR &= ~pin;
}

void gpioTogglePin(uint16_t pin)
{

  	GPIOA->ODR ^= pin;
}

void gpioExtInterupt(void)
{
  	unsigned int prova = EXTI_EMR_MR0;
	
	EXTI->EMR |= EXTI_EMR_MR0 ;
	EXTI->RTSR|= EXTI_RTSR_TR0;
	
}

extern "C" void EXTI0_IRQHandler(void)
{
  	gpioSetPin(GPIO_ODR_1);
}
