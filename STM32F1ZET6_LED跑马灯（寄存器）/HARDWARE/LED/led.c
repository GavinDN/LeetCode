#include "led.h"
#include "stm32f10x.h"

void LED_Init()
{
	RCC->APB2ENR |= 1<<3; // 使能GPIOB "|=" 可以只改变需要变化的值，保留不需要改变的值
	RCC->APB2ENR |= 1<<6; // 使能GPIOE
	
	//GPIOB.5
	GPIOB->CRL &= 0XFF0FFFFF; //CRL控制低位的GPIO 先将GPIOB.5的位清零 1111 1111 0000 1111 1111 1111 1111 1111
	GPIOB->CRL |= 0X00300000; //使用或运算 "|=" 可以只改变需要变化的值，保留不需要改变的值
	GPIOB->ODR |= 1<<5; //给GPIOB.5高电平
	
	//GPIOE.5
	GPIOE->CRL &= 0XFF0FFFFF; //CRL控制低位的GPIO 先将GPIOE.5的位清零 1111 1111 0000 1111 1111 1111 1111 1111
	GPIOE->CRL |= 0X00300000; //使用或运算 "|=" 可以只改变需要变化的值，保留不需要改变的值
	GPIOE->ODR |= 1<<5; //给GPIOE.5高电平
}
