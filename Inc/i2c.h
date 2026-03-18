/*
 * i2c.h
 *
 *  Created on: Mar 5, 2026
 *      Author: janec
 */

#ifndef I2C_H_
#define I2C_H_

#include "stm32f4xx.h"



void i2c1_init(void);
void i2c1_byte_read(char saddr, char maddr, char* data);
void i2c1_burst_read(char saddr, char maddr, int n, char* data);
void i2c1_burst_write(char saddr, char maddr, int n, char* data);


#endif /* I2C_H_ */
