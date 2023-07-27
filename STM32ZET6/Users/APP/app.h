#ifndef __APP_H
#define __APP_H

#include <stdlib.h>
#include <string.h>
#include "stdio.h"
#include "main.h"
#include "tim.h"
#include "led.h"
#include "OLED.h"
#include "motor.h"
#include "encoder.h"
#include "serial_it_config.h"
#include "Grayscale.h"
#include "protocol.h"
#include "cJSON.h"



void App_Init(void);
void App_Task(void);
void MPU6050_Data_Read(void);
void Motor_Speed_Read(void);
void Car_PID_Ctrl(void);
void Set_PID_Target(float temp_val);
void Set_PID(int32_t kp, int32_t ki, int32_t kd);
int32_t PID_Speed(int32_t target_speed, int32_t fact_speed);
int32_t PID_Direction(int32_t target_direction, int32_t fact_direction);;
#endif // !__APP_H
