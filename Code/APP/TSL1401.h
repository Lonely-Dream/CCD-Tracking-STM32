#ifndef _TSL1401_H
#define _TSL1401_H
/*
Description:
Pins:
PA 7
PA 2
PA 3

Link:
STM32   TSL1401
PA 7 ---- SI
PA 2 ---- CLK
PA 3 ---- AO   (ADC ch 3)

Note:
Sensor integration time Tint=(64.5,100 000)us
Clock frequency Fclock=(5,2000)KHz
The relation SI and CLK
*/

#include <system.h>
#include "SysTick.h"
#include "adc.h"

#define TSL_SI  BIT_ADDR(GPIOA_ODR_Addr,7)
#define TSL_CLK BIT_ADDR(GPIOA_ODR_Addr,2)

void TSL1401_Init(void);
void TSL1401_Read(void);
extern u8 ADV[128];

#endif // !_TSL1401_H

