/*****************************************************************************
*                                                                            *
*  @file     laser_receive.c                                                 *
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
*  2018/10/31 | 1.0.1   | Feipeng Ma       | add the basic function          *
*----------------------------------------------------------------------------*
*****************************************************************************/
#include "laser_receive.h"

static void ADVANCE_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = ADVANCE_TIM_IRQ; 	
		// 设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置子优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
/**
  * @brief  高级定时器PWM输入用到的GPIO初始化
  * @param  无
  * @retval 无
  */
static void ADVANCE_TIM_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(ADVANCE_TIM_CH1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_Init(ADVANCE_TIM_CH1_PORT, &GPIO_InitStructure);	
}



static void ADVANCE_TIM_Mode_Config(void)
{
  // 开启定时器时钟,即内部时钟CK_INT=72M
	ADVANCE_TIM_APBxClock_FUN(ADVANCE_TIM_CLK,ENABLE);

/*--------------------时基结构体初始化-------------------------*/
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period=ADVANCE_TIM_PERIOD;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= ADVANCE_TIM_PSC;	
	// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
	TIM_TimeBaseInit(ADVANCE_TIM, &TIM_TimeBaseStructure);

	/*--------------------输入捕获结构体初始化-------------------*/	
  // 使用PWM输入模式时，需要占用两个捕获寄存器，一个测周期，另外一个测占空比
	
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	// 捕获通道IC1配置
	// 选择捕获通道
  TIM_ICInitStructure.TIM_Channel = ADVANCE_TIM_IC1PWM_CHANNEL;
	// 设置捕获的边沿
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	// 设置捕获通道的信号来自于哪个输入通道，有直连和非直连两种
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	// 1分频，即捕获信号的每个有效边沿都捕获
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	// 不滤波
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
	// 初始化PWM输入模式
  TIM_PWMIConfig(ADVANCE_TIM, &TIM_ICInitStructure);
	
	// 当工作做PWM输入模式时,只需要设置触发信号的那一路即可（用于测量周期）
	// 另外一路（用于测量占空比）会由硬件自带设置，不需要再配置
	
	// 捕获通道IC2配置	
//	TIM_ICInitStructure.TIM_Channel = ADVANCE_TIM_IC1PWM_CHANNEL;
//  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
//  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;
//  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
//  TIM_ICInitStructure.TIM_ICFilter = 0x0;
//  TIM_PWMIConfig(ADVANCE_TIM, &TIM_ICInitStructure);
	
	// 选择输入捕获的触发信号
  TIM_SelectInputTrigger(ADVANCE_TIM, TIM_TS_TI1FP1);		

	// 选择从模式: 复位模式
	// PWM输入模式时,从模式必须工作在复位模式，当捕获开始时,计数器CNT会被复位
  TIM_SelectSlaveMode(ADVANCE_TIM, TIM_SlaveMode_Reset);
  TIM_SelectMasterSlaveMode(ADVANCE_TIM,TIM_MasterSlaveMode_Enable); 

  // 使能捕获中断,这个中断针对的是主捕获通道（测量周期那个）
  TIM_ITConfig(ADVANCE_TIM, TIM_IT_CC1, ENABLE);	
	// 清除中断标志位
	TIM_ClearITPendingBit(ADVANCE_TIM, TIM_IT_CC1);
	
	 // 使能高级控制定时器，计数器开始计数
  TIM_Cmd(ADVANCE_TIM, ENABLE);
}

void ADVANCE_TIM_Init(void)
{
	ADVANCE_TIM_GPIO_Config();
	ADVANCE_TIM_NVIC_Config();
	ADVANCE_TIM_Mode_Config();		
}


static void GENERAL_TIM_c_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(GENERAL_TIM_c_CH1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_c_CH1_PIN;
  GPIO_Init(GENERAL_TIM_c_CH1_PORT, &GPIO_InitStructure);
}

static void GENERAL_TIM_c_Mode_Config(void)
{
  // 开启定时器时钟,即内部时钟CK_INT=72M
	GENERAL_TIM_c_APBxClock_FUN(GENERAL_TIM_c_CLK,ENABLE);
/*--------------------时基结构体初始化-------------------------*/
	// 配置周期，这里配置为100K
	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_c_PERIOD;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_PSC;	
	// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
	TIM_TimeBaseInit(GENERAL_TIM_c, &TIM_TimeBaseStructure);
	

	/*--------------------输出比较结构体初始化-------------------*/	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// 输出比较通道 1
	TIM_OCInitStructure.TIM_Pulse = GENERAL_TIM_CCR2;
	TIM_OC1Init(GENERAL_TIM_c, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(GENERAL_TIM_c, TIM_OCPreload_Enable);
	
	// 使能计数器
	TIM_Cmd(GENERAL_TIM_c, ENABLE);

}



static void GENERAL_TIM_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // 输出比较通道1 GPIO 初始化
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM_CH1_PORT, &GPIO_InitStructure);
}


///*
// * 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
// * TIM_Prescaler和TIM_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可，
// * 另外三个成员是通用定时器和高级定时器才有.
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            都有
// *	TIM_CounterMode			     TIMx,x[6,7]没有，其他都有
// *  TIM_Period               都有
// *  TIM_ClockDivision        TIMx,x[6,7]没有，其他都有
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]才有
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */

/* ----------------   PWM信号 周期和占空比的计算--------------- */
// ARR ：自动重装载寄存器的值
// CLK_cnt：计数器的时钟，等于 Fck_int / (psc+1) = 72M/(psc+1)
// PWM 信号的周期 T = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// 占空比P=CCR/(ARR+1)
/**
  * @brief  通用定时器PWM输出初始化
  * @param  无
  * @retval 无
	* @note   
  */
static void GENERAL_TIM_Mode_Config(void)
{
  // 开启定时器时钟,即内部时钟CK_INT=72M
	GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK,ENABLE);
/*--------------------时基结构体初始化-------------------------*/
	// 配置周期，这里配置为100K
	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_PERIOD;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_PSC;	
	// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
	
	/*--------------------输出比较结构体初始化-------------------*/	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// 输出比较通道 1
	TIM_OCInitStructure.TIM_Pulse = GENERAL_TIM_CCR1;
	TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	// 使能计数器
	TIM_Cmd(GENERAL_TIM, ENABLE);
}


/**
  * @brief  通用定时器PWM输出用到的GPIO和PWM模式初始化
  * @param  无
  * @retval 无
  */
void GENERAL_TIM_Init(void)
{
	GENERAL_TIM_GPIO_Config();
	GENERAL_TIM_Mode_Config();		
}

void GENERAL_TIM_c_Init(void)
{
	GENERAL_TIM_c_GPIO_Config();
	GENERAL_TIM_c_Mode_Config();		
}

/*****************EXTI*********************/
static void EXTI_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_Stru;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_Stru.NVIC_IRQChannel = KEY1_EXTI_IRQ;
	NVIC_Stru.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Stru.NVIC_IRQChannelSubPriority = 1;
	NVIC_Stru.NVIC_IRQChannelCmd =ENABLE;
	NVIC_Init(&NVIC_Stru);
	
	NVIC_Stru.NVIC_IRQChannel = KEY2_EXTI_IRQ;
	NVIC_Init(&NVIC_Stru);
	
	NVIC_Stru.NVIC_IRQChannel = KEY3_EXTI_IRQ;
	NVIC_Init(&NVIC_Stru);
	NVIC_Stru.NVIC_IRQChannel = KEY4_EXTI_IRQ;
	NVIC_Init(&NVIC_Stru);
}
void EXTI_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_Stru;
	EXTI_InitTypeDef EXTI_Stru;
	
	RCC_APB2PeriphClockCmd(KEY1_PORT_CLK|KEY2_PORT_CLK|KEY3_PORT_CLK|KEY4_PORT_CLK,ENABLE);
	EXTI_NVIC_Config();
	GPIO_Stru.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Stru.GPIO_Pin = KEY1_PIN;
	GPIO_Init(KEY1_PORT,&GPIO_Stru);
	
	GPIO_Stru.GPIO_Pin = KEY2_PIN;
	GPIO_Init(KEY2_PORT,&GPIO_Stru);
	
	GPIO_Stru.GPIO_Pin = KEY3_PIN;
	GPIO_Init(KEY3_PORT,&GPIO_Stru);
	
	GPIO_Stru.GPIO_Pin = KEY4_PIN;
	GPIO_Init(KEY4_PORT,&GPIO_Stru);
	
	GPIO_EXTILineConfig(KEY1_PORTSSOURCE,KEY1_PINSOURCE);
	EXTI_Stru.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Stru.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Stru.EXTI_LineCmd = ENABLE;
	EXTI_Stru.EXTI_Line = KEY1_EXTI_LINE;
	EXTI_Init(&EXTI_Stru);
	
	GPIO_EXTILineConfig(KEY2_PORTSSOURCE,KEY2_PINSOURCE);
	EXTI_Stru.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Stru.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Stru.EXTI_LineCmd = ENABLE;
	EXTI_Stru.EXTI_Line = KEY2_EXTI_LINE;
	EXTI_Init(&EXTI_Stru);
	
	GPIO_EXTILineConfig(KEY3_PORTSSOURCE,KEY3_PINSOURCE);
	EXTI_Stru.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Stru.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Stru.EXTI_LineCmd = ENABLE;
	EXTI_Stru.EXTI_Line = KEY3_EXTI_LINE;
	EXTI_Init(&EXTI_Stru);
	
	GPIO_EXTILineConfig(KEY4_PORTSSOURCE,KEY4_PINSOURCE);
	EXTI_Stru.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Stru.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Stru.EXTI_LineCmd = ENABLE;
	EXTI_Stru.EXTI_Line = KEY4_EXTI_LINE;
	EXTI_Init(&EXTI_Stru);
	
}





