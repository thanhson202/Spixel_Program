/*
 * read.c
 *
 *  Created on: Jul 1, 2024
 *      Author: admin
 */

#include"read.h"
#include"main.h"
#include"stdio.h"
#include"stdlib.h"



extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim6;
uint32_t read1_out, read2_out, read3_out, read4_out, read5_out, read6_out,
		 read7_out, read8_out, read9_out, read10_out,read11_out;

uint32_t read2_check,read1_check,action;

int Read_ss1,Read_ss2,Read_ss3,Read_ss4;
int save,val,limit_value;
int running;
int signal_ss;

int run,change,active;
int size = 10;
int count_ch1=0,count_ch2=0;
uint32_t array_read_ch1[10],array_read_ch2[10];

///////


////////////
typedef struct
{
uint32_t start;
uint32_t end;
uint32_t out;
uint32_t check;
} read;
read read_1,read_2,read_3,read_4,read_5,read_6,read_7,read_8,read_9,read_10,read_11,
	 read_ss1,read_ss2,read_ss3,read_ss4;



uint16_t map(uint16_t x,uint16_t In_Max,uint16_t In_Min,uint16_t Out_Max,uint16_t Out_Min )
{
	return(((x-In_Min)*(Out_Max-Out_Min)/(In_Max-In_Min))+Out_Min);
}

uint32_t media_filter(uint32_t* array_read, int size) {


    uint32_t temp_array[15];
    for (int i = 0; i < size; i++) {
        temp_array[i] = array_read[i];
    }

    // Sắp xếp mảng tạm bằng Insertion Sort
    for (int i = 1; i < size; i++) {
        uint32_t temp = temp_array[i];
        int j = i - 1;

        while (j >= 0 && temp_array[j] > temp) {
            temp_array[j + 1] = temp_array[j];
            j--;
        }
        temp_array[j + 1] = temp;
    }

    // Trả về giá trị trung vị
    return temp_array[size / 2];
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
						array_read_ch1[count_ch1] = read_1.out;
					    count_ch1 = (count_ch1 + 1) % size;
						read_1.out = media_filter(array_read_ch1,10);
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
						array_read_ch2[count_ch2] = read_2.out;
					    count_ch2 = (count_ch2 + 1) % size;
						read_2.out = media_filter(array_read_ch2,10);

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
			case 12:

				if(HAL_GPIO_ReadPin(SS1_GPIO_Port, SS1_Pin)==0)
				{
					read_ss1.start = htim1.Instance -> CNT;
					GPIO_InitTypeDef GPIO_InitStruct;
					GPIO_InitStruct.Pin = SS1_Pin;
					GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
					GPIO_InitStruct.Pull = GPIO_NOPULL;
					HAL_GPIO_Init(SS1_GPIO_Port, &GPIO_InitStruct);
					active =1;
				}
				else
				{
//					read_ss1.end = htim1.Instance->CNT;
//
//					if( read_ss1.start > read_ss1.end)
//					{
//						read_ss1.out = 65535 - read_ss1.start + read_ss1.end;
//					}
//					else
//					{
//						read_ss1.out = read_ss1.end - read_ss1.start;
//					}

					GPIO_InitTypeDef GPIO_InitStruct;
					GPIO_InitStruct.Pin = SS1_Pin;
					GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
					GPIO_InitStruct.Pull = GPIO_NOPULL;
					HAL_GPIO_Init(SS1_GPIO_Port, &GPIO_InitStruct);
				}
				break;
			case 13:

				if(HAL_GPIO_ReadPin(SS2_GPIO_Port, SS2_Pin)==0)
				{
					active =1;
					read_ss2.start = htim1.Instance -> CNT;
					GPIO_InitTypeDef GPIO_InitStruct;
					GPIO_InitStruct.Pin = SS2_Pin;
					GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
					GPIO_InitStruct.Pull = GPIO_NOPULL;
					HAL_GPIO_Init(SS2_GPIO_Port, &GPIO_InitStruct);
					active =1;
				}
				else
				{
//					read_ss2.end = htim1.Instance->CNT;
//
//					if( read_ss2.start > read_ss2.end)
//					{
//						read_ss2.out = 65535 - read_ss2.start + read_ss2.end;
//					}
//					else
//					{
//						read_ss1.out = read_ss1.end - read_ss1.start;
//					}

					GPIO_InitTypeDef GPIO_InitStruct;
					GPIO_InitStruct.Pin = SS2_Pin;
					GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
					GPIO_InitStruct.Pull = GPIO_NOPULL;
					HAL_GPIO_Init(SS2_GPIO_Port, &GPIO_InitStruct);
				}
				break;
			case 14:

				if(HAL_GPIO_ReadPin(SS3_GPIO_Port, SS3_Pin)==0)
				{
					active = 1;
					read_ss3.start = htim1.Instance -> CNT;
					GPIO_InitTypeDef GPIO_InitStruct;
					GPIO_InitStruct.Pin = SS3_Pin;
					GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
					GPIO_InitStruct.Pull = GPIO_NOPULL;
					HAL_GPIO_Init(SS3_GPIO_Port, &GPIO_InitStruct);
					active =1;
				}
				else
				{

					GPIO_InitTypeDef GPIO_InitStruct;
					GPIO_InitStruct.Pin = SS3_Pin;
					GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
					GPIO_InitStruct.Pull = GPIO_NOPULL;
					HAL_GPIO_Init(SS3_GPIO_Port, &GPIO_InitStruct);
				}
			case 15:

				if(HAL_GPIO_ReadPin(SS4_GPIO_Port, SS4_Pin)==0)
				{
					read_ss4.start = htim1.Instance -> CNT;
					GPIO_InitTypeDef GPIO_InitStruct;
					GPIO_InitStruct.Pin = SS4_Pin;
					GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
					GPIO_InitStruct.Pull = GPIO_NOPULL;
					HAL_GPIO_Init(SS4_GPIO_Port, &GPIO_InitStruct);
					active =1;
				}
				else
				{

					GPIO_InitTypeDef GPIO_InitStruct;
					GPIO_InitStruct.Pin = SS4_Pin;
					GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
					GPIO_InitStruct.Pull = GPIO_NOPULL;
					HAL_GPIO_Init(SS4_GPIO_Port, &GPIO_InitStruct);
				}
		}
	}

void convert(void)
{
	// xoay phai
	if(read_1.out > 43200)
	{
		read1_out = map(read_1.out,43200,61200,28700,0);
		val = 1;
		change = 1;

	}
	//xoay trai
	else if(read_1.out < 43200)
	{
		read1_out = map(read_1.out,7000,43200,0,28700);
		val = 2;
		change = 2;
	}
	else
	{
		read1_out = 28700;
	}

	//ch2 tien lui banh
	if(read_2.out > 43250)
	{
		read2_out = map(read_2.out,43250,61200,28700,0);
		val = 3;
		change = 3;

	}
	else if((read_2.out < 43250))//||((read1_out>read2_out)&&(read_2.out < 43250))
	{
		read2_out = map(read_2.out,7000,43250,0,28700);
		val = 4;
		change = 4;

	}
	else
	{
		read2_out = 28700;
	}

	//////// JOYSTIK GIUA
	if(read_1.out != 43200 && read_2.out != 43250)
	{
		limit_value = 1;
	}
	else
	{
		limit_value = 0;
	}
	if(limit_value == 1)
	{
		if((val ==4)&&(read_1.out>read_2.out)&&(read_1.out<55000))//(read_1.out > 43200)
		{
			val =4;
		}
		else if((read_1.out < read_2.out)&&(read_1.out<10000))//(read_1.out < 43200)
		{
			val = 2;
		}
		else if((read_1.out>read_2.out)&&(change = 1))//(read_1.out > 43200)
		{
			val = 1;
		}
		else
		{
			val=3;
		}
		/*
		if(((change ==4)&&(read_1.out>read_2.out)&&(read_1.out<55000))||
		   ((change ==3)&&(read_1.out<read_2.out)&&(read_2.out>55000)))
		{
			read1_out = 28700;

		}
		else if(read1_out!=28700)
		{
			read2_out = 28700;
			val = 1;
		}
		*/
		if(read_1.out == 7000 && read_2.out==7000)
		{
			val =17;
		}
		else if(read_1.out == 61200 && read_2.out == 7000)
		{
			val = 18;
		}
		else if (read_1.out == 7000 && read_2.out ==61200)
		{
			val = 19;
		}
		else if (read_1.out == 61200 && read_2.out ==61200)
		{
			val = 20;
		}
	}
		//////////////////++++++end+++++/////////////////

}
void direction(int running,uint32_t speed_CCR1,uint32_t speed_CCR2)
{
	//tien
	if(running == 1)
	{
		TIM3 -> CCR1 = speed_CCR1; // DC TRAI
		TIM3 -> CCR2 = speed_CCR2; // DC PHAI
		HAL_GPIO_WritePin(F_R_1A_GPIO_Port, F_R_1A_Pin, RESET);
		HAL_GPIO_WritePin(F_R_1B_GPIO_Port, F_R_1B_Pin, SET);

	}
	//lui
	else if(running == 2)
	{
		TIM3 -> CCR1 = speed_CCR1; // DC TRAI
		TIM3 -> CCR2 = speed_CCR2; // DC PHAI
		HAL_GPIO_WritePin(F_R_1A_GPIO_Port, F_R_1A_Pin, SET);
		HAL_GPIO_WritePin(F_R_1B_GPIO_Port, F_R_1B_Pin, RESET);
	}
	// xoay trai
	else if(running == 3)
	{
		TIM3 -> CCR1 = speed_CCR1; // DC TRAI
		TIM3 -> CCR2 = speed_CCR2; // DC PHAI
		HAL_GPIO_WritePin(F_R_1A_GPIO_Port, F_R_1A_Pin, RESET);
		HAL_GPIO_WritePin(F_R_1B_GPIO_Port, F_R_1B_Pin, RESET);
	}
	// xoay phai
	else if(running == 4)
	{
		TIM3 -> CCR1 = speed_CCR1; // DC TRAI
		TIM3 -> CCR2 = speed_CCR2; // DC PHAI
		HAL_GPIO_WritePin(F_R_1A_GPIO_Port, F_R_1A_Pin, SET);
		HAL_GPIO_WritePin(F_R_1B_GPIO_Port, F_R_1B_Pin, SET);
	}
}

void Status_SS(void)
{
	if(active ==1)
	{
		if( read_ss1.start > value_timer)
		{
			read_ss1.out = 65535 - read_ss1.start + value_timer;
		}
		else
		{
			read_ss1.out = value_timer - read_ss1.start;
		}
		if(read_ss1.out >= 2000)
		{
			active =0;
			HAL_GPIO_WritePin(BRK_1A_GPIO_Port, BRK_1A_Pin, RESET);
			HAL_GPIO_WritePin(BRK_1B_GPIO_Port, BRK_1B_Pin, RESET);
			HAL_GPIO_WritePin(BRK_2A_GPIO_Port, BRK_2A_Pin, RESET);
			HAL_GPIO_WritePin(BRK_2B_GPIO_Port, BRK_2B_Pin, RESET);

			HAL_GPIO_WritePin(BRK_1A_GPIO_Port, BRK_1A_Pin, SET);
			HAL_GPIO_WritePin(BRK_1B_GPIO_Port, BRK_1B_Pin, SET);
			HAL_GPIO_WritePin(BRK_2A_GPIO_Port, BRK_2A_Pin, SET);
			HAL_GPIO_WritePin(BRK_2B_GPIO_Port, BRK_2B_Pin, SET);

			GPIO_InitTypeDef GPIO_InitStruct;
			GPIO_InitStruct.Pin = SS1_Pin;
			GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			HAL_GPIO_Init(SS1_GPIO_Port, &GPIO_InitStruct);

			direction(2,22000,15000);// ss1: lui nhe sang phai
			HAL_Delay(1000);
		}
		if( read_ss2.start > value_timer)
		{
			read_ss2.out = 65535 - read_ss2.start + value_timer;
		}
		else
		{
			read_ss2.out = value_timer - read_ss2.start;
		}

		if(read_ss2.out >= 2000)
		{
			active =0;
			HAL_GPIO_WritePin(BRK_1A_GPIO_Port, BRK_1A_Pin, RESET);
			HAL_GPIO_WritePin(BRK_1B_GPIO_Port, BRK_1B_Pin, RESET);
			HAL_GPIO_WritePin(BRK_2A_GPIO_Port, BRK_2A_Pin, RESET);
			HAL_GPIO_WritePin(BRK_2B_GPIO_Port, BRK_2B_Pin, RESET);

			HAL_GPIO_WritePin(BRK_1A_GPIO_Port, BRK_1A_Pin, SET);
			HAL_GPIO_WritePin(BRK_1B_GPIO_Port, BRK_1B_Pin, SET);
			HAL_GPIO_WritePin(BRK_2A_GPIO_Port, BRK_2A_Pin, SET);
			HAL_GPIO_WritePin(BRK_2B_GPIO_Port, BRK_2B_Pin, SET);

			GPIO_InitTypeDef GPIO_InitStruct;
			GPIO_InitStruct.Pin = SS2_Pin;
			GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			HAL_GPIO_Init(SS2_GPIO_Port, &GPIO_InitStruct);

			direction(2,15000+13000,22000);// ss1: lui nhe sang trai lui +13000
			HAL_Delay(1000);
		}
		if( read_ss3.start > value_timer)
		{
			read_ss3.out = 65535 - read_ss3.start + value_timer;
		}
		else
		{
			read_ss3.out = value_timer - read_ss3.start;
		}
		if(read_ss3.out >= 2000)
		{
			active =0;
			HAL_GPIO_WritePin(BRK_1A_GPIO_Port, BRK_1A_Pin, RESET);
			HAL_GPIO_WritePin(BRK_1B_GPIO_Port, BRK_1B_Pin, RESET);
			HAL_GPIO_WritePin(BRK_2A_GPIO_Port, BRK_2A_Pin, RESET);
			HAL_GPIO_WritePin(BRK_2B_GPIO_Port, BRK_2B_Pin, RESET);

			HAL_GPIO_WritePin(BRK_1A_GPIO_Port, BRK_1A_Pin, SET);
			HAL_GPIO_WritePin(BRK_1B_GPIO_Port, BRK_1B_Pin, SET);
			HAL_GPIO_WritePin(BRK_2A_GPIO_Port, BRK_2A_Pin, SET);
			HAL_GPIO_WritePin(BRK_2B_GPIO_Port, BRK_2B_Pin, SET);

			GPIO_InitTypeDef GPIO_InitStruct;
			GPIO_InitStruct.Pin = SS3_Pin;
			GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			HAL_GPIO_Init(SS3_GPIO_Port, &GPIO_InitStruct);

			direction(1,22000,15000);// ss1: tien nhe sang phai
			HAL_Delay(1000);
		}

		if( read_ss4.start > value_timer)
		{
			read_ss4.out = 65535 - read_ss4.start + value_timer;
		}
		else
		{
			read_ss4.out = value_timer - read_ss4.start;
		}
		if(read_ss4.out >= 2000)
		{
			active =0;
			HAL_GPIO_WritePin(BRK_1A_GPIO_Port, BRK_1A_Pin, RESET);
			HAL_GPIO_WritePin(BRK_1B_GPIO_Port, BRK_1B_Pin, RESET);
			HAL_GPIO_WritePin(BRK_2A_GPIO_Port, BRK_2A_Pin, RESET);
			HAL_GPIO_WritePin(BRK_2B_GPIO_Port, BRK_2B_Pin, RESET);

			HAL_GPIO_WritePin(BRK_1A_GPIO_Port, BRK_1A_Pin, SET);
			HAL_GPIO_WritePin(BRK_1B_GPIO_Port, BRK_1B_Pin, SET);
			HAL_GPIO_WritePin(BRK_2A_GPIO_Port, BRK_2A_Pin, SET);
			HAL_GPIO_WritePin(BRK_2B_GPIO_Port, BRK_2B_Pin, SET);

			GPIO_InitTypeDef GPIO_InitStruct;
			GPIO_InitStruct.Pin = SS4_Pin;
			GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			HAL_GPIO_Init(SS4_GPIO_Port, &GPIO_InitStruct);

			direction(1,15000,22000);// ss1: lui nhe sang trai
			HAL_Delay(1000);
		}
	}
}

void control(void)
{
	Read_ss1 = HAL_GPIO_ReadPin(SS1_GPIO_Port, SS1_Pin);
	Read_ss2 = HAL_GPIO_ReadPin(SS2_GPIO_Port, SS2_Pin);
	Read_ss3 = HAL_GPIO_ReadPin(SS3_GPIO_Port, SS3_Pin);
	Read_ss4 = HAL_GPIO_ReadPin(SS4_GPIO_Port, SS4_Pin);
	if(read_1.out>7500&&read_1.out<10500&&read_2.out>27500&&read_2.out<29800)
	{
		run =0;
		HAL_GPIO_WritePin(BRK_1A_GPIO_Port, BRK_1A_Pin, RESET);
		HAL_GPIO_WritePin(BRK_1B_GPIO_Port, BRK_1B_Pin, RESET);
		HAL_GPIO_WritePin(BRK_2A_GPIO_Port, BRK_2A_Pin, RESET);
		HAL_GPIO_WritePin(BRK_2B_GPIO_Port, BRK_2B_Pin, RESET);

		HAL_GPIO_WritePin(EN_1A_GPIO_Port, EN_1A_Pin, RESET);
		HAL_GPIO_WritePin(EN_1B_GPIO_Port, EN_1B_Pin, RESET);
		HAL_GPIO_WritePin(EN_2A_GPIO_Port, EN_2A_Pin, RESET);
		HAL_GPIO_WritePin(EN_2B_GPIO_Port, EN_2B_Pin, RESET);

		HAL_GPIO_WritePin(BRK_1A_GPIO_Port, BRK_1A_Pin, SET);
		HAL_GPIO_WritePin(BRK_1B_GPIO_Port, BRK_1B_Pin, SET);
		HAL_GPIO_WritePin(BRK_2A_GPIO_Port, BRK_2A_Pin, SET);
		HAL_GPIO_WritePin(BRK_2B_GPIO_Port, BRK_2B_Pin, SET);
	}
	else
	{
		if (Read_ss1 ==1 && Read_ss2 ==1 && Read_ss3 ==1 && Read_ss4==1)
		{
			run =1;
			HAL_GPIO_WritePin(EN_1A_GPIO_Port, EN_1A_Pin, SET);
			HAL_GPIO_WritePin(EN_1B_GPIO_Port, EN_1B_Pin, SET);
			HAL_GPIO_WritePin(EN_2A_GPIO_Port, EN_2A_Pin, SET);
			HAL_GPIO_WritePin(EN_2B_GPIO_Port, EN_2B_Pin, SET);

			HAL_GPIO_WritePin(BRK_1A_GPIO_Port, BRK_1A_Pin, SET);
			HAL_GPIO_WritePin(BRK_1B_GPIO_Port, BRK_1B_Pin, SET);
			HAL_GPIO_WritePin(BRK_2A_GPIO_Port, BRK_2A_Pin, SET);
			HAL_GPIO_WritePin(BRK_2B_GPIO_Port, BRK_2B_Pin, SET);

			switch (val)
			{
				case 1:
					direction(4,read1_out,read1_out);
					break;
				case 2:
					direction(3,read1_out,read1_out);
					break;
				case 3:
					direction(2,read2_out+13000,read2_out);
					break;
				case 4:
					direction(1,read2_out,read2_out);
					break;
				case 17:
					direction(1,read2_out,read2_out+18000);
					break;
				case 18:
					direction(1,read2_out+18000,read2_out);
					break;
				case 19:
					direction(2,read2_out,read2_out);
					break;
				case 20:
					direction(2,read2_out+20000,read2_out);
					break;
			}

		}
		else
		{
			active  =1;
		}
	}
}
