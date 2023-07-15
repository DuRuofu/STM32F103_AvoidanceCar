#ifndef __APP_H
#define __APP_H

#include "main.h"
#include "tim.h"
#include "led.h"
#include "oled.h"
#include "motor.h"
#include "encoder.h"
#include "serial_it_config.h"
#include "Grayscale.h"
#include "protocol.h"



void App_Init(void);
void App_Task(void);
void MPU6050_Data_Read(void);
void Motor_Speed_Read(void);
void Car_PID_Ctrl(void);
void Set_PID_Target(float temp_val);
void Set_PID(float kp, float ki, float kd);

#endif // !__APP_H
