#include <stm32f3xx.h>
#include <stm32f303x8.h>
#include <system_stm32f3xx.h>

/*Function prototypes*/
void SystemClock_Config(void);
void GPIO_Config(void);
void Delay (uint32_t time);
void GPIO_SetPin(uint16_t pin);
void GPIO_ClearPin(uint16_t pin);



int main(void)
{
  /* Init var*/

  
  /*MCU init*/
  SystemClock_Config();
  GPIO_Config();
  
  while(1)
  {
		GPIOA->BSRR |= (1<<5); // Set the Pin PA5
		GPIO_ClearPin(GPIO_ODR_5);
		
////		GPIOA->ODR = 1<<5;
		GPIO_SetPin(GPIO_ODR_5);
//		GPIOA->BSRR |= (1<<5) <<16;  // Clear the Pin PA5
////		GPIOA->ODR &= ~(1<<5);
//		Delay (10000000);  // random delay
  }

}


/*Function definition*/
void Delay (uint32_t time)
{
	while (time--);  
}
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

void GPIO_Config(void)
{
//  RCC->AHBENR |= (1<<17);  // Enable the GPIOA clock IOPAEN: I/O port A clock enable
//  GPIOA->MODER |= (1<<0);  // pin PA5(bits 11:10) as Output (01)
//  GPIOA->OTYPER &= ~(1<<0);  // bit 5=0 --> Output push pull
//  GPIOA->OSPEEDR &= ~ (1<<1);  // Pin PA5 (bits 11:10) as Fast Speed (1:0)
//  GPIOA->PUPDR &= ~((1<<0) | (1<<1));  // Pin PA5 (bits 11:10) are 0:0 --> no pull up or pulldown

  GPIOA->MODER &= ~GPIO_MODER_MODER5;
  GPIOA->MODER |= GPIO_MODER_MODER5_0;
  
}

void GPIO_SetPin(uint16_t pin)
{
	GPIOA->ODR |= pin;
}

void GPIO_ClearPin(uint16_t pin)
{
	GPIOA->ODR &= ~pin;
}