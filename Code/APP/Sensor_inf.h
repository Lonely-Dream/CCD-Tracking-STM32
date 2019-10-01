#ifndef _Sensor_inf_H
#define _Sensor_inf_H
/*
Description:
Pins:
PB4 PB5 //Sensor at Front
PB6 PB7 //Sensor at LEFT
PB8 PB9 //Sensor at Right
*/

#include "system.h"

#define SFL BIT_ADDR(GPIOB_IDR_Addr,4)
#define SFR BIT_ADDR(GPIOB_IDR_Addr,5)
#define SLL BIT_ADDR(GPIOB_IDR_Addr,10)
#define SLR BIT_ADDR(GPIOB_IDR_Addr,11)
#define SRL BIT_ADDR(GPIOB_IDR_Addr,13)
#define SRR BIT_ADDR(GPIOB_IDR_Addr,9)


void Sensor_Init(void);


#endif
