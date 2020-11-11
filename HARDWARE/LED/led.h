#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
	/// 不精确的延时
static void RS485_delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

//#define LED0 PAout(8)	// PA8

//#define LED1 PBout(5)	// PD2	green
//#define LED2_LOCK PBout(3)	// 	out   red
//#define LED2_CTL PBout(7)	// 	out 100ms   ?


#define LED1 PAout(15)	// PD2	green
#define LED2_LOCK PBout(5)	// 	out
//#define LED2_CTL PBout(7)	// 	out 100ms   ?


#define GO_1 PAout(0)	//
#define GO_2 PAout(1)	//
#define GO_3 PAout(2)	//
#define GO_4 PAout(3)	//
#define GO_5 PAout(4)	//
#define GO_6 PAout(5)	//
#define GO_7 PAout(6)	//
#define GO_8 PAout(7)	//
#define GO_9 PCout(4)	//
#define GO_10 PCout(5)	//
#define GO_11 PBout(0)	//
#define GO_12 PBout(1)	//
#define GO_13 PBout(10)	//
#define GO_14 PBout(11)	//
#define GO_15 PBout(12)	//
#define GO_16 PBout(13)	//
#define GO_17 PBout(14)	//
#define GO_18 PBout(15)	//
#define GO_19 PCout(6)	//
#define GO_20 PCout(7)	//
#define GO_21 PCout(8)	//
#define GO_22 PCout(9)	//
#define GO_23 PCout(11)	//
#define GO_24 PCout(10)	//


//#define GI_1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)//读取按键1

//#define GI_2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)//读取按键1

//#define GI_3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//

//#define GI_4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)//读取按键0

//#define GI_5  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//

//#define GI_6  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//

//#define GI_7  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)//

//#define GI_8  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//

//#define GI_9  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//

//#define GI_10  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//

//#define GI_11  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)//

//#define GI_12  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)//

//#define GI_13  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)//

//#define GI_14  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_13)//

//#define GI_15  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15)//

//#define GI_16  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)//

//#define GI_17  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)//

//#define GI_18  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//

//#define GI_19  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9)//

//#define GI_20  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11)//

//#define GI_21  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13)//

//#define GI_22  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15)//

//#define GI_23  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)//

//#define GI_24  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)//





//bo ma kai guan
#define DSW_1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)
#define DSW_2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)
#define DSW_3 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)
#define DSW_4 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)
#define DSW_5 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)
#define DSW_6 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)
//#define DSW_7 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)
//#define DSW_8 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)


/*控制收发引脚*/
//进入接收模式,必须要有延时等待485处理完数据
#define RS485_RX_EN()			RS485_delay(1000); GPIO_ResetBits(GPIOA,GPIO_Pin_11);  RS485_delay(1000);
//进入发送模式,必须要有延时等待485处理完数据
#define RS485_TX_EN()			RS485_delay(1000); GPIO_SetBits(GPIOA,GPIO_Pin_11);  RS485_delay(1000);

void LED_Init(void);//初始化



void TIM4_Int_Init(u16 arr,u16 psc);
void TIM4_Set(u8 sta);

void lock_all_off(void);

extern u8 key_mode;

		 				    
#endif
