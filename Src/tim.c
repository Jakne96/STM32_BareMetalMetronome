/*
 * tim.c
 *
 *  Created on: Mar 11, 2026
 *      Author: janec
 */

#include "tim.h"
#define TIM2EN (1U<<0)
#define TIM3EN (1u<<1)
#define CR1_CEN (1U<<0)
#define SR_UIF (1U<<0)
#define EGR_UG (1U<<0)
#define DIER_UIE (1U<<0)

void tim2_init(void)
{
	RCC->APB1ENR |=TIM2EN;

	TIM2->PSC =  8000 - 1 ;
	TIM2->ARR =  10 - 1;
	TIM2->CNT = 0;
	TIM2->CR1 = CR1_CEN;
}

void delay(void){
	while(!(TIM2->SR & SR_UIF)){}
	TIM2->SR &=~SR_UIF;
}

void tim3_init(void)
{
		RCC->APB1ENR |=TIM3EN;
	    TIM3->PSC =  16000 - 1 ;
	    TIM3->ARR =  500 - 1;
	    TIM3->CNT = 0;

	    TIM3->EGR |= EGR_UG;
	    TIM3->DIER |= DIER_UIE;
	    TIM3->CR1 = CR1_CEN;
}

void tim3_update(uint8_t new_bpm)
{
	TIM3->ARR = 0;
	TIM3->ARR = ((-5*new_bpm)/2) + 650;
	TIM3->EGR |= EGR_UG;//Event update to prevent timer from suspending due to ARR change
}


