#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "oled.h"
#include "usart.h"	 
#include "dht11.h"

int main(void)
{
	u8 t;
	u8 n = 0;			    
	u8 temperature;  	    
	u8 humidity;
	vu8 key = 0;
	
	delay_init();	                               	  //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 	LED_Init();			                                //LED端口初始化
	OLED_Init();		                               	//初始化OLED   
	
	OLED_ShowString(0, 0, "03180213", 12);
	OLED_ShowString(0, 12, "2021.7.2", 12);
  OLED_ShowString(56, 0, "Gavin", 24);	
	OLED_ShowString(16, 24, "Azure Dragon", 16);  
 	OLED_ShowString(36, 40, "System 1.0", 12);  
 	OLED_ShowString(0, 52, "Humi:   %", 12);  
 	OLED_ShowString(72, 52, "Temp:   C", 12);  
  
	OLED_Refresh_Gram();		//更新显示到OLED 
	t=' ';  
	while(1) 
	{	
		key = KEY_Scan(0); //读取键值
		
		//OLED显示
		if(n % 10 == 0)			//每100ms读取一次
		{									  
			DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值
			OLED_ShowNum(32,52,humidity, 2, 12);
			OLED_Refresh_Gram();   		   
			OLED_ShowNum(104,52,temperature, 2, 12);		//显示湿度	 	   
		}				   
	 	delay_ms(10);
		t++;
//		OLED_ShowChar(48,52,t,12,1);//显示ASCII字符	   
//		OLED_Refresh_Gram();
//		t++;
//		if(t>'~')t=' ';
//		OLED_ShowNum(103,52,t,3,12);//显示ASCII字符的码值 
//		delay_ms(500);
//		LED0=!LED0;
	}	  
}
