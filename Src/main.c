#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx.h"
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
}state;

extern uint16_t adc_raw_data[NUM_OF_CHANNELS];

state metronom_state = PLAY; //Initial state

char current_bpm = 100;

//ADC Filtering Parameters
    uint16_t alpha = 12;
    uint16_t filtered = 0;
    uint16_t last_output = 0;
    uint16_t value = 0;

int main(void)
{
    adc_dma_init(); //ADC for potentiometer for changing BPM, PA1
    gpio_init(); //PA4 PA5 buttons, PA7 diode

    tim2_init(); //Timer for refreshing 7 segment display
    tim3_init(); //Timer for metronome update

    i2c1_init(); //I2C for EEPROM memory, PB8 PB9

    disp7seg_init(); //PC0-PC6 for segments PC7-PC9 for digit multiplexing

    NVIC_SetPriority(TIM3_IRQn, 0x03);
    NVIC_EnableIRQ(TIM3_IRQn);

    m24AA01_byte_read(BPM_MEMORY_ADDRESS, &current_bpm);

    while(1)
    {
    	//EMA Filter for ADC		
    	filtered = filtered + (adc_raw_data[0] - filtered) / alpha;
		
    	value = (60 + (filtered - 760) / 40);
		
		//Deadzone
    	if (abs(value - last_output) > 1) {
    	    last_output = value;
    	}

    	//Looking for state changes
    	if((GPIOA->IDR & 112) < 112)
    		{
    		metronom_state = (GPIOA->IDR & 112);
    		tim3_update(current_bpm);
    		m24AA01_write(BPM_MEMORY_ADDRESS, 1, &current_bpm); //Prototyp zapisywania BPM do EEPROMu za każdym razem.
    		}

    	switch(metronom_state){
    	case PLAY:
    		disp7seg_display_number(current_bpm);
    		break;
    	case CONFIG:
    		disp7seg_display_number(value);
    		current_bpm = value;
    		break;
    	default: break;

    	}
    }
}

	//ISR for metronome update
	void TIM3_IRQHandler(void)
{
    	if(TIM3->SR & TIM_SR_UIF){
    		TIM3->SR &= ~(TIM_SR_UIF);
    		GPIOA->ODR ^= (1U<<7);
    }
}






