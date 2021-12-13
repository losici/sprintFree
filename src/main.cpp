//#include <intrinsics.h>
#include <stm32f3xx.h>
#include <stm32f303x8.h>
#include <system_stm32f3xx.h>

#include "gpio.h"


#define F_CPU 8000000 // * MHz
//#define delay_us(usecs) __delay_cycles((F_CPU/1000000)  *(usecs))

/*Function prototypes*/
void SystemClock_Config(void);
void delay_ms(unsigned char millisecs);



int main(void)
{
  /* Init var*/

  
  /*MCU init*/
  SystemClock_Config();
  gpioConfig();
  gpioExtInterupt();
  
  
  while(1)
  {
		gpioClearPin(GPIO_ODR_5);
		for(int i = 0; i<50000; i++);
		gpioSetPin(GPIO_ODR_5);
		for(int i = 0; i<50000; i++);
  }
}


/*Function definition*/

//void delay_ms(unsigned char millisecs)
//{
//    while(millisecs--)
//    {
//      delay_us(1000);
//    }
//}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  	/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************
	
	
	********************************************************/
	RCC->CR |= 1<<0;  			//	ENABLE HSION 
	while (!(RCC->CR & (1<<1)));	// wait for the HSI to become Ready
	RCC->APB1ENR |= 1<<28;		// PWREN Set the POWER ENABLE CLOCK
	PWR->CR |= 3<<14; 			// SET Voltage Regulator
	FLASH->ACR = (1<<8) | (1<<9)| (1<<10)| (5<<0); //Configure the FLASH PREFETCH and the LATENCY Related Settings
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // enable clock on port A 
	GPIOA->MODER &= ~GPIO_MODER_MODER8;
	GPIOA->MODER |= GPIO_MODER_MODER8_1; //PA8 alternate function for MCO
	
	RCC->CFGR &= ~RCC_CFGR_MCO;
	RCC->CFGR |= RCC_CFGR_MCO_0; // MCO = PA8
  	RCC->CFGR |= RCC_CFGR_MCO_2;
	
//	RCC->CFGR &= ~(1<<)

	
//	RCC->CFGR |= (5<<24);  // MCO HSI 101 clock selected
//	RCC->CFGR &= ~(1<<25); //
//	RCC->CFGR |= (1<<26);  //
//	RCC->CFGR &= ~RCC_CFGR_SW; // HSI as a system clock
	RCC->CFGR &= ~RCC_CFGR_SW_HSI;
	while (!(RCC->CFGR & ~(RCC_CFGR_SWS_HSI)));
}

