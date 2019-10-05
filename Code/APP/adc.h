#ifndef _ADC_H
#define _ADC_H
/*
Description:
Pins:
.

*/

#include <system.h>

void ADCx_Init(ADC_TypeDef* ADCx);
u16 Get_ADCx_Value(ADC_TypeDef* ADCx, u8 ch);

#endif // !_ADC_H

