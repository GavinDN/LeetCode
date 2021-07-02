#include "timer.h"
#include "led.h"

void TIM3_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//ʹ�ܶ�ʱ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);            
	
	//��ʼ����ʱ��������NVIC
	TIM_TimeBaseInitStructure.TIM_Period = arr;                     //�����Զ�װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;                  //����Ԥ��Ƶϵ��
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //����ģʽΪ���ϼ���
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ѡ����ЧֵΪ1
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	//������ʱ���ж�
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);                      //ʹ�ܶ�ʱ��3�ĸ����ж�
	
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                 //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);                                 //��ʼ��NVIC�Ĵ���
	
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM3, ENABLE);
}

/***********************************************************************
*                             �жϷ�����                             *
***********************************************************************/
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		LED1 = !LED1;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}
