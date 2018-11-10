/*****************************************************************************
*                                                                            *
*  @file     bsp_led.h                                                 			 *
*  @brief    the header file to control the digital tube      			 				 *
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


#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"

//define the GPIO of 4 digital tube
#define TUBE_0_GPIO_PORT  GPIOB
#define TUBE_0_GPIO_PIN		GPIO_Pin_14
#define TUBE_0_GPIO_CLK	 	RCC_APB2Periph_GPIOB

#define TUBE_1_GPIO_PORT	GPIOE
#define TUBE_1_GPIO_PIN		GPIO_Pin_14
#define TUBE_1_GPIO_CLK	 	RCC_APB2Periph_GPIOE

#define TUBE_2_GPIO_PORT	GPIOE
#define TUBE_2_GPIO_PIN		GPIO_Pin_12
#define TUBE_2_GPIO_CLK		RCC_APB2Periph_GPIOE

#define TUBE_3_GPIO_PORT	GPIOE
#define TUBE_3_GPIO_PIN		GPIO_Pin_11
#define TUBE_3_GPIO_CLK		RCC_APB2Periph_GPIOE

//define the A->G LED
#define LED_A_GPIO_PORT		GPIOB
#define LED_A_GPIO_PIN		GPIO_Pin_12
#define LED_A_GPIO_CLK		RCC_APB2Periph_GPIOB
#define LED_B_GPIO_PORT		GPIOE
#define LED_B_GPIO_PIN		GPIO_Pin_10
#define LED_B_GPIO_CLK		RCC_APB2Periph_GPIOE
#define LED_C_GPIO_PORT		GPIOE
#define LED_C_GPIO_PIN		GPIO_Pin_15
#define LED_C_GPIO_CLK		RCC_APB2Periph_GPIOE
#define LED_D_GPIO_PORT		GPIOB
#define LED_D_GPIO_PIN		GPIO_Pin_13
#define LED_D_GPIO_CLK		RCC_APB2Periph_GPIOB
#define LED_E_GPIO_PORT		GPIOB
#define LED_E_GPIO_PIN		GPIO_Pin_15
#define LED_E_GPIO_CLK		RCC_APB2Periph_GPIOB
#define LED_F_GPIO_PORT		GPIOB
#define LED_F_GPIO_PIN		GPIO_Pin_10
#define LED_F_GPIO_CLK		RCC_APB2Periph_GPIOB
#define LED_G_GPIO_PORT		GPIOE
#define LED_G_GPIO_PIN		GPIO_Pin_13
#define LED_G_GPIO_CLK		RCC_APB2Periph_GPIOE

#define TUBE_0_ON					{GPIO_ResetBits(TUBE_0_GPIO_PORT, TUBE_0_GPIO_PIN);\
GPIO_SetBits(TUBE_1_GPIO_PORT,TUBE_1_GPIO_PIN);GPIO_SetBits(TUBE_2_GPIO_PORT,TUBE_2_GPIO_PIN);\
GPIO_SetBits(TUBE_3_GPIO_PORT,TUBE_3_GPIO_PIN);}

#define TUBE_1_ON					{GPIO_ResetBits(TUBE_1_GPIO_PORT, TUBE_1_GPIO_PIN);\
GPIO_SetBits(TUBE_0_GPIO_PORT,TUBE_0_GPIO_PIN);GPIO_SetBits(TUBE_2_GPIO_PORT,TUBE_2_GPIO_PIN);\
GPIO_SetBits(TUBE_3_GPIO_PORT,TUBE_3_GPIO_PIN);}

#define TUBE_2_ON					{GPIO_ResetBits(TUBE_2_GPIO_PORT, TUBE_2_GPIO_PIN);\
GPIO_SetBits(TUBE_1_GPIO_PORT,TUBE_1_GPIO_PIN);GPIO_SetBits(TUBE_0_GPIO_PORT,TUBE_0_GPIO_PIN);\
GPIO_SetBits(TUBE_3_GPIO_PORT,TUBE_3_GPIO_PIN);}

#define TUBE_3_ON					{GPIO_ResetBits(TUBE_3_GPIO_PORT, TUBE_3_GPIO_PIN);\
GPIO_SetBits(TUBE_1_GPIO_PORT,TUBE_1_GPIO_PIN);GPIO_SetBits(TUBE_0_GPIO_PORT,TUBE_0_GPIO_PIN);\
GPIO_SetBits(TUBE_2_GPIO_PORT,TUBE_2_GPIO_PIN);}

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

void LED_GPIO_Config(void);
void BASIC_TIM_6_Init(void);
void BASIC_TIM_7_Init(void);
void delay_0_1_ms(int ms);
void Clear_LED(void);
void Display_Number(int *digital);

#endif  /* __BSP_LED_H */