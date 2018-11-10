/*****************************************************************************
*                                                                            *
*  @file     bsp_led.c                                                 			 *
*  @brief    the source file to control the digital tube      			 				 *
*                                                                            *
*  @author   Feipeng Ma                                                      *
*  @email    767102280@qq.com                                                *
*  @version  1.0.0                                                           *
*  @date     2018/11/03                                                      *                     
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2018/11/03 | 1.0.0   | Feipeng Ma       | Create file                     *
*----------------------------------------------------------------------------*
*****************************************************************************/

#include "bsp_led.h"
extern volatile uint32_t time_6;
extern volatile uint32_t time_7;

static void BASIC_TIM_6_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_Initstructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	TIM_Initstructure.TIM_Period = 1000;
	TIM_Initstructure.TIM_Prescaler = 72-1;
	TIM_TimeBaseInit(TIM6,&TIM_Initstructure);
	TIM_ClearFlag(TIM6,TIM_FLAG_Update);
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM6,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,DISABLE);
}
static void TIM_6_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void BASIC_TIM_6_Init(void)
{
	TIM_6_NVIC_Config();
	BASIC_TIM_6_Config();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,DISABLE);
}


static void BASIC_TIM_7_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_Initstructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
	TIM_Initstructure.TIM_Period = 100;
	TIM_Initstructure.TIM_ClockDivision = 72-1;
	TIM_TimeBaseInit(TIM7,&TIM_Initstructure);
	TIM_ClearFlag(TIM7,TIM_FLAG_Update);
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM7,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,DISABLE);
}
static void TIM_7_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void BASIC_TIM_7_Init(void)
{
	TIM_7_NVIC_Config();
	BASIC_TIM_7_Config();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
}

void delay_0_1_ms(int ms)
{
	time_7 =0;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
	while(time_7<=ms);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,DISABLE);
}

void Clear_LED(void)
{
	
	LED_A_OFF;
	LED_B_OFF;
	LED_C_OFF;
	LED_D_OFF;
	LED_E_OFF;
	LED_F_OFF;
	LED_G_OFF;
	
}
void Display_Number(int *digital)
{
	
	Clear_LED();
	if(digital[0]==1)
		LED_A_ON;
	if(digital[1]==1)
		LED_B_ON;
	if(digital[2]==1)
		LED_C_ON;
	if(digital[3]==1)
		LED_D_ON;
	if(digital[4]==1)
		LED_E_ON;
	if(digital[5]==1)
		LED_F_ON;
	if(digital[6]==1)
		LED_G_ON;
}

void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(TUBE_0_GPIO_CLK|TUBE_1_GPIO_CLK|TUBE_2_GPIO_CLK|TUBE_3_GPIO_CLK\
	|LED_A_GPIO_CLK|LED_B_GPIO_CLK|LED_C_GPIO_CLK|LED_D_GPIO_CLK|LED_E_GPIO_CLK\
	|LED_F_GPIO_CLK|LED_G_GPIO_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = TUBE_0_GPIO_PIN;	
	GPIO_Init(TUBE_0_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = TUBE_1_GPIO_PIN;	
	GPIO_Init(TUBE_1_GPIO_PORT,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = TUBE_2_GPIO_PIN;	
	GPIO_Init(TUBE_2_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = TUBE_3_GPIO_PIN;	
	GPIO_Init(TUBE_3_GPIO_PORT,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = LED_A_GPIO_PIN;	
	GPIO_Init(LED_A_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LED_B_GPIO_PIN;	
	GPIO_Init(LED_B_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LED_C_GPIO_PIN;	
	GPIO_Init(LED_C_GPIO_PORT,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LED_D_GPIO_PIN;	
	GPIO_Init(LED_D_GPIO_PORT,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LED_E_GPIO_PIN;	
	GPIO_Init(LED_E_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LED_F_GPIO_PIN;	
	GPIO_Init(LED_F_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LED_G_GPIO_PIN;	
	GPIO_Init(LED_G_GPIO_PORT,&GPIO_InitStructure);
}




