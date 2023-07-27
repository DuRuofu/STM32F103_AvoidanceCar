/*
 * @Author: DuRuofu duruofu@qq.com
 * @Date: 2023-07-27 09-48-56
 * @LastEditors: DuRuofu
 * @LastEditTime: 2023-07-27 10-18-23
 * @FilePath: \MDK-ARMd:\duruofu\Project\Avoidance_Car\project\STM32ZET6\Users\OLED\OLEDGUI\gui.c
 * @Description: 0.96OLED配合的GUI简单GUI界面
 * Copyright (c) 2023 by duruofu@foxmail.com All Rights Reserved. 
 */

#include "gui.h"
#include <stdio.h>

extern  uint8_t GUI_Menu ;


uint8_t str_buff1[64];
uint8_t str_buff2[64];
uint8_t str_buff3[64];
uint8_t str_buff4[64];   
uint8_t str_buff5[64];
uint8_t str_buff6[64];

void Menu_Refresh(void)
{
   //OLED_Clear(); 
   switch(GUI_Menu)
   {
        case 0:
        {
            OLED_ShowString(40,0,"GUI",16);
            sprintf((char *)str_buff1, "GUI_Menu:%5d",GUI_Menu); 
            break;
        }
        case 1:
        {
            OLED_ShowString(40,0,"Mot",16);
            sprintf((char *)str_buff1, "GUI_Menu:%5d",GUI_Menu); 
            break;
        }
        case 2:
        {
            OLED_ShowString(40,0,"PID",16);
            sprintf((char *)str_buff1, "GUI_Menu:%5d",GUI_Menu); 
            break;
        }
    }
    OLED_ShowString(0, 2,str_buff1, 8);
    OLED_ShowString(0, 3,str_buff2, 8);
    OLED_ShowString(0, 4,str_buff3, 8);
    OLED_ShowString(0, 5,str_buff4, 8);
    OLED_ShowString(0, 6,str_buff5, 8);
    OLED_ShowString(0, 7,str_buff6, 8);
}
