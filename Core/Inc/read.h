/*
 * read.h
 *
 *  Created on: Jul 1, 2024
 *      Author: admin
 */

#ifndef INC_READ_H_
#define INC_READ_H_


#include"stm32f1xx.h"


void read_pwm(int val_ch);
void direction(int running,uint32_t speed_CCR1,uint32_t speed_CCR2);
void Status_SS(void);
void convert(void);
void control(void);
extern uint32_t read1_out,read2_out,read3_out,read4_out,read5_out,read6_out,
				read7_out,read8_out,read9_out,read10_out,read11_out;

extern int flag_tim6;
extern float timer_delay;

#endif /* INC_READ_H_ */
