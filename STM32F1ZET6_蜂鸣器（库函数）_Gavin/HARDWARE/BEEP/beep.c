#include "beep.h"
#include "stm32f10x.h"

void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                  //����ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��GPIOB�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�����������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;             //ѡ��GPIOB.8 -> BEEP
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //����GPIO�˿��ٶ�λ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);                //�ɲ�����ʼ��GPIOB.8�˿�
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_8);                    //���0���رշ�����
}
