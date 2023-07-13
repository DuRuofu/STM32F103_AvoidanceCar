#ifndef __ENCODER_H
#define __ENCODER_H

#include "main.h"
#include "tim.h"


void Encoder_Count_Init(void);
int16_t Encoder_Value(uint8_t n);
void Encoder_Count_Clear(uint8_t n);

#endif // !__ENCODER_H


