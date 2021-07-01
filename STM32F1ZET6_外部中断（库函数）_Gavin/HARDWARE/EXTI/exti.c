#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "beep.h"

/**********************************************************
*                  �ⲿ�ж�0�������                      *
**********************************************************/
void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	KEY_Init();                                                 //������ʼ����������ʼ��IO��Ϊ����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);        //����IO�ڸ�λʱ�ӣ�APB2������ʱ��ʹ��
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4); //����IO�����ж��ߵ�ӳ���ϵ
	
	//��ʼ���ṹ��ĳ�Ա����
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;                  //��ʼ���ж���4
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;         //ģʽ����Ϊ�ж�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;     //�����½��ش���
	EXTI_Init(&EXTI_InitStructure);                             //��ʼ�������жϣ����ô�������
	
	//�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;            //ѡ��ͨ�����ⲿ�ж���4
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //������ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;          //���������ȼ�
	NVIC_Init(&NVIC_InitStructure);                             //�����жϷ��飨NVIC������ʹ���ж�
}


/**********************************************************
*                      �жϷ�����                       *
**********************************************************/
void EXTI4_IRQHandler(void)
{
	delay_ms(10);                                                //��������
	if(KEY0 == 0)
	{
		LED0 = !LED0;
		LED1 = !LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line4);                          //����4���жϱ�־λ����������´��ٽ����ж�
}
