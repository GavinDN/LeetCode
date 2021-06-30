#include "beep.h"
#include "stm32f10x.h"

void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                  //定义结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能GPIOB端口时钟
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //设置推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;             //选择GPIOB.8 -> BEEP
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //设置GPIO端口速度位50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);                //由参数初始化GPIOB.8端口
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_8);                    //输出0，关闭蜂鸣器
}
