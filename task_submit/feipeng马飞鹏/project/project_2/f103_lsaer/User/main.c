/*****************************************************************************
*                                                                            *
*  @file     main.c                                                 			 	 *
*  @brief    the main file of this project      			 											 *
*                                                                            *
*  @author   Feipeng Ma                                                      *
*  @email    767102280@qq.com                                                *
*  @version  1.0.0                                                           *
*  @date     2018/10/27                                                      *                     
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2018/10/27 | 1.0.0   | Feipeng Ma       | Create file                     *
*----------------------------------------------------------------------------*
*  2018/11/04 | 1.0.1   | Feipeng Ma       | fix the bug that cannot display *
*----------------------------------------------------------------------------*
*  2018/11/07 | 1.0.2   | Feipeng Ma       | make it perfect								 *
*----------------------------------------------------------------------------*
*****************************************************************************/
#include "stm32f10x.h"
#include "bsp_led.h"
#include "laser_receive.h"
#include "bsp_usart.h"

volatile uint32_t time_6 = 0;
volatile uint32_t time_7 = 0;
volatile float DutyCycle = 0;
volatile float Frequency = 0;
volatile uint32_t c_flag = 0;
volatile uint32_t be_attack = 0;
volatile uint32_t be_cure = 0;
uint32_t cure_times = 0;
uint32_t cure_plane[4] = {0,0,0,0};
uint8_t NUM[11][7]={
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
{0,0,0,0,0,0,1}, // -
};

int digital_0[7]={0,1,1,0,0,0,0};
int digital_1[7]={1,1,1,1,1,1,0};
int digital_2[7]={0,0,0,0,0,0,1};
int digital_3[7]={1,1,1,1,1,1,0};
int d_0 = 1;
int d_1 = 0;
int d_3 = 0;
int main()
{
	int i,temp;
	LED_GPIO_Config();
	BASIC_TIM_6_Init();
	BASIC_TIM_7_Init();
	ADVANCE_TIM_Init();
	GENERAL_TIM_Init();
	GENERAL_TIM_c_Init();
	EXTI_GPIO_Config();
	while(1)
	{
		//have been attacked(PWM_INPUT_MODE)
		if(c_flag==0&&time_6>=5000)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,DISABLE);
			time_6=0;
			for(i=0;i<7;i++)
			{
				digital_3[i]=NUM[0][i];
			}
//			TIM_ITConfig(ADVANCE_TIM, TIM_IT_CC1, ENABLE);
			TIM_Cmd(TIM1,ENABLE);
		}
		//be attacked
		if(be_attack==1&&c_flag == 1&&time_6==0)
		{
//			TIM_ITConfig(ADVANCE_TIM, TIM_IT_CC1, DISABLE);
			TIM_Cmd(TIM1,DISABLE);
			be_attack = 0;
			// if life is 10,should turn to 9,this option is kind of different
			if(d_0==1)
			{
				for(i=0;i<7;i++)
				{
					digital_0[i] = NUM[0][i];
				}
				for(i=0;i<7;i++)
				{
					digital_1[i] = NUM[9][i];
				}
				d_0 = 0;
				d_1 = 9;
			}
			else
			{
				if(d_1>0)
				{
					d_1--;
				}
				for(i=0;i<7;i++)
				{
					digital_1[i]=NUM[d_1][i];
				}
			}
			for(i=0;i<7;i++)
			{
				digital_3[i]=NUM[1][i];
			}
			for(i=0;i<7;i++)
			{
				digital_2[i]=NUM[10][i];
			}
			c_flag = 0;
			time_6 = 0;
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
			
		}
		if(be_cure==1&&c_flag == 1&&time_6==0&&cure_times<4)
		{
			
			TIM_Cmd(TIM1,DISABLE);
			if(DutyCycle<=10)
				temp = 0;
			else if(DutyCycle>15&&DutyCycle<25)
				temp = 1;
			else if(DutyCycle>30&&DutyCycle<50)
				temp = 2;
			else if(DutyCycle>50&&DutyCycle<70)
				temp = 3;
			else
			{
				be_cure = 0;
				c_flag = 0;
				TIM_Cmd(TIM1,ENABLE);
				continue;
			}
			if(cure_plane[temp]==1)
			{
				c_flag = 0;
				be_cure =0;
				TIM_Cmd(TIM1,ENABLE);
				continue;
			}
			else
			{
				cure_plane[temp] = 1;
			}
			if(d_0==1||d_1==9)
			{
				if(d_1==9)
				{			
					for(i=0;i<7;i++)
					{
						digital_0[i] = NUM[1][i];
					}
					for(i=0;i<7;i++)
					{
						digital_1[i] = NUM[0][i];
					}
					d_0 = 1;
					d_1 = 0;
					cure_times++;
				}		
			}
			else
			{
				d_1++;
				for(i=0;i<7;i++)
				{
					digital_1[i]=NUM[d_1][i];
				}
				cure_times++;
			}
			for(i=0;i<7;i++)
			{
				digital_3[i]=NUM[1][i];
			}
			for(i=0;i<7;i++)
			{
				digital_2[i]=NUM[0][i];
			}
			time_6=0;
			c_flag =0;
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
			be_cure = 0;
		}


/**********************************************************************/

		TUBE_0_ON;
		Display_Number(digital_0);
		delay_0_1_ms(8);
		
		TUBE_1_ON;
		Display_Number(digital_1);
		delay_0_1_ms(8);
		
		TUBE_2_ON;
		Display_Number(digital_2);
		delay_0_1_ms(8);
		
		TUBE_3_ON;
		Display_Number(digital_3);
		delay_0_1_ms(8);
		
		
	}
	
	
}