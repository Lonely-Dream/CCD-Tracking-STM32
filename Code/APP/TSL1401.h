#ifndef _TSL1401_H
#define _TSL1401_H
/*
Description:
Pins:
PA 0 
PC 2 
PC 0 

Link:
STM32   TSL1401
PA 0 ---- SI
PC 2 ---- CLK
PC 0 ---- AO   (ADC1 ch 10)

Note:
Sensor integration time Tint=(64.5,100 000)us
Clock frequency Fclock=(5,2000)KHz
The relation SI and CLK
*/

#include <system.h>
#include "SysTick.h"
#include "adc.h"

#define TSL_SI  BIT_ADDR(GPIOA_ODR_Addr,0)
#define TSL_CLK BIT_ADDR(GPIOC_ODR_Addr,2)

void TSL1401_Init(void);
void TSL1401_Read(void);


extern u8 ADV[128];

/*
补充曝光时间(根据环境而定) 单位是ms 
Tint2=(0,96); 环境光线越强 Tint2需要越小
*/
extern u8 Tint2;
#endif // !_TSL1401_H

