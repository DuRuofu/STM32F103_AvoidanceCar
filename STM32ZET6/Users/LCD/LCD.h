#ifndef __LCD_H
#define __LCD_H

#include "main.h"



//---------------------------------------------------------
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入
//---------------------------------------------------------




#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        128

//颜色代码定义
#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//灰色0 3165 00110 001011 00101
#define GRAY1   0x8410      	//灰色1      00000 000000 00000
#define GRAY2   0x4208      	//灰色2  1111111111011111


#define LCD_SCL  PBout(15)
#define LCD_SDA  PBout(13)
#define LCD_CS   PBout(12)
#define LCD_RES  PBout(14)
#define LCD_DC   PCout(5)
#define LCD_BLK  PBout(1)

/* 定义SPI连接的GPIO端口, 用户只需要修改下面代码即可任意改变相应的引脚*/
#define LCD_SCL_GPIO_PORT	 GPIOB			            /* GPIO端口 */
#define LCD_SCL_RCC 	     RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LCD_SCL_PIN		     GPIO_Pin_8			        /* 连接到SCL时钟线的GPIO */

#define LCD_SDA_GPIO_PORT	 GPIOB			            /* GPIO端口 */
#define LCD_SDA_RCC 	     RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LCD_SDA_PIN		     GPIO_Pin_9			        /* 连接到SDA数据线的GPIO */

#define LCD_RES_GPIO_PORT	 GPIOB			            /* GPIO端口 */
#define LCD_RES_RCC 	     RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LCD_RES_PIN		     GPIO_Pin_6			        /* 连接到RES时钟线的GPIO */

#define LCD_DC_GPIO_PORT	 GPIOB			            /* GPIO端口 */
#define LCD_DC_RCC 	       RCC_APB2Periph_GPIOB		    /* GPIO端口时钟 */
#define LCD_DC_PIN		     GPIO_Pin_5			        /* 连接到DC数据线的GPIO */

#define LCD_CS_GPIO_PORT	 GPIOB			            /* GPIO端口 */
#define LCD_CS_RCC	       RCC_APB2Periph_GPIOB		    /* GPIO端口时钟 */
#define LCD_CS_PIN		     GPIO_Pin_7			        /* 连接到CS数据线的GPIO */

#define LCD_BLK_GPIO_PORT	 GPIOB			            /* GPIO端口 */
#define LCD_BLK_RCC	       RCC_APB2Periph_GPIOB		    /* GPIO端口时钟 */
#define LCD_BLK_PIN		     GPIO_Pin_4			        /* 连接到BLK数据线的GPIO */


void LCD_GPIO_Init(void);
void LCD_WriteIndex(u8 Index);
void LCD_WriteData(u8 Data);
void LCD_WriteData_16Bit(u16 Data);
void LCD_WriteReg(u8 Index,u8 Data);
void LCD_Reset(void);
void LCD_Init(void);
void LCD_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end);
void LCD_SetXY(u16 x,u16 y);
void LCD_DrawPoint(u16 x,u16 y,u16 Data);
unsigned int LCD_ReadPoint(u16 x,u16 y);
void LCD_Clear(u16 Color);


u16 LCD_BGR2RGB(u16 c);
void LCD_Circle(u16 X,u16 Y,u16 R,u16 fc);
void LCD_DrawLine(u16 x0, u16 y0,u16 x1, u16 y1,u16 Color);
void LCD_box(u16 x, u16 y, u16 w, u16 h,u16 bc);
void LCD_box2(u16 x,u16 y,u16 w,u16 h, u8 mode);
void DisplayButtonDown(u16 x1,u16 y1,u16 x2,u16 y2);
void DisplayButtonUp(u16 x1,u16 y1,u16 x2,u16 y2);
void LCD_DrawFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void LCD_DrawFont_GBK24(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void LCD_DrawFont_Num32(u16 x, u16 y, u16 fc, u16 bc, u16 num);
void LCD_Showimage(u16 x0, u16 y0,u16 x1, u16 y1,const unsigned char *p);

#endif
