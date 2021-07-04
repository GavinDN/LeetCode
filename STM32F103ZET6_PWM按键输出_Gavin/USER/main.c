#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"

int main(void)
{	
	vu8 key = 0;	
	u16 led0pwmval = 0;

	delay_init();	    	                            //��ʱ������ʼ��	
	KEY_Init();                                     //������ʼ�� 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	                            //���ڳ�ʼ��Ϊ115200
 	LED_Init();			                                //LED�˿ڳ�ʼ��
 	TIM3_PWM_Init(899, 0);	                        //����Ƶ��PWMƵ��=72000000/900=80Khz��Ƶ��=((1+TIM_Prescaler )/72M)*(1+TIM_Period )
  
	while(1)                                                      
	{
		//delay_ms(10);	
		key = KEY_Scan(0); //��ȡ��ֵ		
		
		if(key)
		{
			switch(key)
			{
				case KEY0_PRES: //KEY0
					led0pwmval = 0;
					break;
				case KEY1_PRES: //KEY1
					led0pwmval = 224;
					break;
				case KEY2_PRES: //KET2
					led0pwmval = 449;
					break;
				case WKUP_PRES: //KEY_UP
					led0pwmval = 899;
					break;
			}
		}else delay_ms(10);
										 
		TIM_SetCompare2(TIM3, led0pwmval);		   
	}	 
}	 
