#include "SteeringGear.h"

void GPIOInit(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	PCout(13)=0;
	PCout(14)=1;
}
void TIM3_CH1_PWM_Init(u16 per, u16 psc){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//1234
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//¸´ÓÃÍÆÍìÊä³ö
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);//¸Ä±äÖ¸¶¨¹Ü½ÅµÄÓ³Éä	
	
	TIM_TimeBaseInitStructure.TIM_Period=per;   //×Ô¶¯×°ÔØÖµ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //·ÖÆµÏµÊý 16bit 1-65536
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //ÉèÖÃÏòÉÏ¼ÆÊýÄ£Ê½
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);	
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//?
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	
	TIM_OC1Init(TIM3,&TIM_OCInitStructure); //Êä³ö±È½ÏÍ¨µÀ1³õÊ¼»¯
	
	TIM_CtrlPWMOutputs(TIM3,ENABLE);
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable); //Ê¹ÄÜTIMxÔÚ CCR1 ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);//Ê¹ÄÜÔ¤×°ÔØ¼Ä´æÆ÷
	
	TIM_Cmd(TIM3,ENABLE); //Ê¹ÄÜ¶¨Ê±Æ÷
}

void SteeringGearInit(void){
	GPIOInit();
	TIM3_CH1_PWM_Init(200, 7199);
	
}

/*
angle=(0,180)
*/
void setSteeringGearAngle(int angle){
	TIM3->CCR1=angle;
}
