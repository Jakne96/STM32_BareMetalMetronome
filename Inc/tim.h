/*
 * tim.h
 *
 *  Created on: Mar 11, 2026
 *      Author: janec
 */

#ifndef TIM_H_
#define TIM_H_

#include "stm32f4xx.h"

void tim2_init(void);
void tim2_stop(void);
void delay(void);

void tim3_init(void);
void tim3_update(uint8_t new_bpm);

#endif /* TIM_H_ */
