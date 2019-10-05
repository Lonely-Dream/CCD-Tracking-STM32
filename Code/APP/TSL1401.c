#include "TSL1401.h"

void TSL1401_Init(void) {
	//Init GPIO
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//SI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//CLK
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//AO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//analog input
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);


	//初始化ADC1
	ADCx_Init(ADC1);
}

u8 ADV[128] = { 0 };
u8 Tint2 = 50;//补充曝光时间(根据环境而定) 单位是ms
/*
采用单次曝光 预计曝光时间是Tint=Tint1+Tint2=Tint2+4.884 ms 
CLK=(5,2000)KHz
在这里使用 Tclk(H)=11us Tclk(L)=11us
周期为22us的时钟(45.454KHz)
*/
void TSL1401_Read(void) {
	
	u8 i = 0;

	//这是为了清除之前积分数据 重新曝光
	TSL_CLK = 1;
	TSL_SI = 0;
	delay_us(11);//初始状态

	TSL_CLK = 0;
	delay_us(11);
	TSL_SI = 1;//-------SI高电平持续超过一个时钟周期
	delay_us(11);

	TSL_CLK = 1;
	delay_us(11);
	TSL_SI = 0;//-------SI高电平持续超过一个时钟周期
	delay_us(11);//TSL 启动开始工作

	for (i = 0; i < 128; ++i) {
		TSL_CLK = 0;
		ADV[i] = (u8)(Get_ADCx_Value(ADC1,ADC_Channel_10)>>4);//预计22us
		//从12位映射到8位
		
		TSL_CLK = 1;
		delay_us(22);
	}
	TSL_CLK = 0;
	delay_us(22);//第129个时钟周期完成

	//以上曝光时间为 Tint1=(128-18)*44+44=4884us
	delay_ms(Tint2);//补充曝光时间 Tint2=7000us

	//曝光完成  累计曝光时间Tint=Tint1+Tint2=4884+7000=13.884ms 
	//进行采集
	TSL_SI = 1;//-------SI高电平持续超过一个时钟周期
	delay_us(11);

	TSL_CLK = 1;
	delay_us(11);
	TSL_SI = 0;//-------SI高电平持续超过一个时钟周期
	delay_us(11);//TSL 启动开始工作

	for (i = 0; i < 128; ++i) {
		TSL_CLK = 0;
		ADV[i] = (u8)(Get_ADCx_Value(ADC1,ADC_Channel_10) >> 4);//预计22us
		//从12位映射到8位

		TSL_CLK = 1;
		delay_us(22);
	}
	TSL_CLK = 0;
}