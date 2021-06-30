#include "stm32f10x.h"
#include "beep.h"
#include "delay.h"

int main(void)
{
  delay_init();	
	BEEP_Init();
	
  while(1)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);   //输出0，关闭蜂鸣器
		delay_ms(500);                       //延时500ms
		
		GPIO_SetBits(GPIOB, GPIO_Pin_8);     //输出1，开启蜂鸣器
		delay_ms(500);                       //延时500ms
	}
}
