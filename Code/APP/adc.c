#include "adc.h"
/*
u16 get_Adc(u8 ch) {
	ADC1->SQR3 &= 0xffffffe0;//规则序列1 
	ADC1->SQR3 |= ch; //通道ch
	ADC1->CR2 |= 1 << 22;//启动规则转换通道
	while (!(ADC1->SR & 1 << 1)) {
		;//等待转换结束
	}
	return ADC1->DR;//返回digital值
}

void adc_init(void) {
	RCC->APB2ENR |= 1 << 9;//ADC1 时钟使能
	RCC->APB2RSTR |= 1 << 9;//ADC1 复位
	RCC->APB2RSTR &= ~(1 << 9);//复位结束
	RCC->CFGR &= (3 << 14);//分频因子清零

	RCC->CFGR |= 2 << 14;
	ADC1->CR1 &= 0XF0FFFF;//工作模式清零
	ADC1->CR1 |= 0 << 16;//独立工作模式
	ADC1->CR1 &= ~(1 << 8);//非扫描模式
	ADC1->CR2 &= ~(1 << 1);//单次转换模式
	ADC1->CR2 &= ~(7 << 17);
	ADC1->CR2 |= 7 << 17;//软件控制转换
	ADC1->CR2 |= 1 << 20;//使用外部触发(SWSTART) 必须使用一个事件来触发
	ADC1->CR2 &= ~(1 << 11);//右对齐
	ADC1->SQR1 &= ~(0XF << 20);
	ADC1->SQR1 &= 0 << 20;//1个转换在规则序列中 也就是只转换规则序列1
	
	//设置ch 7 的采样时间
	ADC1->SMPR2 = 0x3FFFFFFF;//所有通道的采样周期都为239.5
	ADC1->SMPR2 |= 7 << 24;//通道8 239.5周期
	ADC1->CR2 |= 1 << 0;//使能 ADC1
	ADC1->CR2 |= 1 << 3;//使能 复位 校准
	while (ADC1->CR2 & 1 << 3) {
		;//等待校准结束
	}
	
	ADC1->CR2 |= 1 << 2;//使能 AD 校准
	while (ADC1->CR2 & 1 << 2) {
		;//等待校准结束
	}
	delay_ms(1);
}*/
void Adc_Init(void) {
	//GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;

	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//设置ADC的分频因子 CLKadc=72MHz/6=12MHz

	/*
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//PA1 ADC1 引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//analog input
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化引脚*/

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//disable scan conversion mode
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//disable continue conversion mode
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//disable external (use sofeware )
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;//1一个转换在规则序列中 也就是只转换规则序列1
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_Cmd(ADC1, ENABLE);//开启ADC
	
	ADC_ResetCalibration(ADC1);//重置ADC1的校准寄存器
	while (ADC_GetResetCalibrationStatus(ADC1)) {
		;//等待 重置ADC1的校准寄存器 的完成
	}

	ADC_StartCalibration(ADC1);//校准ADC1
	while (ADC_GetCalibrationStatus(ADC1)){
		;//等待 校准ADC1 的完成
	}

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//使能ADC1的软件启动功能

}

/*
Descrition: 获取通道 ch的转换值
Note:该函数至少需要21us
*/
u16 Get_ADC_Value(u8 ch) {
	//CLKadc=72MHz/6=12MHz
	//采样周期=239.5*CLKadc
	//转换时间=采样周期+12.5)*CLKadc
	//       =239.5+12.5)*CLKadc
	//       =21us
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5);//设置ADC1 ch通道 239.5个采样周期
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)){
		;//这里会持续21us
	}
	return ADC_GetConversionValue(ADC1);
}

