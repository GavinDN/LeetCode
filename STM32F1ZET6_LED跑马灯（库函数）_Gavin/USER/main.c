#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

int main(void)
{	
	delay_init();
	LED_Init(); //LED初始化
	
  while(1)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5); //关LED0
		GPIO_ResetBits(GPIOE, GPIO_Pin_5); //开LED1
		
		delay_ms(500); //延时50ms
		
		GPIO_ResetBits(GPIOB, GPIO_Pin_5); //开LED0
		GPIO_SetBits(GPIOE, GPIO_Pin_5); //关灯LED1
		delay_ms(500); //延时50ms
	}
}
