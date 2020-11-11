#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK miniSTM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PCin(5)   	
//#define KEY1 PAin(15)	 
//#define WK_UP  PAin(0)	 
 


#define KEY2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)//读取按键1
#define KEY4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)//读取按键0
//#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键2 

#define KEY2_PRES	2		//KEY0  
#define KEY4_PRES	4		//KEY1 
//#define WKUP_PRES	3		//WK_UP  

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数		
u8 KEY_close_Scan(void);
u8 KEY_open_Scan(void);
extern u8 key_Level;





/* Macro definitions ---------------------------------------------------------*/
#define KEYn                            (3)

#define KEY0_RCC_AHB1Periph_GPIO        RCC_APB2Periph_GPIOE
#define KEY0_GPIO                       GPIOE
#define KEY0_GPIO_Pin                   GPIO_Pin_4
#define KEY0_GPIO_PuPd                  GPIO_PuPd_UP
#define KEY0_PRESS_STATUS               Bit_RESET

#define KEY1_RCC_AHB1Periph_GPIO        RCC_APB2Periph_GPIOE
#define KEY1_GPIO                       GPIOE
#define KEY1_GPIO_Pin                   GPIO_Pin_3
#define KEY1_GPIO_PuPd                  GPIO_PuPd_UP
#define KEY1_PRESS_STATUS               Bit_RESET

#define KEY2_RCC_AHB1Periph_GPIO        RCC_APB2Periph_GPIOE
#define KEY2_GPIO                       GPIOB
#define KEY2_GPIO_Pin                   GPIO_Pin_6// on using
#define KEY2_GPIO_PuPd                  GPIO_PuPd_UP
#define KEY2_PRESS_STATUS               Bit_RESET

#define KEY_RCC_APB1Periph_TIM          RCC_APB1Periph_TIM2
#define KEY_TIM                         TIM2
#define KEY_TIM_Prescaler               (83)   /*!< Clock divided to 1MHz. */
#define KEY_TIM_Period                  (4999) /*!< 5ms timer interrupt. */
#define KEY_TIM_IRQn                    TIM2_IRQn
#define KEY_TIM_IRQHandler              TIM2_IRQHandler
#define KEY_TIM_IRQ_PreemptionPriority  (0)
#define KEY_TIM_IRQ_SubPriority         (0)

/* Type definitions ----------------------------------------------------------*/
typedef enum
{
  KEY_Pin0 = 0,
  KEY_Pin1 = 1,
  KEY_Pin2 = 2
}KEY_Pin;

typedef enum
{
  KEY_NoPress    = 0,
  KEY_ShortPress = 1,
  KEY_LongPress  = 2
}KEY_Status;

/* Variable declarations -----------------------------------------------------*/
/* Variable definitions ------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/
void KEY_Init1(KEY_Pin pin);
void KEY_DeInit(KEY_Pin pin);
KEY_Status KEY_GetStatus(KEY_Pin pin);
void KEY_SetPressCallback(KEY_Pin pin, void (*fun)(KEY_Status));





#endif
