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
#include "gui.h"
#include "ccd.h"
#include "control.h"
#include "yuntai.h"
void App_Init(void);
void App_Task(void);
void MPU6050_Data_Read(void);
void Motor_Speed_Read(void);
int32_t PID_Speed(int32_t target_speed, int32_t fact_speed);
int32_t PID_Direction(int32_t target_direction, int32_t fact_direction);

#endif // !__APP_H
