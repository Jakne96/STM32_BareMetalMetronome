/*
 * disp7seg.c
 *
 *  Created on: Mar 12, 2026
 *      Author: janec
 */

#include "disp7seg.h"

#define GPIOCEN (1U<<2)

uint8_t digits[10] =
{
		0b00111111, //0
		0b00000110, //1
		0b01011011, //2
		0b01001111, //3
		0b01100110, //4
		0b01101101, //5
		0b01111101, //6
		0b00000111, //7
		0b01111111, //8
		0b01101111 //9
};

void disp7seg_init(void)
{
	//Wyświetlacz 7segmentowy, PC0-PC6, PC7 digit 4, PC8 digit 3, PC9 digit 2
	RCC->AHB1ENR |= GPIOCEN;

	GPIOC->MODER |= (1U<<0);
	GPIOC->MODER &= ~(1U<<1);
	GPIOC->MODER |= (1U<<2);
	GPIOC->MODER &= ~(1U<<3);
	GPIOC->MODER |= (1U<<4);
	GPIOC->MODER &= ~(1U<<5);
	GPIOC->MODER |= (1U<<6);
	GPIOC->MODER &= ~(1U<<7);
	GPIOC->MODER |= (1U<<8);
	GPIOC->MODER &= ~(1U<<9);
	GPIOC->MODER |= (1U<<10);
	GPIOC->MODER &= ~(1U<<11);
	GPIOC->MODER |= (1U<<12);
	GPIOC->MODER &= ~(1U<<13);
	GPIOC->MODER |= (1U<<14);
	GPIOC->MODER &= ~(1U<<15);
	GPIOC->MODER |= (1U<<16);
	GPIOC->MODER &= ~(1U<<17);
	GPIOC->MODER |= (1U<<18);
	GPIOC->MODER &= ~(1U<<19);


}

void disp7seg_display_digit(uint8_t digit){
	GPIOC->ODR &= ~(0x7F << 0);
	GPIOC->ODR |= digits[digit];
}

void disp7seg_display_number(uint8_t number){
	uint8_t number_digits[3];

	number_digits[0] = number % 10;
	number_digits[1] = (number % 100)/10;
	number_digits[2] = number / 100;

	GPIOC->ODR |= (1U<<7);
	disp7seg_display_digit(number_digits[0]);
	delay();
	GPIOC->ODR &= ~(1U<<7);
	GPIOC->ODR |= (1U<<8);
	disp7seg_display_digit(number_digits[1]);
	delay();
	GPIOC->ODR &= ~(1U<<8);
	GPIOC->ODR |= (1U<<9);
	disp7seg_display_digit(number_digits[2]);
	delay();
	GPIOC->ODR &= ~(1U<<9);

}


