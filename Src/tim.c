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
/*Enable clock access to tim2*/
	RCC->APB1ENR |=TIM2EN;
	    /*Set prescaler value*/
	    TIM2->PSC =  8000 - 1 ;
	    /*Set auto-reload value*/
	    TIM2->ARR =  10 - 1;
	    /*Clear counter*/
	    TIM2->CNT = 0;
	    /*Enable timer*/
	    TIM2->CR1 = CR1_CEN;
}

void tim2_stop(void){
		TIM2->CR1 &= ~(CR1_CEN);
} //Jeszcze jakiś update by się przydał albo coś takiego

void delay(void){
	/*Wait for UIF */
	while(!(TIM2->SR & SR_UIF)){}
	/*Clear UIF*/
	TIM2->SR &=~SR_UIF;
}

void tim3_init(void)
{
/*Enable clock access to tim2*/
	RCC->APB1ENR |=TIM3EN;
	    /*Set prescaler value*/
	    TIM3->PSC =  16000 - 1 ;
	    /*Set auto-reload value*/
	    TIM3->ARR =  500 - 1;
	    /*Clear counter*/
	    TIM3->CNT = 0;

	    TIM3->EGR |= EGR_UG;
	    TIM3->DIER |= DIER_UIE;
	    /*Enable timer*/
	    TIM3->CR1 = CR1_CEN;
}

void tim3_stop(void){
		TIM3->CR1 &= ~(CR1_CEN);
}

void tim3_update(uint8_t new_bpm)
{
	//if(new_bpm > 115) new_bpm = 115;
	//TIM3->CR1 &= ~CR1_CEN;
	//New values of arr
	TIM3->ARR = 0;
	TIM3-> ARR = ((-5*new_bpm)/2) + 650;
	TIM3->EGR |= EGR_UG;//Przy updacie trzeba to dać, bo inaczej timer może się zablokować i przerwanie może się nie generować
	//TIM3->CR1 = CR1_CEN;
}


