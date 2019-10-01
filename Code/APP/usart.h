#ifndef _USART_H
#define _USART_H
/*
Description:
Pins:
PA9  TX
PA10 RX

Link:
 STM32    Other
PA 9(TX)---RX
PA10(RX)---TX

*/

#include <system.h>

void USART1_Init(u32 BaudRate);
extern uint16_t r;// the function USART_ReceiveData() returns a value of type uint16_t

#endif // !_USART_H

