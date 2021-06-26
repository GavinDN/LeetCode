#include "led.h"
#include "stm32f10x.h"

void LED_Init()
{
	RCC->APB2ENR |= 1<<3; // ʹ��GPIOB "|=" ����ֻ�ı���Ҫ�仯��ֵ����������Ҫ�ı��ֵ
	RCC->APB2ENR |= 1<<6; // ʹ��GPIOE
	
	//GPIOB.5
	GPIOB->CRL &= 0XFF0FFFFF; //CRL���Ƶ�λ��GPIO �Ƚ�GPIOB.5��λ���� 1111 1111 0000 1111 1111 1111 1111 1111
	GPIOB->CRL |= 0X00300000; //ʹ�û����� "|=" ����ֻ�ı���Ҫ�仯��ֵ����������Ҫ�ı��ֵ
	GPIOB->ODR |= 1<<5; //��GPIOB.5�ߵ�ƽ
	
	//GPIOE.5
	GPIOE->CRL &= 0XFF0FFFFF; //CRL���Ƶ�λ��GPIO �Ƚ�GPIOE.5��λ���� 1111 1111 0000 1111 1111 1111 1111 1111
	GPIOE->CRL |= 0X00300000; //ʹ�û����� "|=" ����ֻ�ı���Ҫ�仯��ֵ����������Ҫ�ı��ֵ
	GPIOE->ODR |= 1<<5; //��GPIOE.5�ߵ�ƽ
}
