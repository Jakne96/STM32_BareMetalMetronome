#include <stdio.h>
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
	RESET_STATE = 48
}state;

extern uint16_t adc_raw_data[NUM_OF_CHANNELS];
state metronom_state = PLAY;

char new = 100;
//char *bpm = &new;


void TIM3_IRQHandler(void){
    		if(TIM3->SR & TIM_SR_UIF){
    			TIM3->SR &= ~(TIM_SR_UIF); //To ciekawe, ale jak zmieniam stan i updatuje ARR timera, to przerwanie przestaje działać
    			GPIOA->ODR ^= (1U<<7);
    		}
    	}

int main(void)
{
    /*Initialize debug UART*/
    uart_init(); //PA2
    /*Initialize ADC DMA*/
    adc_dma_init(); //PA0, PA1
    gpio_init(); //PA4 PA5 PA6 buttony, dioda PA7
    //Wyświetlacz 7segmentowy, PC0-PC6, PC7 digit 4, PC8 digit 3, PC9 digit 2
    //TODO: Napisać plik gpio.h do inicjalizacji przycisków i diody metronomu, napisać kod do wyświetlacza 7 segmentowego.
    //Przetestować po kolei czy wszystko działa, dioda, timer, ADC z DMA, I2C, Wyświetlacz


    tim2_init(); //Tim2 będzie od 7segmentowego a od diod będzie drugi timer
    tim3_init();
    i2c1_init();//PB8 i PB9
    //60 + ((adc_raw_data[0] - 760) / 18 ); //Wstępna formuła żeby wyliczać BPM.
    //Jeśli chce żeby tempo było takie jak ostatnie, no to musze zmieniać tempo tylko w trybie configu
    //Trzeba sobie też wypisać jakie tu są piny zajęte
    //3 GPIO od buttonów trzeba dodać
    //Trzeba dodać wyświetlacz, albo 7segmentowy, albo i2c, można też zrobić najpierw z 7segmentowymi albo z I2C, 7segmentowy to kwestia 10 GPIO
    //Czy oba timery zrobić na przerwaniach? No bo synchronizacja itd to mi sie tak wydaje że trzeba to zrobić dobrze.

    disp7seg_init();

    //To tak w ramach szablonu raczej
    NVIC_SetPriority(TIM3_IRQn, 0x03);
    NVIC_EnableIRQ(TIM3_IRQn);



    //checking buttons,
    //Ogólnie stany się zmieniają, tylko dioda przestaje świecić jak coś zmieniam, więc warto byłoby robić ten update tylko raz, można przemyśleć wykrywanie zmiany stanu
    //Update timera działa, ale trzeba zobaczyć czy poprawnie się to przelicza i zmienić formułę,
    //Zapisywanie do pamięci zrobić
    //Reset state zrobić
    //Jak przyjdzie analizator to też go ogarnąć potężnie i tu zczytać rzeczy.
    //Opisać jakoś bardziej zgrabnie ten kod potem


    //Czytanie z pamięci, prototyp, będziemy to testować albo jutro albo jak mnie najdzie.
    m24AA01_byte_read(BPM_MEMORY_ADDRESS, &new);


    while(1)
    {
    	//printf("Value from sensor one : %d \n\r ",60 + ((adc_raw_data[0] - 760) / 18 ));
    	//delay();
    	if((GPIOA->IDR & 112) < 112)
    		{
    		metronom_state = (GPIOA->IDR & 112);
    		tim3_update(new);
    		m24AA01_write(BPM_MEMORY_ADDRESS, 1, &new); //Prototyp zapisywania BPM do EEPROMu za każdym razem.

    		}

    	switch(metronom_state){
    	case PLAY:
    		disp7seg_display_number(new);
    		break;
    	case CONFIG:
    		disp7seg_display_number((60+ (adc_raw_data[0] - 760) / 18));
    		new = (60+ (adc_raw_data[0] - 760) / 18);

    		break;
    	case RESET_STATE: break;
    	default: break;
    	}


    }
}
