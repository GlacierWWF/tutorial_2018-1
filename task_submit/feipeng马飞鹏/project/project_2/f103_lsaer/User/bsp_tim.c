#include "bsp_tim.h"

static void TIM_Configuration()
{
	TIM_TimeBaseInitTypeDef TIM_Structure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	TIM_Structure.TIM_Prescaler = 71;
	TIM_Structure.TIM_Period = 999;
	TIM_TimeBaseInit(TIM6,&TIM_Structure);
	TIM_ClearFlag(TIM6,TIM_FLAG_Update);
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM6,ENABLE);
}

static void NVIC_Configuration()
{
		NVIC_InitTypeDef NVIC_InitStructure; 
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
		NVIC_Init(&NVIC_InitStructure);

}

void Basic_TIM6_Init()
{
	NVIC_Configuration();
	TIM_Configuration();
}