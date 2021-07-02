#include "timer.h"
#include "led.h"

void TIM3_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//使能定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);            
	
	//初始化定时器，配置NVIC
	TIM_TimeBaseInitStructure.TIM_Period = arr;                     //设置自动装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;                  //设置预分频系数
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //设置模式为向上计数
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //选择有效值为1
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	//开启定时器中断
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);                      //使能定时器3的更新中断
	
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                 //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);                                 //初始化NVIC寄存器
	
	//使能定时器
	TIM_Cmd(TIM3, ENABLE);
}

/***********************************************************************
*                             中断服务函数                             *
***********************************************************************/
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		LED1 = !LED1;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}
