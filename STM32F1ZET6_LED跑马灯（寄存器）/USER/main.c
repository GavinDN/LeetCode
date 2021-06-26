#include "stm32f10x.h"
#include "delay.h"
#include "led.h"

int main(void)
{
	delay_init();
	LED_Init();
	
  while(1)
	{
		GPIOB->ODR |= 1<<5; //��GPIOB.5�ߵ�ƽ LED0��
		GPIOE->ODR = ~(1<<5); //��GPIOE.5�͵�ƽ LED1��
		delay_ms(500); //��ʱ500ms
		
		GPIOE->ODR |= 1<<5; //��GPIOE.5�ߵ�ƽ LED1��
		GPIOB->ODR = ~(1<<5); //��GPIOB.5�͵�ƽ LED0��
		delay_ms(500); //��ʱ500ms
	}
}
