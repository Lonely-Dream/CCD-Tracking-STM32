#include "usart.h"

uint16_t r;// the function USART_ReceiveData() returns a value of type uint16_t

void USART1_Init(u32 BaudRate) {
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//open clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//----------------------Configure GPIO-----------------------
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//multiplexing push-pull output复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//Rx
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//floating input 浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//---------------------Configure USART1----------------------
	USART_InitStructure.USART_BaudRate = BaudRate;//set baudrate
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	USART_Cmd(USART1, ENABLE);

	USART_ClearFlag(USART1, USART_FLAG_TC);//clear flag

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//open interrupt of RXNE

	//----------------------Configure NVIC-----------------------
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//Preemption Priority 3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//sub priorty 3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	r = 0;
}

void USART1_IRQHandler(void) {
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		r = USART_ReceiveData(USART1);//get data

		USART_SendData(USART1, r);

		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET) {
			;//waiting 
		}
	}

	USART_ClearFlag(USART1, USART_FLAG_TC);
}
