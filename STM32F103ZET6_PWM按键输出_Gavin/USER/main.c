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

	delay_init();	    	                            //延时函数初始化	
	KEY_Init();                                     //按键初始化 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	                            //串口初始化为115200
 	LED_Init();			                                //LED端口初始化
 	TIM3_PWM_Init(899, 0);	                        //不分频。PWM频率=72000000/900=80Khz，频率=((1+TIM_Prescaler )/72M)*(1+TIM_Period )
  
	while(1)                                                      
	{
		//delay_ms(10);	
		key = KEY_Scan(0); //读取键值		
		
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
