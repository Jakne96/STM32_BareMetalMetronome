/*
 * m24AA01.h
 *
 *  Created on: Mar 9, 2026
 *      Author: janec
 */

#ifndef M24AA01_H_
#define M24AA01_H_

void m24AA01_byte_read(char memory_cell, char* data1);
void m24AA01_write(char memory_cell, int n, char* data1);
void m24AA01_burst_read(char memory_cell, int n, char* data);

#endif /* M24AA01_H_ */
