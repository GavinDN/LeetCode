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
	
	delay_init();	                               	  //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
 	LED_Init();			                                //LED�˿ڳ�ʼ��
	OLED_Init();		                               	//��ʼ��OLED   
	
	OLED_ShowString(0, 0, "03180213", 12);
	OLED_ShowString(0, 12, "2021.7.2", 12);
  OLED_ShowString(56, 0, "Gavin", 24);	
	OLED_ShowString(16, 24, "Azure Dragon", 16);  
 	OLED_ShowString(36, 40, "System 1.0", 12);  
 	OLED_ShowString(0, 52, "Humi:   %", 12);  
 	OLED_ShowString(72, 52, "Temp:   C", 12);  
  
	OLED_Refresh_Gram();		//������ʾ��OLED 
	t=' ';  
	while(1) 
	{	
		key = KEY_Scan(0); //��ȡ��ֵ
		
		//OLED��ʾ
		if(n % 10 == 0)			//ÿ100ms��ȡһ��
		{									  
			DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ
			OLED_ShowNum(32,52,humidity, 2, 12);
			OLED_Refresh_Gram();   		   
			OLED_ShowNum(104,52,temperature, 2, 12);		//��ʾʪ��	 	   
		}				   
	 	delay_ms(10);
		t++;
//		OLED_ShowChar(48,52,t,12,1);//��ʾASCII�ַ�	   
//		OLED_Refresh_Gram();
//		t++;
//		if(t>'~')t=' ';
//		OLED_ShowNum(103,52,t,3,12);//��ʾASCII�ַ�����ֵ 
//		delay_ms(500);
//		LED0=!LED0;
	}	  
}
