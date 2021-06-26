#include "stm32f10x.h"
#include "delay.h"
#include "led.h"

int main(void)
{
	delay_init();
	LED_Init();
	
  while(1)
	{
		GPIOB->ODR |= 1<<5; //给GPIOB.5高电平 LED0灭
		GPIOE->ODR = ~(1<<5); //给GPIOE.5低电平 LED1亮
		delay_ms(500); //延时500ms
		
		GPIOE->ODR |= 1<<5; //给GPIOE.5高电平 LED1灭
		GPIOB->ODR = ~(1<<5); //给GPIOB.5低电平 LED0亮
		delay_ms(500); //延时500ms
	}
}
