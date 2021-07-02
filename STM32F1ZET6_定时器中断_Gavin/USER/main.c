#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "timer.h"

int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	LED_Init();
	
	TIM3_Int_Init(4999, 7199); //Tout(Òç³öÊ±¼ä) = (ARR+1)(PSC+1)/Tclk

	
  while(1)
	{
		LED0 = !LED0;
		delay_ms(200);
	}
}
