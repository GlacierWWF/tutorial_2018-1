/*****************************************************************************
*                                                                            *
*  @file     main.c                                             						 *
*  @brief    the main file of the project         													 *
*  @author   Feipeng Ma                                                      *
*  @email    767102280@qq.com                                                *
*  @version  1.0.0                                                           *
*  @date     2018/10/26                                                      *                     
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2018/10/19 | 1.0.0   | Feipeng Ma      | Create file                      *
*----------------------------------------------------------------------------*
*  2018/10/26 | 1.0.1   | Feipeng Ma      | finish the basic function        *
*----------------------------------------------------------------------------*
*****************************************************************************/


#include "stm32f10x.h"
#include "display_num.h"
#include "password_processing.h"
#include "bsp_usart.h"
#include<stdlib.h>
uint8_t NUM[10][7]={
{1,1,1,1,1,1,0}, // 0
{0,1,1,0,0,0,0}, // 1
{1,1,0,1,1,0,1}, // 2
{1,1,1,1,0,0,1}, // 3
{0,1,1,0,0,1,1}, // 4
{1,0,1,1,0,1,1}, // 5
{1,0,1,1,1,1,1}, // 6
{1,1,1,0,0,0,0}, // 7
{1,1,1,1,1,1,1}, // 8
{1,1,1,1,0,1,1}, // 9
};
volatile uint32_t ktime = 0;
volatile uint32_t rtime = 0;
volatile uint8_t secret[4];
volatile uint8_t change_flag = 0;
int digital_0[7]=NUM_2;
int digital_1[7]=NUM_3;
int digital_2[7]=NUM_3;
int digital_3[7]=NUM_3;
int digital_0_1[7];
int digital_1_1[7];
int digital_2_1[7];
int digital_3_1[7];
int digital_0_2[7];
int digital_1_2[7];
int digital_2_2[7];
int digital_3_2[7];
int change_time=15000;
int main()
{

	USART_Config();
	BASIC_TIM_6_Init();
	BASIC_TIM_7_Init();
	LED_GPIO_Config();
	Clear_LED();
	
	break_password(digital_0,digital_0_1,digital_0_2);
	break_password(digital_1,digital_1_1,digital_1_2);
	break_password(digital_2,digital_2_1,digital_2_2);
	break_password(digital_3,digital_3_1,digital_3_2);
	
	while(1)
	{

		if(change_flag==1)
		{
			uint8_t k,i;
			k=secret[0]-48;
			for(i=0;i<7;i++)
			{
				digital_0[i]=NUM[k][i];
			}
			k=secret[1]-48;
			for(i=0;i<7;i++)
			{
				digital_1[i]=NUM[k][i];
			}
			k=secret[2]-48;
			for(i=0;i<7;i++)
			{
				digital_2[i]=NUM[k][i];
			}
			k=secret[3]-48;
			for(i=0;i<7;i++)
			{
				digital_3[i]=NUM[k][i];
			}
			break_password(digital_0,digital_0_1,digital_0_2);
			break_password(digital_1,digital_1_1,digital_1_2);
			break_password(digital_2,digital_2_1,digital_2_2);
			break_password(digital_3,digital_3_1,digital_3_2);
			change_flag=0;

		}

		if(rtime>=change_time)
		{
				break_password(digital_0,digital_0_1,digital_0_2);
				break_password(digital_1,digital_1_1,digital_1_2);
				break_password(digital_2,digital_2_1,digital_2_2);
				break_password(digital_3,digital_3_1,digital_3_2);
				rtime = 0;	
		}
		TUBE_0_ON;
		Display_Number(digital_0_1);
		delay_ms(3);
		
		TUBE_1_ON;
		Display_Number(digital_1_1);
		delay_ms(3);
		
		TUBE_2_ON;
		Display_Number(digital_2_1);
		delay_ms(3);
		
		TUBE_3_ON;
		Display_Number(digital_3_1);
		delay_ms(3);
		TUBE_4_ON;
		Display_Number(digital_0_2);
		delay_ms(3);
		
		TUBE_5_ON;
		Display_Number(digital_1_2);
		delay_ms(3);
		
		TUBE_6_ON;
		Display_Number(digital_2_2);
		delay_ms(3);
		
		TUBE_7_ON;
		Display_Number(digital_3_2);
		delay_ms(3);
	}


}

