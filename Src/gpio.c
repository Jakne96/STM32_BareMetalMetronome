/*
 * gpio.c
 *
 *  Created on: Mar 11, 2026
 *      Author: janec
 */

#include "gpio.h"
#define GPIOAEN (1U<<0)

void gpio_init(void){

	RCC->AHB1ENR |= GPIOAEN;

	//Buttons
	GPIOA->MODER &= ~(1U<<8);
	GPIOA->MODER &= ~(1U<<9);
	GPIOA->MODER &= ~(1U<<10);
	GPIOA->MODER &= ~(1U<<11);
	GPIOA->MODER &= ~(1U<<12);
	GPIOA->MODER &= ~(1U<<13);

	GPIOA->PUPDR |= (1U<<8);
	GPIOA->PUPDR &= ~(1U<<9);
	GPIOA->PUPDR |= (1U<<10);
	GPIOA->PUPDR &= ~(1U<<11);
	GPIOA->PUPDR |= (1U<<12);
	GPIOA->PUPDR &= ~(1U<<13);
	
	//Buzzer
	GPIOA->MODER |= (1U<<14);
	GPIOA->MODER &= ~(1U<<15);

}
