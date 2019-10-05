#include "Motor.h"

void PWM_Init(u16 arr,u16 psc)
{		 		
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	//Motor_Init();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //使能GPIO外设时钟使能
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_9; //TIM4_CH1 //TIM4_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;                            //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	//TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	//TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

	TIM_CtrlPWMOutputs(TIM4,ENABLE);	//MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1预装载使能	
	//TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1预装载使能	
	//TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1预装载使能		
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH4预装载使能	 
	
	TIM_ARRPreloadConfig(TIM4, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM4, ENABLE);  //使能TIM
}
void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB 端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_4 | GPIO_Pin_5;	//端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
	GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 

	PWM_Init(7199, 0);
}


//Correction factor for the left motor
u8 CF_L = 100;

//Correction factor for the right motor
u8 CF_R = 100;


/*
v =(0,100)
*/
void Go(int v){
	LIN1 = 1;
	LIN2 = 0;
	RIN1 = 1;
	RIN2 = 0;

	PWML = (u32)(0.72 * CF_L * v);
	PWMR = (u32)(0.72 * CF_R * v);
}

void Back(int v){
	LIN1 = 0;
	LIN2 = 1;
	RIN1 = 0;
	RIN2 = 1;

	PWML = (u32)(0.72 * CF_L * v);
	PWMR = (u32)(0.72 * CF_R * v);
}

/*
pwm control left motor 
pwm =(0,100)
*/
void TurnLeft(int v, int pwm){
	LIN1 = 1;
	LIN2 = 0;
	RIN1 = 1;
	RIN2 = 0;

	PWML = (u32)(0.0072 * CF_L * v * pwm);
	PWMR = (u32)(0.72 * CF_R * v);
}

void TurnRight(int v, int pwm){
	LIN1 = 1;
	LIN2 = 0;
	RIN1 = 1;
	RIN2 = 0;

	PWML = (u32)(0.72 * CF_L * v);
	PWMR = (u32)(0.0072 * CF_R * v * pwm);
}

void Stop(void){
	LIN1 = 0;
	LIN2 = 0;
	RIN1 = 0;
	RIN2 = 0;

	PWML = 0;
	PWMR = 0;
}

void test(int a,int b, int c,int d){
	PBout(6) = a;
	PBout(7) = b;
	PBout(8) = c;
	PBout(9) = d;
}


