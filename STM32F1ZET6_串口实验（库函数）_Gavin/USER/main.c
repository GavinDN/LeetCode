#include "stm32f10x.h"

void My_USART1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
/********************************************************************************************************************
	                                          GPIOA.9 GPIOA.10 USART1 的初始化
********************************************************************************************************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 115200;                                    //设置波特率为115200
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //硬件流控制，设为不使用
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;                 //发送、接收都使能
	USART_InitStructure.USART_Parity = USART_Parity_No;                             //设置奇偶校验，设为不使用
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //设置停止位，设为1
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //设置字长，因为没有奇偶校验位，所以此处设为8
	USART_Init(USART1, &USART_InitStructure);                                       //初始化串口USART1设置
	
	USART_Cmd(USART1, ENABLE);                                                      //使能串口函数,使能串口1
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                                  //开启接收中断，接收到缓冲区非空后，执行中断服务函数
	
/********************************************************************************************************************
	                                                中断的初始化
********************************************************************************************************************/	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;                               //设置通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                                 //开启中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;                       //设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                              //子优先级
	NVIC_Init(&NVIC_InitStructure);
}

void USART1_IRQHandler(void)
{
	u8 num;
	
	if(USART_GetFlagStatus(USART1, USART_IT_RXNE))
	{
		num = USART_ReceiveData(USART1);
		USART_SendData(USART1, num);
	}
}

int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //把系统中断的优先级分组，设置为2，2位抢占、2位响应
	My_USART1_Init();
  while(1);
}
