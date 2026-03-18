/*
 * disp7seg.h
 *
 *  Created on: Mar 12, 2026
 *      Author: janec
 */

#ifndef DISP7SEG_H_
#define DISP7SEG_H_

#include "stm32f4xx.h"
#include "tim.h"

void disp7seg_init(void);
void disp7seg_display_digit(uint8_t digit);
void disp7seg_display_number(uint8_t number);

#endif /* DISP7SEG_H_ */
