#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

int main(void)
{	
	delay_init();
	LED_Init(); //LED��ʼ��
	
  while(1)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5); //��LED0
		GPIO_ResetBits(GPIOE, GPIO_Pin_5); //��LED1
		
		delay_ms(500); //��ʱ50ms
		
		GPIO_ResetBits(GPIOB, GPIO_Pin_5); //��LED0
		GPIO_SetBits(GPIOE, GPIO_Pin_5); //�ص�LED1
		delay_ms(500); //��ʱ50ms
	}
}
