#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "stm32f10x.h"

/******************************************************************************
                                ������ʼ������
******************************************************************************/
void KEY_Init(void)                                                          //IO��ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;                                       //����һ���ṹ������
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);  //ʹ��PORTA,PORTEʱ��
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                              //ѡ����������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;            //��GPIOE.2 GPIOE.3 GPIOE.4���г�ʼ�����ã�KEY0-KEY2��
	GPIO_Init(GPIOE, &GPIO_InitStructure);                                     //��ʼ��GPIOE2,3,4
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;                              //ѡ����������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                                  //��GPIOA.0���г�ʼ�����ã�KEY_UP��
	GPIO_Init(GPIOA, &GPIO_InitStructure);                                     //��ʼ��GPIOA0 
}

/******************************************************************************
                                 ������ȡ����
*******************************************************************************
���ذ���ֵ
mode:0,��֧��������;1,֧��������;
0��û���κΰ�������
1��KEY0����
2��KEY1����
3��KEY2���� 
4��KEY3���� WK_UP
ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!
******************************************************************************/
u8 KEY_Scan(u8 mode)
{
	static u8 key_up = 1; //����key_up�ĳ�ֵ
	
	if(mode) key_up = 1;  //����ѡ�񰴼��Ƿ�֧�ֳ���
	
	if(key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || WK_UP == 1))
	{
		delay_ms(10); //��������
		key_up = 0;
		if(KEY0 == 0)return KEY0_PRES;
		else if(KEY1 == 0)return KEY1_PRES;
		else if(KEY2 == 0)return KEY2_PRES;
		else if(WK_UP == 1)return WKUP_PRES;
	}else if (KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && WK_UP == 0) key_up = 1;
	return 0; //�ް�������
}
