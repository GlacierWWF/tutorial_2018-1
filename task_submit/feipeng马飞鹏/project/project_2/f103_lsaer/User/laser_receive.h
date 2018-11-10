/*****************************************************************************
*                                                                            *
*  @file     laser_receive.h                                                 *
*  @brief    This file contains the funtion to receive the laser      			 *
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
*****************************************************************************/
#ifndef __RECEIVE_H
#define __RECEIVE_H

#include "stm32f10x.h"

#define            ADVANCE_TIM                   TIM1
#define            ADVANCE_TIM_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            ADVANCE_TIM_CLK               RCC_APB2Periph_TIM1

// 输入捕获能捕获到的最小的频率为 72M/{ (ARR+1)*(PSC+1) }
#define            ADVANCE_TIM_PERIOD            (1000-1)
#define            ADVANCE_TIM_PSC               (72-1)

// 中断相关宏定义
#define            ADVANCE_TIM_IRQ               TIM1_CC_IRQn
#define            ADVANCE_TIM_IRQHandler        TIM1_CC_IRQHandler

// TIM1 输入捕获通道1
#define            ADVANCE_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            ADVANCE_TIM_CH1_PORT          GPIOA
#define            ADVANCE_TIM_CH1_PIN           GPIO_Pin_8

#define            ADVANCE_TIM_IC1PWM_CHANNEL    TIM_Channel_1
#define            ADVANCE_TIM_IC2PWM_CHANNEL    TIM_Channel_2

#define            GENERAL_TIM                   TIM3
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM3
// 输出PWM的频率为 72M/{ (ARR+1)*(PSC+1) }
#define            GENERAL_TIM_PERIOD            (28-1)
#define            GENERAL_TIM_PSC               (72-1)

#define            GENERAL_TIM_CCR1              5
#define            GENERAL_TIM_CCR2              4
#define            GENERAL_TIM_CCR3              3
#define            GENERAL_TIM_CCR4              2

#define            PLANE_0             					 4
#define            PLANE_1           						 17
#define            PLANE_2             					 31
#define            PLANE_3							         46

// TIM3 输出比较通道1
#define            GENERAL_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH1_PORT          GPIOA
#define            GENERAL_TIM_CH1_PIN           GPIO_Pin_6

#define            GENERAL_TIM_c                  	TIM2
#define            GENERAL_TIM_c_APBxClock_FUN     	RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_c_CLK               	RCC_APB1Periph_TIM2


// 输出PWM的频率为 72M/{ (ARR+1)*(PSC+1) }

#define            GENERAL_TIM_c_PERIOD            (77-1)
#define            GENERAL_TIM_c_PSC               (72-1)

#define            GENERAL_TIM_c_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_c_CH1_PORT          GPIOA
#define            GENERAL_TIM_c_CH1_PIN           GPIO_Pin_0

#define 						KEY1_PORT											GPIOE
#define 						KEY1_PIN											GPIO_Pin_2
#define 						KEY1_PORT_CLK									(RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO)
#define 						KEY1_PORTSSOURCE							GPIO_PortSourceGPIOE
#define 						KEY1_PINSOURCE								GPIO_PinSource2
#define 						KEY1_EXTI_LINE								EXTI_Line2
#define 						KEY1_EXTI_IRQ									EXTI2_IRQn
#define 						KEY1_IRQHandler								EXTI2_IRQHandler

#define 						KEY2_PORT											GPIOE
#define 						KEY2_PORT_CLK									(RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO)
#define 						KEY2_PIN											GPIO_Pin_3
#define 						KEY2_PORTSSOURCE							GPIO_PortSourceGPIOE
#define 						KEY2_PINSOURCE								GPIO_PinSource3
#define 						KEY2_EXTI_LINE								EXTI_Line3
#define 						KEY2_EXTI_IRQ									EXTI3_IRQn
#define 						KEY2_IRQHandler								EXTI3_IRQHandler

#define 						KEY3_PORT											GPIOB
#define 						KEY3_PORT_CLK									(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define 						KEY3_PIN											GPIO_Pin_4
#define 						KEY3_PORTSSOURCE							GPIO_PortSourceGPIOB
#define 						KEY3_PINSOURCE								GPIO_PinSource4
#define 						KEY3_EXTI_LINE								EXTI_Line4
#define 						KEY3_EXTI_IRQ									EXTI4_IRQn
#define 						KEY3_IRQHandler								EXTI4_IRQHandler

#define 						KEY4_PORT											GPIOB
#define 						KEY4_PORT_CLK									(RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO)
#define 						KEY4_PIN											GPIO_Pin_5
#define 						KEY4_PORTSSOURCE							GPIO_PortSourceGPIOB
#define 						KEY4_PINSOURCE								GPIO_PinSource5
#define 						KEY4_EXTI_LINE								EXTI_Line5
#define 						KEY4_EXTI_IRQ									EXTI9_5_IRQn
#define 						KEY4_IRQHandler								EXTI9_5_IRQHandler

void ADVANCE_TIM_Init(void);
void GENERAL_TIM_Init(void);
void GENERAL_TIM_c_Init(void);
void EXTI_GPIO_Config(void);
#endif