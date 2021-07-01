#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "beep.h"

/**********************************************************
*                  外部中断0服务程序                      *
**********************************************************/
void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	KEY_Init();                                                 //按键初始化函数，初始化IO口为输入
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);        //开启IO口复位时钟，APB2的外设时钟使能
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4); //设置IO口与中断线的映射关系
	
	//初始化结构体的成员变量
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;                  //初始化中断线4
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;         //模式设置为中断
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;     //设置下降沿触发
	EXTI_Init(&EXTI_InitStructure);                             //初始化线上中断，设置触发条件
	
	//设置中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;            //选择通道，外部中断线4
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;          //设置子优先级
	NVIC_Init(&NVIC_InitStructure);                             //配置中断分组（NVIC），并使能中断
}


/**********************************************************
*                      中断服务函数                       *
**********************************************************/
void EXTI4_IRQHandler(void)
{
	delay_ms(10);                                                //消除抖动
	if(KEY0 == 0)
	{
		LED0 = !LED0;
		LED1 = !LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line4);                          //把线4的中断标志位清除，方便下次再进入中断
}
