/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "laser_receive.h"
#include "bsp_led.h"
#include "bsp_usart.h"
extern volatile uint32_t time_7;
extern volatile uint32_t time_6;
extern volatile uint32_t c_flag;
extern volatile uint32_t be_attack;
extern volatile uint32_t be_cure;
__IO uint16_t IC2Value = 0;
__IO uint16_t IC1Value = 0;
extern volatile float DutyCycle;
extern volatile float Frequency;

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

void TIM7_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM7,TIM_IT_Update)!=RESET)
	{
		time_7++;
		TIM_ClearITPendingBit(TIM7,TIM_FLAG_Update);
	}
}

void TIM6_IRQHandler(void)
{
		if ( TIM_GetITStatus( TIM6, TIM_IT_Update) != RESET ) 
	{	
		time_6++;
		TIM_ClearITPendingBit(TIM6 , TIM_IT_Update);  		 
	}		

}

void ADVANCE_TIM_IRQHandler(void)
{
  /* 清除中断标志位 */
  TIM_ClearITPendingBit(ADVANCE_TIM, TIM_IT_CC1);

  /* 获取输入捕获值 */
  IC1Value = TIM_GetCapture1(ADVANCE_TIM);
  IC2Value = TIM_GetCapture2(ADVANCE_TIM);
	
  // 注意：捕获寄存器CCR1和CCR2的值在计算占空比和频率的时候必须加1
	if (IC1Value != 0)
  {
    /* 占空比计算 */
    DutyCycle = (float)((IC2Value+1) * 100) / (IC1Value+1);

    /* 频率计算 */
    Frequency = (72000000/(ADVANCE_TIM_PSC+1))/(float)(IC1Value+1);
		if(Frequency>=34000&&Frequency<=38000)
		{
			be_attack = 1;
			c_flag = 1;
		}
		if(Frequency>=12000&&Frequency<=15000)
		{
			be_cure = 1;
			c_flag = 1;
		}		
  }
  else
  {
    DutyCycle = 0;
    Frequency = 0;
		be_attack = 0;
		be_cure = 0;
		c_flag = 0;
  }
}

void KEY1_IRQHandler(void)
{
	if(EXTI_GetITStatus(KEY1_EXTI_LINE) != RESET)
	{
	TIM_Cmd(GENERAL_TIM_c, DISABLE);
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = GENERAL_TIM_CCR2;
	TIM_OC1Init(GENERAL_TIM_c, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(GENERAL_TIM_c, TIM_OCPreload_Enable);
	TIM_Cmd(GENERAL_TIM_c, ENABLE);
	
	
		EXTI_ClearITPendingBit(KEY1_EXTI_LINE);
	}
}

void KEY2_IRQHandler(void)
{
	if(EXTI_GetITStatus(KEY2_EXTI_LINE) != RESET)
	{
		TIM_Cmd(GENERAL_TIM_c, DISABLE);
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = PLANE_1;
	TIM_OC1Init(GENERAL_TIM_c, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(GENERAL_TIM_c, TIM_OCPreload_Enable);
	TIM_Cmd(GENERAL_TIM_c, ENABLE);
		
		EXTI_ClearITPendingBit(KEY2_EXTI_LINE);
	}

}

void KEY3_IRQHandler(void)
{
	if(EXTI_GetITStatus(KEY3_EXTI_LINE) != RESET)
	{
		TIM_Cmd(GENERAL_TIM_c, DISABLE);
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = PLANE_2;
	TIM_OC1Init(GENERAL_TIM_c, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(GENERAL_TIM_c, TIM_OCPreload_Enable);
	TIM_Cmd(GENERAL_TIM_c, ENABLE);
		EXTI_ClearITPendingBit(KEY3_EXTI_LINE);
	}

}

void KEY4_IRQHandler(void)
{
	if(EXTI_GetITStatus(KEY4_EXTI_LINE) != RESET)
	{
		TIM_Cmd(GENERAL_TIM_c, DISABLE);
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = PLANE_3;
	TIM_OC1Init(GENERAL_TIM_c, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(GENERAL_TIM_c, TIM_OCPreload_Enable);
	TIM_Cmd(GENERAL_TIM_c, ENABLE);
		EXTI_ClearITPendingBit(KEY4_EXTI_LINE);
	}

}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
