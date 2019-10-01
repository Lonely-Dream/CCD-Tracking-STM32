#ifndef _ADC_H
#define _ADC_H
/*
Description:
Pins:
.

*/

#include <system.h>
#include "SysTick.h"

u16 Get_ADC_Value(u8 ch);
void Adc_Init(void);

#endif // !_ADC_H

