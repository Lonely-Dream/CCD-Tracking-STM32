#ifndef __MOTOR_H
#define __MOTOR_H
/*
Description:
Pins:
PB0 PB1 PC4 PC5 //control direction
PC6 PC7 PC8 PC9 //control size by timer8 ch1-ch4

Table:(PWMmax=7200)
D RB PB1 TIM8->CCR4 C9 (pos EN=1 Vmax=PWMmin) (neg EN=0 Vmax=PWMmax)
C RF PC5 TIM8->CCR3 C8 (pos EN=1 Vmax=PWMmin) (neg EN=0 Vmax=PWMmax)
B LF PB0 TIM8->CCR2 C7 (pos EN=1 Vmax=PWMmin) (neg EN=0 Vmax=PWMmax)
A LB PC4 TIM8->CCR1 C6 (pos EN=1 Vmax=PWMmin) (neg EN=0 Vmax=PWMmax)
*/


#include <system.h>	 

#define PWMRB   TIM8->CCR4  
#define PWMRF   TIM8->CCR3  
#define PWMLF   TIM8->CCR2 
#define PWMLB   TIM8->CCR1 
#define ENRB   PBout(1)  
#define ENRF   PCout(5)  
#define ENLF   PBout(0)  
#define ENLB   PCout(4)  

void PWM_Init(u16 arr,u16 psc);
//void Motor_Init(void);
void Go(int v);
void Back(int v);
void TurnLeft(int v,int pwm);
void TurnRight(int v,int pwm);
void Stop(void);
void VerticalR(int v);
void VerticalRLeft(int v,int pwm);
void VerticalRRight(int v,int pwm);

void VerticalL(int v);
void VerticalLLeft(int v,int pwm);
void VerticalLRight(int v,int pwm);

void test(int a,int b,int c,int d);
void test_en(int a,int b,int c,int d);
#endif

