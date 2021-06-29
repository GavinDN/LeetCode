#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "sys.h"
#include "beep.h"

int main(void)
{
	vu8 key = 0;
	delay_init();
	BEEP_Init();
	LED_Init();
	KEY_Init();
	LED0 = 0;
	
  while(1)
	{
		key = KEY_Scan(0); //��ȡ��ֵ
		
		if(key)
		{
			switch(key)
			{
				case KEY0_PRES: //KEY0
					LED0 =! LED0; //LED0״̬��ת
					break;
				case KEY1_PRES: //KEY1
					LED1 =! LED1; //LED1״̬��ת
					break;
				case KEY2_PRES: //KET2
					BEEP =! BEEP; //������״̬��ת
					break;
				case WKUP_PRES: //KEY_UP
					LED1 =! LED1; //LED1״̬��ת
					LED0 =! LED0; //LED0״̬��ת
					break;
			}
		}else delay_ms(10);
	}
}
