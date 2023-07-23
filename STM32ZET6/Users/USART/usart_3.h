#include <stdio.h>
#include "main.h"
#include "usart.h"
#include "cJSON.h"
#include <stdlib.h>
#include <string.h>

#ifndef __USART_3_H
#define __USART_3_H


//串口1接收中断初始化
void  UART3_Init(void);
//串口1接收完成回调函数
void UART3_RxCpltCallback(UART_HandleTypeDef *huart);
void UART3_ErrorCallback(UART_HandleTypeDef *huart);
//void Usart3_SendString(uint8_t *str);
#endif // !__USART_3_H




