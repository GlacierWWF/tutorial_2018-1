/*****************************************************************************
*                                                                            *
*  @file     display_num.h                                                   *
*  @brief    This file contains the funtion to control the digital tube      *
*	Function: 																 																 *
*                                                                            *
*  @author   Feipeng Ma                                                      *
*  @email    767102280@qq.com                                                *
*  @version  1.0.0                                                           *
*  @date     2018/10/19                                                      *                     
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2018/10/19 | 1.0.0   | Feipeng Ma      | Create file                      *
*----------------------------------------------------------------------------*
*  2018/10/19 | 1.0.1   | Feipeng Ma      | add the function                 *
*----------------------------------------------------------------------------*
*  2018/10/26 | 1.0.2   | Feipeng Ma      | add the function          			 *
*****************************************************************************/

#ifndef __DISPLAY_NUM_H
#define __DISPLAY_NUM_H
/*
数码管为共阴数码管
从左下角开始逆时针数1-12
共阴极 12 9 8 6 
数码管段 从最上面的横开始顺时针数到中间的横 A-G
	A
  F   B
    G  
  E   C
    D

 A   B   C   D   E   F    G
 11  7   4   2   1   10   5
 
 数字 0   A B C D E F \
 数字 1		B C
 数字 2  	A B G E D
 数字 3 	A B G C D
 数字 4 	F G B C
 数字 5		A F G C D
 数字 6 	A F G E D C
 数字 7 	A B C
 数字 8 	A B C D E F G
 数字 9 	A B C D F G
*/ 
#include "stm32f10x.h"

#define TUBE_0_GPIO_PORT  GPIOA
#define TUBE_0_GPIO_PIN		GPIO_Pin_4
#define TUBE_0_GPIO_CLK	 	RCC_APB2Periph_GPIOA

#define TUBE_1_GPIO_PORT	GPIOA
#define TUBE_1_GPIO_PIN		GPIO_Pin_5
#define TUBE_1_GPIO_CLK	 	RCC_APB2Periph_GPIOA

#define TUBE_2_GPIO_PORT	GPIOA
#define TUBE_2_GPIO_PIN		GPIO_Pin_6
#define TUBE_2_GPIO_CLK		RCC_APB2Periph_GPIOA

#define TUBE_3_GPIO_PORT	GPIOA
#define TUBE_3_GPIO_PIN		GPIO_Pin_7
#define TUBE_3_GPIO_CLK		RCC_APB2Periph_GPIOA

#define TUBE_4_GPIO_PORT	GPIOB
#define TUBE_4_GPIO_PIN		GPIO_Pin_12
#define TUBE_4_GPIO_CLK		RCC_APB2Periph_GPIOB

#define TUBE_5_GPIO_PORT	GPIOB
#define TUBE_5_GPIO_PIN		GPIO_Pin_13
#define TUBE_5_GPIO_CLK		RCC_APB2Periph_GPIOB

#define TUBE_6_GPIO_PORT	GPIOC
#define TUBE_6_GPIO_PIN		GPIO_Pin_13
#define TUBE_6_GPIO_CLK		RCC_APB2Periph_GPIOC

#define TUBE_7_GPIO_PORT	GPIOC
#define TUBE_7_GPIO_PIN		GPIO_Pin_4
#define TUBE_7_GPIO_CLK		RCC_APB2Periph_GPIOC


#define LED_A_GPIO_PORT		GPIOC
#define LED_A_GPIO_PIN		GPIO_Pin_6
#define LED_A_GPIO_CLK		RCC_APB2Periph_GPIOC
#define LED_B_GPIO_PORT		GPIOC
#define LED_B_GPIO_PIN		GPIO_Pin_10
#define LED_B_GPIO_CLK		RCC_APB2Periph_GPIOC
#define LED_C_GPIO_PORT		GPIOC
#define LED_C_GPIO_PIN		GPIO_Pin_9
#define LED_C_GPIO_CLK		RCC_APB2Periph_GPIOC
#define LED_D_GPIO_PORT		GPIOD
#define LED_D_GPIO_PIN		GPIO_Pin_2
#define LED_D_GPIO_CLK		RCC_APB2Periph_GPIOD
#define LED_E_GPIO_PORT		GPIOC
#define LED_E_GPIO_PIN		GPIO_Pin_8
#define LED_E_GPIO_CLK		RCC_APB2Periph_GPIOC
#define LED_F_GPIO_PORT		GPIOC
#define LED_F_GPIO_PIN		GPIO_Pin_7
#define LED_F_GPIO_CLK		RCC_APB2Periph_GPIOC
#define LED_G_GPIO_PORT		GPIOC
#define LED_G_GPIO_PIN		GPIO_Pin_12
#define LED_G_GPIO_CLK		RCC_APB2Periph_GPIOC

#define TUBE_0_ON					{GPIO_ResetBits(TUBE_0_GPIO_PORT, TUBE_0_GPIO_PIN);\
GPIO_SetBits(TUBE_1_GPIO_PORT,TUBE_1_GPIO_PIN);GPIO_SetBits(TUBE_2_GPIO_PORT,TUBE_2_GPIO_PIN);\
GPIO_SetBits(TUBE_3_GPIO_PORT,TUBE_3_GPIO_PIN);GPIO_SetBits(TUBE_4_GPIO_PORT,TUBE_4_GPIO_PIN);\
GPIO_SetBits(TUBE_5_GPIO_PORT,TUBE_5_GPIO_PIN);GPIO_SetBits(TUBE_6_GPIO_PORT,TUBE_6_GPIO_PIN);\
GPIO_SetBits(TUBE_7_GPIO_PORT,TUBE_7_GPIO_PIN);}

#define TUBE_1_ON					{GPIO_ResetBits(TUBE_1_GPIO_PORT, TUBE_1_GPIO_PIN);\
GPIO_SetBits(TUBE_0_GPIO_PORT,TUBE_0_GPIO_PIN);GPIO_SetBits(TUBE_2_GPIO_PORT,TUBE_2_GPIO_PIN);\
GPIO_SetBits(TUBE_3_GPIO_PORT,TUBE_3_GPIO_PIN);GPIO_SetBits(TUBE_4_GPIO_PORT,TUBE_4_GPIO_PIN);\
GPIO_SetBits(TUBE_5_GPIO_PORT,TUBE_5_GPIO_PIN);GPIO_SetBits(TUBE_6_GPIO_PORT,TUBE_6_GPIO_PIN);\
GPIO_SetBits(TUBE_7_GPIO_PORT,TUBE_7_GPIO_PIN);}

#define TUBE_2_ON					{GPIO_ResetBits(TUBE_2_GPIO_PORT, TUBE_2_GPIO_PIN);\
GPIO_SetBits(TUBE_1_GPIO_PORT,TUBE_1_GPIO_PIN);GPIO_SetBits(TUBE_0_GPIO_PORT,TUBE_0_GPIO_PIN);\
GPIO_SetBits(TUBE_3_GPIO_PORT,TUBE_3_GPIO_PIN);GPIO_SetBits(TUBE_4_GPIO_PORT,TUBE_4_GPIO_PIN);\
GPIO_SetBits(TUBE_5_GPIO_PORT,TUBE_5_GPIO_PIN);GPIO_SetBits(TUBE_6_GPIO_PORT,TUBE_6_GPIO_PIN);\
GPIO_SetBits(TUBE_7_GPIO_PORT,TUBE_7_GPIO_PIN);}

#define TUBE_3_ON					{GPIO_ResetBits(TUBE_3_GPIO_PORT, TUBE_3_GPIO_PIN);\
GPIO_SetBits(TUBE_1_GPIO_PORT,TUBE_1_GPIO_PIN);GPIO_SetBits(TUBE_0_GPIO_PORT,TUBE_0_GPIO_PIN);\
GPIO_SetBits(TUBE_2_GPIO_PORT,TUBE_2_GPIO_PIN);GPIO_SetBits(TUBE_4_GPIO_PORT,TUBE_4_GPIO_PIN);\
GPIO_SetBits(TUBE_5_GPIO_PORT,TUBE_5_GPIO_PIN);GPIO_SetBits(TUBE_6_GPIO_PORT,TUBE_6_GPIO_PIN);\
GPIO_SetBits(TUBE_7_GPIO_PORT,TUBE_7_GPIO_PIN);}

#define TUBE_4_ON					{GPIO_ResetBits(TUBE_4_GPIO_PORT, TUBE_4_GPIO_PIN);\
GPIO_SetBits(TUBE_1_GPIO_PORT,TUBE_1_GPIO_PIN);GPIO_SetBits(TUBE_0_GPIO_PORT,TUBE_0_GPIO_PIN);\
GPIO_SetBits(TUBE_2_GPIO_PORT,TUBE_2_GPIO_PIN);GPIO_SetBits(TUBE_3_GPIO_PORT,TUBE_3_GPIO_PIN);\
GPIO_SetBits(TUBE_5_GPIO_PORT,TUBE_5_GPIO_PIN);GPIO_SetBits(TUBE_6_GPIO_PORT,TUBE_6_GPIO_PIN);\
GPIO_SetBits(TUBE_7_GPIO_PORT,TUBE_7_GPIO_PIN);}

#define TUBE_5_ON					{GPIO_ResetBits(TUBE_5_GPIO_PORT, TUBE_5_GPIO_PIN);\
GPIO_SetBits(TUBE_1_GPIO_PORT,TUBE_1_GPIO_PIN);GPIO_SetBits(TUBE_0_GPIO_PORT,TUBE_0_GPIO_PIN);\
GPIO_SetBits(TUBE_2_GPIO_PORT,TUBE_2_GPIO_PIN);GPIO_SetBits(TUBE_4_GPIO_PORT,TUBE_4_GPIO_PIN);\
GPIO_SetBits(TUBE_3_GPIO_PORT,TUBE_3_GPIO_PIN);GPIO_SetBits(TUBE_6_GPIO_PORT,TUBE_6_GPIO_PIN);\
GPIO_SetBits(TUBE_7_GPIO_PORT,TUBE_7_GPIO_PIN);}

#define TUBE_6_ON					{GPIO_ResetBits(TUBE_6_GPIO_PORT, TUBE_6_GPIO_PIN);\
GPIO_SetBits(TUBE_1_GPIO_PORT,TUBE_1_GPIO_PIN);GPIO_SetBits(TUBE_0_GPIO_PORT,TUBE_0_GPIO_PIN);\
GPIO_SetBits(TUBE_2_GPIO_PORT,TUBE_2_GPIO_PIN);GPIO_SetBits(TUBE_4_GPIO_PORT,TUBE_4_GPIO_PIN);\
GPIO_SetBits(TUBE_5_GPIO_PORT,TUBE_5_GPIO_PIN);GPIO_SetBits(TUBE_3_GPIO_PORT,TUBE_3_GPIO_PIN);\
GPIO_SetBits(TUBE_7_GPIO_PORT,TUBE_7_GPIO_PIN);}

#define TUBE_7_ON					{GPIO_ResetBits(TUBE_7_GPIO_PORT, TUBE_7_GPIO_PIN);\
GPIO_SetBits(TUBE_1_GPIO_PORT,TUBE_1_GPIO_PIN);GPIO_SetBits(TUBE_0_GPIO_PORT,TUBE_0_GPIO_PIN);\
GPIO_SetBits(TUBE_2_GPIO_PORT,TUBE_2_GPIO_PIN);GPIO_SetBits(TUBE_4_GPIO_PORT,TUBE_4_GPIO_PIN);\
GPIO_SetBits(TUBE_5_GPIO_PORT,TUBE_5_GPIO_PIN);GPIO_SetBits(TUBE_6_GPIO_PORT,TUBE_6_GPIO_PIN);\
GPIO_SetBits(TUBE_3_GPIO_PORT,TUBE_3_GPIO_PIN);}



#define LED_A_ON		GPIO_SetBits(LED_A_GPIO_PORT,LED_A_GPIO_PIN)
#define LED_A_OFF		GPIO_ResetBits(LED_A_GPIO_PORT,LED_A_GPIO_PIN)

#define LED_B_ON		GPIO_SetBits(LED_B_GPIO_PORT,LED_B_GPIO_PIN)
#define LED_B_OFF		GPIO_ResetBits(LED_B_GPIO_PORT,LED_B_GPIO_PIN)

#define LED_C_ON		GPIO_SetBits(LED_C_GPIO_PORT,LED_C_GPIO_PIN)
#define LED_C_OFF		GPIO_ResetBits(LED_C_GPIO_PORT,LED_C_GPIO_PIN)

#define LED_D_ON		GPIO_SetBits(LED_D_GPIO_PORT,LED_D_GPIO_PIN)
#define LED_D_OFF		GPIO_ResetBits(LED_D_GPIO_PORT,LED_D_GPIO_PIN)

#define LED_E_ON		GPIO_SetBits(LED_E_GPIO_PORT,LED_E_GPIO_PIN)
#define LED_E_OFF		GPIO_ResetBits(LED_E_GPIO_PORT,LED_E_GPIO_PIN)

#define LED_F_ON		GPIO_SetBits(LED_F_GPIO_PORT,LED_F_GPIO_PIN)
#define LED_F_OFF		GPIO_ResetBits(LED_F_GPIO_PORT,LED_F_GPIO_PIN)

#define LED_G_ON		GPIO_SetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN)
#define LED_G_OFF		GPIO_ResetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN)


#define NUM_1				{0,1,1,0,0,0,0}
#define NUM_2				{1,1,0,1,1,0,1}
#define NUM_3				{1,1,1,1,0,0,1}
#define NUM_4				{0,1,1,0,0,1,1}
#define NUM_5				{1,0,1,1,0,1,1}
#define NUM_6				{1,0,1,1,1,1,1}
#define NUM_7				{1,1,1,0,0,0,0}
#define NUM_8				{1,1,1,1,1,1,1}
#define NUM_9				{1,1,1,1,0,1,1}
#define NUM_0				{1,1,1,1,1,1,0}
void BASIC_TIM_6_Config(void);
void TIM_6_NVIC_Config(void);
void BASIC_TIM_6_Init(void);
void BASIC_TIM_7_Config(void);
void TIM_7_NVIC_Config(void);
void BASIC_TIM_7_Init(void);
void LED_GPIO_Config(void);
void Clear_LED(void);
void Display_Number(int *digital);
void delay_ms(int ms);
#endif

