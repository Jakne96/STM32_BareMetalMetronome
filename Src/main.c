#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc_dma.h"
#include "tim.h"
#include "i2c.h"
#include "m24AA01.h"
#include "disp7seg.h"
#include "gpio.h"

#define BPM_MEMORY_ADDRESS 0x10

typedef enum{
	PLAY = 96,
	CONFIG = 80,
//	RESET_STATE = 48 //Ten reset chyba wydupić, także też trzeba będzie wywalić inicjalizacje pinu do buttona
}state;

extern uint16_t adc_raw_data[NUM_OF_CHANNELS];
state metronom_state = PLAY; //Initial state

char new = 100; //Zastąpić nazwę

//ISR for metronome update
void TIM3_IRQHandler(void){ //W którym miejscu powinny być handlery?
    		if(TIM3->SR & TIM_SR_UIF){
    			TIM3->SR &= ~(TIM_SR_UIF);
    			GPIOA->ODR ^= (1U<<7);
    		}
    	}

int main(void)
{
    /*Initialize debug UART*/
    uart_init(); //PA2 //Uart był do debugowania ale przestał być potrzebny to można wywalić

    /*Initialize ADC DMA*/
    adc_dma_init(); //ADC for potentiometer for changing BPM
    gpio_init(); //PA4 PA5 PA6 buttony, dioda PA7


    tim2_init(); //Timer for refreshing 7 segment display
    tim3_init(); //Timer for metronome update

    i2c1_init(); //I2C for EEPROM memory

    disp7seg_init();

    NVIC_SetPriority(TIM3_IRQn, 0x03);
    NVIC_EnableIRQ(TIM3_IRQn);

    m24AA01_byte_read(BPM_MEMORY_ADDRESS, &new);

    //Filtering (to chyba w osobną funkcje można walnąć)
    uint16_t alpha = 12;  // 0 < alpha < 1
    uint16_t filtered = 0;
    uint16_t last_output = 0;
    uint16_t value = 0;

    while(1)
    {
    	//ADC i filtrowanie

    	filtered = filtered + (adc_raw_data[0] - filtered) / alpha;
    	value = (60 + (filtered - 760) / 40);

    	if (abs(value - last_output) > 1) {
    	    last_output = value;
    	}

    	//Looking for state changes //Funkcją może to można
    	if((GPIOA->IDR & 112) < 112)
    		{
    		metronom_state = (GPIOA->IDR & 112);
    		tim3_update(new);
    		m24AA01_write(BPM_MEMORY_ADDRESS, 1, &new); //Prototyp zapisywania BPM do EEPROMu za każdym razem.
    		}

    	//State machine
    	switch(metronom_state){
    	case PLAY:
    		disp7seg_display_number(new);
    		break;

    	case CONFIG:
    		disp7seg_display_number(value);
    		new = value;
    		break;

    	default: break;

    	}
    }
}







