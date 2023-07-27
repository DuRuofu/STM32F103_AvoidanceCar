/*
 * @Author: DuRuofu duruofu@qq.com
 * @Date: 2023-07-13 17-13-53
 * @LastEditors: DuRuofu
 * @LastEditTime: 2023-07-26 21-26-30
 * @FilePath: \MDK-ARMd:\duruofu\Project\Avoidance_Car\project\STM32ZET6\Users\APP\app.c
 * @Description: 应用层模块
 * Copyright (c) 2023 by duruofu@foxmail.com All Rights Reserved.
 */

#include "app.h"
#define TAG "APP"
#define PWM_MAX 7200
//-------------------上位机调参用-------------------
// 调参用pid系数
int32_t Kp = 300;     // 比例系数
int32_t Ki = 10;      // 积分系数
int32_t Kd = 20;      // 微分系数
int32_t Cycle = 1000; // 采样周期
int32_t Target = 20;  // 目标值
//---------------速度环----------------
int32_t Target_Speed = 30; // 目标速度
int32_t Kp_Speed = 280;       // 速度环比例系数
int32_t Ki_Speed = 50;       // 速度环积分系数
int32_t Kd_Speed = 50;       // 速度环微分系数
int32_t L_Speed_Err = 0;    // 速度环上次误差
int32_t L_L_Speed_Err = 0;  // 速度环上上次误差
int32_t Car_Speed = 0;      // 电机实际速度（两电机加和）
int32_t PWM_Out_Speed = 0;  // 速度环输出

//---------------转向环----------------
int32_t Target_Direction = 0;  // 目标角度
int32_t Kp_Direction = 50;      // 角度环比例系数
int32_t Kd_Direction = 100;      // 角度环微分系数
int32_t Car_Direction = 0;     // 实际角度
int32_t L_Direction_Err = 0;   // 角度环上次误差
int32_t PWM_Out_Direction = 0; // 角度环输出

//----------------最终输出-------------------
int32_t PWM_Output_1 = 0;
int32_t PWM_Output_2 = 0;

uint8_t Grayscale_Value[5] = {0}; // 五路灰度模块的值

/**
 * @description: 系统应用初始化
 * @return {*}
 */
void App_Init(void)
{
    OLED_Init();          // 0.96oled初始化
    OLED_Clear();
    Motor_Init();         // 电机初始化
    USART_IT_Config();    // 总串口接收初始化
    Encoder_Count_Init(); // 编码器计数初始化
    protocol_init();      /* 协议初始化 */
    float pid_temp[3] = {(float)Kp, (float)Ki, (float)Kd};
    set_computer_value(SEND_P_I_D_CMD, CURVES_CH1, pid_temp, 3); // 给通道 1 发送 P I D
    set_computer_value(SEND_TARGET_CMD, CURVES_CH1, &Target, 1); // 给通道 1 发送目标值
    set_computer_value(SEND_PERIOD_CMD, CURVES_CH1, &Cycle, 1);  // 给通道 1 发送周期值


    //-----lcd测试-------
    // LCD_BLK = 1;
    // LCD_Clear(RED);
    // //LCD_Showimage(14, 0, 100, 50, gImage_11);
    // //LCD_DrawFont_GBK16(24, 60, BLUE, WHITE, "111");
    // //LCD_DrawFont_GBK16(28, 80, RED, WHITE, "22222");
    // LCD_DrawFont_GBK16(8, 100, BLACK, WHITE, "333333");
    //-----lcd测试-------

    // 开始数据采样
    HAL_TIM_Base_Start_IT(&htim2); // 启动定时器4
    //Motor_Ctrl(-400, 1); // 作用到电机
    //Motor_Ctrl(-1200, 2); // 作用到电机

}

/**
 * @description: 系统应用循环任务
 * @return {*}
 */
void App_Task(void)
{
    receiving_process();                                          // 协议接收处理(野火上位机)
    set_computer_value(SEND_FACT_CMD, CURVES_CH1, &Car_Speed, 1); // 给通道 1 发送实际值

    // 显示电机速度
    // OLED_ShowSignedNum(1, 1, Car_Speed, 5);
    // // 显示目标速度
    // OLED_ShowSignedNum(1, 7, Target, 5);
    // // 显示当前调差的PID参数
    // OLED_ShowSignedNum(4, 1, Kp, 3);
    // OLED_ShowSignedNum(4, 6, Ki, 3);
    // OLED_ShowSignedNum(4, 10, Kd, 3);

    // 读取灰度模块作为实际方向
    // = Grayscale_Read_Err();
    // 电机控制任务
    //Car_PID_Ctrl();
}

// 定时器中断回调函数(1ms一次)
uint8_t encoder_count = 0;
uint8_t LED_Heartbeat = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim2) // 判断中断是否来自于定时器1
    {
        // 编码器测速任务
        encoder_count++;
        if (encoder_count == 10)
        {
            // 计数值清零
            encoder_count = 0;
            // 读取编码器速度
            Motor_Speed_Read();
        }
        // 心跳(50ms一次)
        LED_Heartbeat++;
        if (LED_Heartbeat == 50)
        {
            LED_Toggle(1);
            
        }


    }
}

// 读取电机速度
void Motor_Speed_Read(void)
{
    // 读取编码器速度(加和)
    Car_Speed = Encoder_Value(1) + Encoder_Value(2);
    // 清零编码器计数值
    Encoder_Count_Clear(1);
    Encoder_Count_Clear(2);
}

//--------------------PID控制--------------------
/**
 * @description: 设置比例、积分、微分系数
 * @param {float} Kp 比例系数 P
 * @param {float} Ki 积分系数 i
 * @param {float} Kd 微分系数 d
 * @return {*} 无
 */
void Set_PID(int32_t kp, int32_t ki, int32_t kd)
{
    Kp = (int32_t)kp; // 设置比例系数 P
    Ki = (int32_t)ki; // 设置积分系数 I
    Kd = (int32_t)kd; // 设置微分系数 D
    DEBUG_info(TAG, "Set_PID: Kp=%u, Ki=%u, Kd=%u", Kp, Ki, Kd);
}

/**
 * @description: 设置当前的目标值
 * @param {float} temp_val
 * @return {*}
 */
void Set_PID_Target(float temp_val)
{
    DEBUG_info(TAG, "set_pid_target: %f", temp_val);
    Target = temp_val; // 设置当前的目标值
}

/**
 * @description: 速度环(待修改)
 * @param {int32_t} target_speed
 * @param {int32_t} fact_speed
 * @return {*}
 */
int32_t PID_Speed(int32_t target_speed, int32_t fact_speed)
{
    static int32_t Speed_PWM_Out = 0, Err_Speed = 0; // 速度环输出
    Err_Speed = target_speed - fact_speed;           // 计算速度误差
    // DEBUG_info(TAG, "PID_Speed: PWM_Out=%u", Speed_PWM_Out);
    // DEBUG_info(TAG, "PID_Speed: Err_Speed=%u", Err_Speed);
    // 死区限制
    if (Err_Speed > -1 && Err_Speed < 1)
    {
        Err_Speed = 0;
    }
    // PID计算(增量)
    //Speed_PWM_Out = Speed_PWM_Out+ Kp_Speed * (Err_Speed - L_Speed_Err) + Ki_Speed * Err_Speed + Kd_Speed * (Err_Speed - 2 * L_Speed_Err + L_L_Speed_Err);
    // 调参用
     Speed_PWM_Out = Speed_PWM_Out +  Kp * (Err_Speed-L_Speed_Err) + Ki * Err_Speed + Kd * (Err_Speed - 2.0*L_Speed_Err + L_L_Speed_Err);
    // 限幅
    if (Speed_PWM_Out > 7200)
    {
        Speed_PWM_Out = 7200;
    }
    else if (Speed_PWM_Out < -7200)
    {
        Speed_PWM_Out = -7200;
    }
    // 保存误差
    L_Speed_Err = Err_Speed;     // 保存上一次的误差
    L_L_Speed_Err = L_Speed_Err; // 保存上上次的误差
    // DEBUG_info(TAG, "PID_Speed: PWM_Out=%u", Speed_PWM_Out);
    return Speed_PWM_Out;
}

/**
 * @description: 转向环(待修改)
 * @param {int32_t} target_direction
 * @param {int32_t} fact_direction
 * @return {*}
 */
int32_t PID_Direction(int32_t target_direction, int32_t fact_direction)
{
    static int32_t Direction_PWM_Out = 0, Err_Direction = 0; // 转向环输出
    Err_Direction = target_direction - fact_direction;       // 计算转向误差
    // 死区限制
    if (Err_Direction > -1 && Err_Direction < 1)
    {
        Err_Direction = 0;
    }

    Direction_PWM_Out = Kp * Err_Direction + Kd * (Err_Direction - L_Direction_Err);
    // Direction_PWM_Out = Kp_Direction * Err_Direction + Kd_Direction * (Err_Direction - L_Direction_Err)

    if (Direction_PWM_Out > 7200)
    {
        Direction_PWM_Out = 7200;
    }
    else if (Direction_PWM_Out < -7200)
    {
        Direction_PWM_Out = -7200;
    }
    // 保存误差
    L_Direction_Err = Err_Direction;     // 保存上一次的误差
    DEBUG_info(TAG,"Direction_PWM_Out:%d",Direction_PWM_Out);
    return Direction_PWM_Out;
}

/**
 * @description: 小车PID总输出
 * @return {*}
 */
void Car_PID_Ctrl(void)
{
    // 速度环
    PWM_Out_Speed = PID_Speed(Target, Car_Speed);

    // 转向环
    PWM_Out_Direction = PID_Direction(0, Car_Direction);

    // 最终输出PWM
    PWM_Output_1 = PWM_Out_Speed;// + PWM_Out_Direction;
    PWM_Output_2 = PWM_Out_Speed; //- PWM_Out_Direction;

    // 限幅
    if (PWM_Output_1 >= PWM_MAX)
    {
        PWM_Output_1 = PWM_MAX;
    }
    else if (PWM_Output_1 <= -PWM_MAX)
    {
        PWM_Output_1 = -PWM_MAX;
    }
    else if (PWM_Output_2 >= PWM_MAX)
    {
        PWM_Output_2 = PWM_MAX;
    }
    else if (PWM_Output_2 <= -PWM_MAX)
    {
        PWM_Output_2 = -PWM_MAX;
    }
    //作用到电机
    Motor_Ctrl(PWM_Output_1, 1); // 作用到电机
    Motor_Ctrl(PWM_Output_2, 2); // 作用到电机
    DEBUG_info(TAG, "Car_PID_Ctrl: %d,%d", PWM_Output_1, PWM_Output_2);
}
