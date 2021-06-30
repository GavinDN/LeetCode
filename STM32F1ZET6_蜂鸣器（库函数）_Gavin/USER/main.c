#include "stm32f10x.h"
#include "beep.h"
#include "delay.h"

int main(void)
{
  delay_init();	
	BEEP_Init();
	
  while(1)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);   //���0���رշ�����
		delay_ms(500);                       //��ʱ500ms
		
		GPIO_SetBits(GPIOB, GPIO_Pin_8);     //���1������������
		delay_ms(500);                       //��ʱ500ms
	}
}
