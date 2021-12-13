#ifndef GPIO_H
#define GPIO_H

#include <stm32f3xx.h>
#include <stm32f303x8.h>
#include <system_stm32f3xx.h>

void gpioConfig(void);
void gpioSetPin(uint16_t pin);
void gpioClearPin(uint16_t pin);
void gpioExtInterupt();
void gpioTogglePin(uint16_t pin);



#endif
