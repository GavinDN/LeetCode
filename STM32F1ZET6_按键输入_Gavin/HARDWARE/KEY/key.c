#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "stm32f10x.h"

/******************************************************************************
                                按键初始化函数
******************************************************************************/
void KEY_Init(void)                                                          //IO初始化
{
	GPIO_InitTypeDef GPIO_InitStructure;                                       //定义一个结构体类型
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);  //使能PORTA,PORTE时钟
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                              //选择输入上拉模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;            //对GPIOE.2 GPIOE.3 GPIOE.4进行初始化配置（KEY0-KEY2）
	GPIO_Init(GPIOE, &GPIO_InitStructure);                                     //初始化GPIOE2,3,4
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;                              //选择输入下拉模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                                  //对GPIOA.0进行初始化配置（KEY_UP）
	GPIO_Init(GPIOA, &GPIO_InitStructure);                                     //初始化GPIOA0 
}

/******************************************************************************
                                 按键读取函数
*******************************************************************************
返回按键值
mode:0,不支持连续按;1,支持连续按;
0，没有任何按键按下
1，KEY0按下
2，KEY1按下
3，KEY2按下 
4，KEY3按下 WK_UP
注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3!!
******************************************************************************/
u8 KEY_Scan(u8 mode)
{
	static u8 key_up = 1; //设置key_up的初值
	
	if(mode) key_up = 1;  //用于选择按键是否支持长按
	
	if(key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || WK_UP == 1))
	{
		delay_ms(10); //按键消抖
		key_up = 0;
		if(KEY0 == 0)return KEY0_PRES;
		else if(KEY1 == 0)return KEY1_PRES;
		else if(KEY2 == 0)return KEY2_PRES;
		else if(WK_UP == 1)return WKUP_PRES;
	}else if (KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && WK_UP == 0) key_up = 1;
	return 0; //无按键按下
}
