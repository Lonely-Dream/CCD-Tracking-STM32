#ifndef __MOTOR_H
#define __MOTOR_H
/*
Description:
Pins:
PB4  M L ain1
PB5  M L ain2
PB6  M L a pwm
PB7  M R bin1
PB8  M R bin2
PB9  M R b pwm

Table:

xIN1    0    1   0
xIN2    0    0   1
Result Stop For Rev
*/


#include <system.h>	 

#define PWML   TIM4->CCR1
#define PWMR   TIM4->CCR4
#define LIN1   PBout(4)  
#define LIN2   PBout(5)  
#define RIN1   PBout(7)  
#define RIN2   PBout(8)  

//void PWM_Init(u16 arr,u16 psc);
void Motor_Init(void);
void Go(int v);
void Back(int v);
void TurnLeft(int v,int pwm);
void TurnRight(int v,int pwm);
void Stop(void);

void test(int a,int b,int c,int d);

#endif

