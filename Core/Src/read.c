/*
 * read.c
 *
 *  Created on: Jul 1, 2024
 *      Author: admin
 */

#include"read.h"
#include"main.h"
#include"stdio.h"

extern TIM_HandleTypeDef htim1;

uint32_t read1_out, read2_out, read3_out, read4_out, read5_out, read6_out,
		 read7_out, read8_out, read9_out, read10_out,read11_out;
uint32_t read2_check,read1_check;
uint32_t speed_CCR1, speed_CCR2;

int DIR,DIR_CHECK,save,val,limit_value;
int active_case =0;
int running;


typedef struct
{
uint32_t start;
uint32_t end;
uint32_t out;
} read;
read read_1,read_2,read_3,read_4,read_5,read_6,read_7,read_8,read_9,read_10,read_11;

int first_filter = 0;
float alpha = 0.5;

uint16_t map(uint16_t x,uint16_t In_Max,uint16_t In_Min,uint16_t Out_Max,uint16_t Out_Min )
{
	return(((x-In_Min)*(Out_Max-Out_Min)/(In_Max-In_Min))+Out_Min);
}

uint32_t filter_ch(uint32_t in)
{
	uint32_t out = alpha*first_filter+(1-alpha)*in;
	first_filter = out;
	return out;
}
void read_pwm(int val_ch)
	{
		switch(val_ch)
		{
			case 1:
					if(HAL_GPIO_ReadPin(CH1_GPIO_Port, CH1_Pin)==1)
					{
						read_1.start = htim1.Instance->CNT;
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH1_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH1_GPIO_Port, &GPIO_InitStruct);
					}
					else
					{
						read_1.end = htim1.Instance->CNT;

						if(read_1.start > read_1.end)
						{
							read_1.out = 65535 - read_1.start + read_1.end;
						}
						else
						{
							read_1.out = read_1.end - read_1.start;
						}
						if(read_1.out > 61200)
						{
							read_1.out = 61200;
						}
						else if(read_1.out < 7000)
						{
							read_1.out = 7000;
						}
						else if(40000 <= read_1.out && read_1.out <= 45000)
						{
							read_1.out = 43200;
						}

						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH1_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH1_GPIO_Port, &GPIO_InitStruct);
					}
			break;
			case 2:
					if(HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin)==1)
					{
						read_2.start = htim1.Instance->CNT;
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH2_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH2_GPIO_Port, &GPIO_InitStruct);
					}
					else
					{
						read_2.end = htim1.Instance->CNT;

						if(read_2.start > read_2.end)
						{
							read_2.out = 65535 - read_2.start + read_2.end;
						}
						else
						{
							read_2.out = read_2.end - read_2.start;
						}
						if(read_2.out >= 61200)
						{
							read_2.out = 61200;
						}
						else if(read_2.out <= 7000)
						{
							read_2.out = 7000;
						}
						else if(40000 < read_2.out && read_2.out < 45000)
						{
							read_2.out = 43250;
						}
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH2_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH2_GPIO_Port, &GPIO_InitStruct);
					}
			break;
			case 3:
				if(HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin)==1)
					{
						read_3.start = htim1.Instance->CNT;
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH3_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH3_GPIO_Port, &GPIO_InitStruct);
					}
					else
					{
						read_3.end = htim1.Instance->CNT;

						if(read_3.start > read_3.end)
						{
							read_3.out = 65535 - read_3.start + read_3.end;
						}
						else
						{
							read_3.out = read_3.end - read_3.start;
						}
						if(read_3.out >= 61200)
						{
							read_3.out = 61200;

						}
						else if(read_3.out <= 7000)
						{
							read_3.out = 7000;

						}
						else if(40000 <= read_3.out && read_3.out <= 45000)
						{
							read_3.out = 41300;
						}
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH3_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH3_GPIO_Port, &GPIO_InitStruct);
					}
			break;
			case 4:
				if(HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin)==1)
					{
						read_4.start = htim1.Instance->CNT;
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH4_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH4_GPIO_Port, &GPIO_InitStruct);
					}
				else
					{
						read_4.end = htim1.Instance->CNT;

						if(read_4.start > read_4.end)
						{
							read_4.out = 65535 - read_4.start + read_4.end;
						}
						else
						{
							read_4.out = read_4.end - read_4.start;
						}
						if(read_4.out > 61200)
						{
							read_4.out = 61200;
						}
						else if(read_4.out < 25000)
						{
							read_4.out = 25000;
						}
						else if(40000 <= read_4.out && read_4.out <= 45000)
						{
							read_4.out = 42900;
						}
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH4_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH4_GPIO_Port, &GPIO_InitStruct);
					}
					break;
			case 5:
				if(HAL_GPIO_ReadPin(CH5_GPIO_Port, CH5_Pin)==1)
					{
						read_5.start = htim1.Instance->CNT;
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH5_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH5_GPIO_Port, &GPIO_InitStruct);
					}
				else
					{
						read_5.end = htim1.Instance->CNT;

						if(read_5.start > read_5.end)
						{
							read_5.out = 65535 - read_5.start + read_5.end;
						}
						else
						{
							read_5.out = read_5.end - read_5.start;
						}
						if(read_5.out > 61200)
						{
							read_5.out = 61200;
						}
						else if(read_5.out < 7000)
						{
							read_5.out = 7000;
						}
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH5_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH5_GPIO_Port, &GPIO_InitStruct);
					}
					break;
			case 6:
				if(HAL_GPIO_ReadPin(CH6_GPIO_Port, CH6_Pin)==1)
					{
						read_6.start = htim1.Instance->CNT;
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH6_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH6_GPIO_Port, &GPIO_InitStruct);
					}
				else
					{
						read_6.end = htim1.Instance->CNT;
					// tinh do rong xung
						if(read_6.start > read_6.end)
						{
							read_6.out = 65535 - read_6.start + read_6.end;
						}
						else
						{
							read_6.out = read_6.end - read_6.start;
						}
					// gioi han 2 dau gia tri
						if(read_6.out > 13700)
						{
							read_6.out = 13700;
						}
						else if(read_6.out < 6900)
						{
							read_6.out = 6900;
						}
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH6_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH6_GPIO_Port, &GPIO_InitStruct);
					}
					break;
			case 7:
					if(HAL_GPIO_ReadPin(CH7_GPIO_Port, CH7_Pin)==1)
					{
						read_7.start = htim1.Instance->CNT;
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH7_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH7_GPIO_Port, &GPIO_InitStruct);
					}
					else
					{
						read_7.end = htim1.Instance->CNT;

						if( read_7.start > read_7.end)
						{
							read_7.out = 65535 - read_7.start + read_7.end;
						}
						else
						{
							read_7.out = read_7.end - read_7.start;
						}
						if(read_7.out > 13500)
						{
							read_7.out = 13500;
						}
						else if(read_7.out < 7140)
						{
							read_7.out = 7140;
						}
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH7_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH7_GPIO_Port, &GPIO_InitStruct);
					}
					break;
			case 8:
					if(HAL_GPIO_ReadPin(CH8_GPIO_Port, CH8_Pin)==1)
					{
						read_8.start = htim1.Instance->CNT;
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH8_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH8_GPIO_Port, &GPIO_InitStruct);
					}
					else
					{
						read_8.end = htim1.Instance->CNT;

						if( read_8.start > read_8.end)
						{
							read_8.out = 65535 - read_8.start + read_8.end;
						}
						else
						{
							read_8.out = read_8.end - read_8.start;
						}
						if(read_8.out > 12500)
						{
							read_8.out = 12500;
						}
						else if(read_8.out < 6160)
						{
							read_8.out = 6160;
						}
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH8_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH8_GPIO_Port, &GPIO_InitStruct);
					}
					break;
			case 9:
					if(HAL_GPIO_ReadPin(CH9_GPIO_Port, CH9_Pin)==1)
					{
						read_9.start = htim1.Instance->CNT;
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH9_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH9_GPIO_Port, &GPIO_InitStruct);
					}
					else
					{
						read_9.end = htim1.Instance->CNT;

						if( read_9.start > read_9.end)
						{
							read_9.out = 65535 - read_9.start + read_9.end;
						}
						else
						{
							read_9.out = read_9.end - read_9.start;
						}
						if(read_9.out > 12500)
						{
							read_9.out = 12500;
						}
						else if(read_9.out < 6200)
						{
							read_9.out = 26500;
						}
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH9_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH9_GPIO_Port, &GPIO_InitStruct);
					}
					break;
			case 10:
					if(HAL_GPIO_ReadPin(CH10_GPIO_Port, CH10_Pin)==1)
					{
						read_10.start = htim1.Instance->CNT;
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH10_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH10_GPIO_Port, &GPIO_InitStruct);
					}
					else
					{
						read_10.end = htim1.Instance->CNT;

						if( read_10.start > read_10.end)
						{
							read_10.out = 65535 - read_10.start + read_10.end;
						}
						else
						{
							read_10.out = read_10.end - read_10.start;
						}
						//loc nhieu
						if(read_10.out > 60000)
						{
							read_10.out = 60000;
						}
						else if(read_10.out < 6200)
						{
							read_10.out = 6200;
						}
						else if(41000 <= read_10.out && read_10.out <= 42000)
						{
							read_10.out = 42100;
						}
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH10_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH10_GPIO_Port, &GPIO_InitStruct);
					}
					break;
			case 11:
					if(HAL_GPIO_ReadPin(CH11_GPIO_Port, CH11_Pin)==1)
					{
						read_11.start = htim1.Instance->CNT;
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH11_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH11_GPIO_Port, &GPIO_InitStruct);
					}
					else
					{
						read_11.end = htim1.Instance->CNT;

						if( read_11.start > read_11.end)
						{
							read_11.out = 65535 - read_11.start + read_11.end;
						}
						else
						{
							read_11.out = read_11.end - read_11.start;
						}
						if(read_11.out > 60000)
						{
							read_11.out = 60000;
						}
						else if(read_11.out < 6100)
						{
							read_11.out = 6100;
						}
						else if(41000 <= read_11.out && read_11.out <= 42000)
						{
							read_11.out = 42100;
						}
						GPIO_InitTypeDef GPIO_InitStruct;
						GPIO_InitStruct.Pin = CH11_Pin;
						GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						HAL_GPIO_Init(CH11_GPIO_Port, &GPIO_InitStruct);
					}
					break;
		}
	}

void convert(void)
{
	/*
	//khi joystick bị lệch thì ngưng
	if(read_1.out != 43200 && read_2.out != 43250)
	{
		limit_value = 1;
	}
	else
	{
		limit_value = 0;
	}
	if(limit_value == 0)
	{
		//ch1 trai phai banh
			if(read_1.out >= 43200)
			{
				read1_out = map(read_1.out,43200,61200,0,28700);
				val = 1;
			}
			else if(read_1.out <= 43200)
			{
				read1_out = map(read_1.out,7000,43200,28700,0);
				val = 2;
			}
			else
			{
				read1_out = 0;
			}

			//ch2 tien lui banh
			if(read_2.out >= 43250)
			{
				read2_out = map(read_2.out,43250,61200,0,28700);
				val = 3;
			}
			else if(read_2.out <= 43250)
			{
				read2_out = map(read_2.out,7000,43250,28700,0);
				val = 4;
			}
			else
			{
				read2_out = 0;
			}
	}
	else
	{
		read1_out = 0;
		read2_out = 0;
	}
*/
//////// khi joystick lệch thì chạy theo hướng lệch ít +++++ start +++++++++///////////////
	//ch1 trai phai banh
	if(read_1.out >= 43200)
	{
		read1_out = map(read_1.out,43200,61200,0,28700);
		val = 1;
	}
	else if(read_1.out <= 43200)
	{
		read1_out = map(read_1.out,7000,43200,28700,0);
		val = 2;
	}
	else
	{
		read1_out = 0;
	}

	//ch2 tien lui banh
	if(read_2.out >= 43250)
	{
		read2_out = map(read_2.out,43250,61200,0,28700);
		val = 3;
	}
	else if(read_2.out <= 43250)
	{
		read2_out = map(read_2.out,7000,43250,28700,0);
		val = 4;
	}
	else
	{
		read2_out = 0;
	}
	if(read_1.out != 43200 && read_2.out != 43250)
	{
		limit_value = 1;
	}
	else
	{
		limit_value = 0;
	}
	//||((read_1.out>read_2.out)&&(val == 2)&&(val == 4))||
//	((read1_out<read2_out)&&(val == 2)&&(val == 3))||((read1_out<read2_out)&&(val == 1)&&(val == 3))
	if(limit_value == 1)
	{
		if(((val ==4)&&(read_1.out>read_2.out)&&(read_1.out<61200)) ||((val ==3)&&(read_1.out<read_2.out)&&(read_1.out>7000)))
		{
			read1_out = 0;
		}
		else if(read1_out!=0)
		{
			read2_out = 0;
		}
		else if(read_1.out == 7000 && read_2.out==7000)
		{
			read1_out = 0;
			read2_out = 0;
			val =17;
		}
		else if(read_1.out == 61200 && read_2.out == 7000)
		{
			read1_out = 0;
			read2_out = 0;
			val = 18;
		}
		else if (read_1.out == 7000 && read_2.out ==61200)
		{
			read1_out = 0;
			read2_out = 0;
			val = 19;
		}
		else if (read_1.out == 61200 && read_2.out ==61200)
		{
			read1_out = 0;
			read2_out = 0;
			val = 20;
		}
	}

	//////////////////++++++end+++++/////////////////
	//ch3 gimbal
	if(read_3.out >= 41300)
	{
		read3_out = map(read_3.out,41300,61200,0,14300);

	}
	else if(read_3.out <= 41300)
	{
		read3_out = map(read_3.out,21600,41300,14300,0);

	}
	else
	{
		read3_out = 0;
	}

	//ch4 gimbal
	if(read_4.out >= 42900)
	{
		read4_out = map(read_4.out,42900,61200,0,14300);

	}
	else if(read_4.out <= 42900)
	{
		read4_out = map(read_4.out,25000,42900,14300,0);

	}
	else
	{
		read4_out = 0;
	}

	//ch5 volume toc do choi
	read5_out = map(read_5.out,7000,61200,0,14300);

	 //ch6 switch luu vi tri
	read6_out = read_6.out;
	if(read6_out > 7500)
	{
		save = 1;
	}
	else
	{
		save = 0;
	}

	//ch7 ngat che do an toan
	read7_out = read_7.out;
	if(read7_out > 7500)
	{
		val = 5;
	}

//	else
//	{
//		val = 6;
//	}

	//ch8 den

 	read8_out = read_8.out;
	if(read8_out < 7500)
	{
		val = 7;
	}
	else
	{
		val = 8;
	}

	//ch9 nuoc

 	read9_out = read_9.out;
	if(read9_out < 7500)
	{
		val = 9;
	}
	else
	{
		val = 10;
	}

	// ch10 choi truoc

	read10_out = read_10.out;
	if(read_10.out >= 42100)
	{
		val = 11;
	}
	else if(read_10.out <= 42100)
	{
		val = 12;
	}
	else
	{
		val = 13;
	}

	 //ch11 choi sau

	read11_out = read_11.out;
	if(read_11.out >= 42100)
	{
		val = 14;
	}
	else if(read_11.out <= 42100)
	{
		val = 15;
	}
	else
	{
		val = 16;
	}
}
void direction(int running,uint32_t speed_CCR1,uint32_t speed_CCR2)
{
	//tien
	if(running == 1)
	{
		TIM3 -> CCR1 = speed_CCR1; // DC TRAI
		TIM3 -> CCR2 = speed_CCR2; // DC PHAI
		HAL_GPIO_WritePin(F_R_1A_GPIO_Port, F_R_1A_Pin, RESET);
		HAL_GPIO_WritePin(F_R_1B_GPIO_Port, F_R_1B_Pin, RESET);

	}
	//lui
	else if(running == 2)
	{
		TIM3 -> CCR1 = speed_CCR1; // DC TRAI
		TIM3 -> CCR2 = speed_CCR2; // DC PHAI
		HAL_GPIO_WritePin(F_R_1A_GPIO_Port, F_R_1A_Pin, SET);
		HAL_GPIO_WritePin(F_R_1B_GPIO_Port, F_R_1B_Pin, SET);
	}
	// xoay trai
	else if(running == 3)
	{
		TIM3 -> CCR1 = speed_CCR1; // DC TRAI
		TIM3 -> CCR2 = speed_CCR2; // DC PHAI
		HAL_GPIO_WritePin(F_R_1A_GPIO_Port, F_R_1A_Pin, SET);
		HAL_GPIO_WritePin(F_R_1B_GPIO_Port, F_R_1B_Pin, RESET);
	}
	// xoay phai
	else if(running == 4)
	{
		TIM3 -> CCR1 = speed_CCR1; // DC TRAI
		TIM3 -> CCR2 = speed_CCR2; // DC PHAI
		HAL_GPIO_WritePin(F_R_1A_GPIO_Port, F_R_1A_Pin, RESET);
		HAL_GPIO_WritePin(F_R_1B_GPIO_Port, F_R_1B_Pin, SET);
	}
}

void control(void)
{
	// check signal TX
	if(read_1.start != read1_check) // có tins hiệu
	{
		 read1_check = read_1.start;
	}
	else
	{
	   read_1.start = 0;
	}

	// hoat dong
	if(read_1.start !=0 && SS1_Pin == 1 && SS2_Pin == 1 && SS3_Pin == 1 && SS4_Pin == 1)
	{
		//enable đc
		HAL_GPIO_WritePin(EN_1A_GPIO_Port, EN_1A_Pin, RESET);
		HAL_GPIO_WritePin(EN_1B_GPIO_Port, EN_1B_Pin, RESET);
		HAL_GPIO_WritePin(EN_2A_GPIO_Port, EN_2A_Pin, RESET);
		HAL_GPIO_WritePin(EN_2B_GPIO_Port, EN_2B_Pin, RESET);

		HAL_GPIO_WritePin(BRK_1A_GPIO_Port, BRK_1A_Pin, RESET);
		HAL_GPIO_WritePin(BRK_1B_GPIO_Port, BRK_1B_Pin, RESET);
		HAL_GPIO_WritePin(BRK_2A_GPIO_Port, BRK_2A_Pin, RESET);
		HAL_GPIO_WritePin(BRK_2B_GPIO_Port, BRK_2B_Pin, RESET);

//		TIM2 -> CCR2 = read3_out; // GIMBAL
//		TIM2 -> CCR3 = read4_out; // GIMBAL
////		TIM2 -> CCR4 = read5_out; // GIMBAL
//
//		TIM3 -> CCR1 = read1_out; // DC TRAI
//		TIM3 -> CCR2 = read2_out; // DC PHAI
//		TIM3 -> CCR3 = read5_out; // DC CHOI


		//	save location joystick
		if(save ==1)
		{
		  if(read2_out != read2_check && DIR_CHECK != DIR)
		  {
			  read2_out = read2_check;
			  DIR = DIR_CHECK;
		  }

		}
		else
		{
		  read2_check = read2_out ;
		  DIR_CHECK = DIR;
		}
		switch (val)
		{
		// xoay trai tai cho
			case 1:
				direction(3,read1_out,read1_out);

		// xoay phai tai cho
			case 2:
				direction(4,read2_out,read2_out);

		// chay tien
			case 3:
				TIM3 -> CCR1 = read2_check; // DC TRAI
				TIM3 -> CCR2 = read2_check; // DC PHAI
				HAL_GPIO_WritePin(F_R_1A_GPIO_Port, F_R_1A_Pin, DIR_CHECK);
				HAL_GPIO_WritePin(F_R_1B_GPIO_Port, F_R_1B_Pin, DIR_CHECK);

		// chay lui
			case 4:
				TIM3 -> CCR1 = read2_check; // DC TRAI
				TIM3 -> CCR2 = read2_check; // DC PHAI
				HAL_GPIO_WritePin(F_R_1A_GPIO_Port, F_R_1A_Pin, DIR_CHECK);
				HAL_GPIO_WritePin(F_R_1B_GPIO_Port, F_R_1B_Pin, DIR_CHECK);

		// bat an toan
//			case 5:
//				if(SS1_Pin == 1 && SS2_Pin == 0 && SS3_Pin == 0 && SS4_Pin == 0)
//				{
//					HAL_GPIO_WritePin(BRK_1A_GPIO_Port, BRK_1A_Pin, RESET);
//					HAL_GPIO_WritePin(BRK_1B_GPIO_Port, BRK_1B_Pin, RESET);
//					HAL_Delay(500);
//					TIM3 -> CCR1 = 100; // DC TRAI
////					TIM3 -> CCR2 = 100; // DC PHAI
//					HAL_GPIO_WritePin(F_R_1A_GPIO_Port, F_R_1A_Pin, RESET);
//					HAL_GPIO_WritePin(F_R_1B_GPIO_Port, F_R_1B_Pin, SET);
//				}
//
//				else if(SS1_Pin == 0 && SS2_Pin == 1 && SS3_Pin == 0 && SS4_Pin == 0)
//				{
//					HAL_GPIO_WritePin(BRK_1A_GPIO_Port, BRK_1A_Pin, RESET);
//					HAL_GPIO_WritePin(BRK_1B_GPIO_Port, BRK_1B_Pin, RESET);
//					HAL_Delay(500);
////					TIM3 -> CCR1 = 100; // DC TRAI
//					TIM3 -> CCR2 = 100; // DC PHAI
//					HAL_GPIO_WritePin(F_R_1A_GPIO_Port, F_R_1A_Pin, SET);
//					HAL_GPIO_WritePin(F_R_1B_GPIO_Port, F_R_1B_Pin, RESET);
//				}
//
//				else if(SS1_Pin == 1 && SS2_Pin == 1 && SS3_Pin == 0 && SS4_Pin == 0)
//				{
//					HAL_GPIO_WritePin(BRK_1A_GPIO_Port, BRK_1A_Pin, RESET);
//					HAL_GPIO_WritePin(BRK_1B_GPIO_Port, BRK_1B_Pin, RESET);
//					HAL_Delay(500);
//					TIM3 -> CCR1 = 100; // DC TRAI
//					TIM3 -> CCR2 = 100; // DC PHAI
//					HAL_GPIO_WritePin(F_R_1A_GPIO_Port, F_R_1A_Pin, RESET);
//					HAL_GPIO_WritePin(F_R_1B_GPIO_Port, F_R_1B_Pin, RESET);
//				}
//
//				else if(SS1_Pin == 0 && SS2_Pin == 0 && SS3_Pin == 1 && SS4_Pin == 0)
//				{
//					HAL_GPIO_WritePin(BRK_1A_GPIO_Port, BRK_1A_Pin, RESET);
//					HAL_GPIO_WritePin(BRK_1B_GPIO_Port, BRK_1B_Pin, RESET);
//					HAL_Delay(500);
//					TIM3 -> CCR1 = 100; // DC TRAI
////					TIM3 -> CCR2 = 100; // DC PHAI
//					HAL_GPIO_WritePin(F_R_1A_GPIO_Port, F_R_1A_Pin, SET);
//					HAL_GPIO_WritePin(F_R_1B_GPIO_Port, F_R_1B_Pin, RESET);
//				}
//
//				else if(SS1_Pin == 0 && SS2_Pin == 0 && SS3_Pin == 0 && SS4_Pin == 1)
//				{
//					HAL_GPIO_WritePin(BRK_1A_GPIO_Port, BRK_1A_Pin, RESET);
//					HAL_GPIO_WritePin(BRK_1B_GPIO_Port, BRK_1B_Pin, RESET);
//					HAL_Delay(500);
////					TIM3 -> CCR1 = 100; // DC TRAI
//					TIM3 -> CCR2 = 100; // DC PHAI
//					HAL_GPIO_WritePin(F_R_1A_GPIO_Port, F_R_1A_Pin, SET);
//					HAL_GPIO_WritePin(F_R_1B_GPIO_Port, F_R_1B_Pin, SET);
//				}
//
//				else if(SS1_Pin == 0 && SS2_Pin == 0 && SS3_Pin == 1 && SS4_Pin == 1)
//				{
//					HAL_GPIO_WritePin(BRK_1A_GPIO_Port, BRK_1A_Pin, RESET);
//					HAL_GPIO_WritePin(BRK_1B_GPIO_Port, BRK_1B_Pin, RESET);
//					HAL_Delay(500);
//					TIM3 -> CCR1 = 100; // DC TRAI
//					TIM3 -> CCR2 = 100; // DC PHAI
//					HAL_GPIO_WritePin(F_R_1A_GPIO_Port, F_R_1A_Pin, SET);
//					HAL_GPIO_WritePin(F_R_1B_GPIO_Port, F_R_1B_Pin, SET);
//				}
//			// Tat an toan
////			case 6:
//////				HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//////				HAL_Delay(200);
////
//			// Bat tat den
//			case 7:
//				HAL_GPIO_WritePin(LIGHT_GPIO_Port, LIGHT_Pin, SET);
//			case 8:
//				HAL_GPIO_WritePin(LIGHT_GPIO_Port, LIGHT_Pin, RESET);
//
//			// Bat tat nuoc
//			case 9:
//				HAL_GPIO_WritePin(SLN_GPIO_Port, SLN_Pin, SET);
//			case 10:
//				HAL_GPIO_WritePin(SLN_GPIO_Port, SLN_Pin, RESET);
//
//			//Choi truoc
//			case 11:
//				HAL_GPIO_WritePin(F_R_2A_GPIO_Port, F_R_2A_Pin, SET);
//			case 12:
//				HAL_GPIO_WritePin(F_R_2A_GPIO_Port, F_R_2A_Pin, RESET);
//			case 13:
//				HAL_GPIO_WritePin(EN_2A_GPIO_Port, EN_2A_Pin, SET);
//
//			//Choi sau
//			case 14:
//				HAL_GPIO_WritePin(F_R_2B_GPIO_Port, F_R_2B_Pin, SET);
//			case 15:
//				HAL_GPIO_WritePin(F_R_2B_GPIO_Port, F_R_2B_Pin, RESET);
//			case 16:
//				HAL_GPIO_WritePin(EN_2B_GPIO_Port, EN_2B_Pin, SET);
//			case17:

		}
	}
	else
	{
		HAL_GPIO_WritePin(EN_1A_GPIO_Port, EN_1A_Pin, SET);
		HAL_GPIO_WritePin(EN_1B_GPIO_Port, EN_1B_Pin, SET);
		HAL_GPIO_WritePin(EN_2A_GPIO_Port, EN_2A_Pin, SET);
		HAL_GPIO_WritePin(EN_2B_GPIO_Port, EN_2B_Pin, SET);
	}


}

