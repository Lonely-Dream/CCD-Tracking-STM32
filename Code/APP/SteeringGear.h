#ifndef _SteeringGear_H
#define _SteeringGear_H

/*
Description:
Pins:
PB0 PB1 PC4 PC5 //control direction
PA8 PA9 PA10 PA11 //control size by timer8 ch1-ch4


*/

#include "system.h"

void SteeringGearInit(void);
void setSteeringGearAngle(int angle);
#endif
