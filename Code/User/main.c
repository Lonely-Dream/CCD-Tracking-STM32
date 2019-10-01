#include "SysTick.h"
//#include "Motor.h"
#include "usart.h"
#include "TSL1401.h"
//#include "Sensor_inf.h"
//#include "SteeringGear.h"

void InitALL()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//Initialize all the configurations here
	SysTick_Init(72);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	USART1_Init(38400);
	//adc_init();
	TSL1401_Init();

	/*
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	//∂Àø⁄≈‰÷√
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //Õ∆ÕÏ ‰≥ˆ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	PDout(0) = 0;*/
	//PCout(0) = 0;
}	

void delay_s(int a){
	int i=0;
	for(i=0;i<a;++i){
		delay_ms(1000);
	}
}


int main()
{
	int i = 0;
	int j = 0;
	InitALL();
	delay_s(15);

	/*
	//Send flag of start

	USART_SendData(USART1, (u8)(0xAA));
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET) {
		;//waiting 
	}
	USART_ClearFlag(USART1, USART_FLAG_TC);*/

	for (j = 0; j < 0x00ffffff ; ++j) {
		TSL1401_Read();
		delay_ms(100);

		for (i = 0; i < 128; ++i) {
			/*
			USART_SendData(USART1, (u8)(ADV[i] >> 8));
			while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET) {
				;//waiting 
			}
			USART_ClearFlag(USART1, USART_FLAG_TC);*/

			USART_SendData(USART1, ADV[i]);
			while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET) {
				;//waiting 
			}
			USART_ClearFlag(USART1, USART_FLAG_TC);

			/*
			//slip
			USART_SendData(USART1, (u8)0xBB);
			while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET) {
				;//waiting
			}
			USART_ClearFlag(USART1, USART_FLAG_TC);
			*/
			//delay_ms(200);
		}
		delay_ms(100);

		/*
		//Send flag of end
		USART_SendData(USART1, (u8)0x0D);// \r
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET) {
			;//waiting 
		}
		USART_ClearFlag(USART1, USART_FLAG_TC);

		USART_SendData(USART1, (u8)0x0A);// \n
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET) {
			;//waiting 
		}
		USART_ClearFlag(USART1, USART_FLAG_TC);*/
	}
	


	return 0;
}
