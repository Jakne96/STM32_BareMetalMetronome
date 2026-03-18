/*
 * gpio.c
 *
 *  Created on: Mar 11, 2026
 *      Author: janec
 */

#include "gpio.h"
#define GPIOAEN (1U<<0)


void gpio_init(void){
//Trzeba zainicjować przyciski do zmiany stanów (PLAY, CONFIGURE, RESET), czyli trzy po prostu, ale to może jeszcze nie teraz, bo trzeba inne rzeczy zainicjować tam gdize już wiemy
//
	//Przyciski do zmiany stanów// PA3 PA4 PA5 //Trzeba zamienić na PA4 5 6 i dioda na 7 bo pa2 chyba koliduje z uartem
	    //Dioda do świecenia, później do zastąpienia buzzerem, PA6

	RCC->AHB1ENR |= GPIOAEN;

	//Buttony
	GPIOA->MODER &= ~(1U<<8);
	GPIOA->MODER &= ~(1U<<9);
	GPIOA->MODER &= ~(1U<<10);
	GPIOA->MODER &= ~(1U<<11);
	GPIOA->MODER &= ~(1U<<12);
	GPIOA->MODER &= ~(1U<<13);
	//Dioda
	GPIOA->MODER |= (1U<<14);
	GPIOA->MODER &= ~(1U<<15);

	GPIOA->PUPDR |= (1U<<8);
	GPIOA->PUPDR &= ~(1U<<9);
	GPIOA->PUPDR |= (1U<<10);
	GPIOA->PUPDR &= ~(1U<<11);
	GPIOA->PUPDR |= (1U<<12);
	GPIOA->PUPDR &= ~(1U<<13);
}
