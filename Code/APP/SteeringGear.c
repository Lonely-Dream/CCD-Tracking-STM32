#include "SteeringGear.h"

void TIM2_CH3_PWM_Init(u16 per, u16 psc){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	TIM_TimeBaseInitStructure.TIM_Period=per;   //×Ô¶¯×°ÔØÖµ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //·ÖÆµÏµÊý 16bit 1-65536
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //ÉèÖÃÏòÉÏ¼ÆÊýÄ£Ê½
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);	
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//?
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	
	TIM_OC3Init(TIM2,&TIM_OCInitStructure); //ch3
	
	TIM_CtrlPWMOutputs(TIM2,ENABLE);
	
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable); //Ê¹ÄÜTIMxÔÚ CCR1 ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	
	TIM_ARRPreloadConfig(TIM2,ENABLE);//Ê¹ÄÜÔ¤×°ÔØ¼Ä´æÆ÷
	
	TIM_Cmd(TIM2,ENABLE); //Ê¹ÄÜ¶¨Ê±Æ÷
}

void SteeringGearInit(void){

	TIM2_CH3_PWM_Init(1999, 719);
	
}

/*
angle=(0,180)
*/
void setSteeringGearAngle(int angle){
	TIM2->CCR3=angle;
}
