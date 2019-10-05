#include "adc.h"

void ADCx_Init(ADC_TypeDef* ADCx) {
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
	ADC_Init(ADCx, &ADC_InitStructure);

	ADC_Cmd(ADCx, ENABLE);//开启ADC
	
	ADC_ResetCalibration(ADCx);//重置ADC1的校准寄存器
	while (ADC_GetResetCalibrationStatus(ADCx)) {
		;//等待 重置ADC1的校准寄存器 的完成
	}

	ADC_StartCalibration(ADCx);//校准ADCx
	while (ADC_GetCalibrationStatus(ADCx)){
		;//等待 校准ADC1 的完成
	}

	ADC_SoftwareStartConvCmd(ADCx, ENABLE);//使能ADC1的软件启动功能

}

/*
Descrition: 获取通道 ch的转换值
Note:该函数至少需要21us
*/
u16 Get_ADCx_Value(ADC_TypeDef* ADCx,u8 ch) {
	//CLKadc=72MHz/6=12MHz
	//采样周期=239.5*CLKadc
	//转换时间=采样周期+12.5)*CLKadc
	//       =239.5+12.5)*CLKadc
	//       =21us
	ADC_RegularChannelConfig(ADCx, ch, 1, ADC_SampleTime_239Cycles5);//设置ADC1 ch通道 239.5个采样周期
	
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);
	while (!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC)){
		;//这里会持续21us
	}
	return ADC_GetConversionValue(ADCx);
}

