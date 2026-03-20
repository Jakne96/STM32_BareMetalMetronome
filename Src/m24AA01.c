/*
 * m24AA01.c
 *
 *  Created on: Mar 9, 2026
 *      Author: janec
 */
#include "m24AA01.h"
#include "i2c.h"

#define M24AA01_SADDR 0x50
#define M24AA01_START_ADDRESS 0x00
#define M24AA01_END_ADDRESS 0x7F

void m24AA01_byte_read(char memory_cell, char* data){
	i2c1_byte_read(M24AA01_SADDR, memory_cell, data);
}

//Memory cell means starting memory cell
void m24AA01_write(char memory_cell, int n, char* data){
	i2c1_burst_write(M24AA01_SADDR, memory_cell, n, data);
}

void m24AA01_burst_read(char memory_cell, int n, char* data){
	i2c1_burst_read(M24AA01_SADDR, memory_cell, n, data);
}
