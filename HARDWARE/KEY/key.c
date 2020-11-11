#include "key.h"
#include "delay.h"
#include "SEGGER_RTT.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//按键输入 驱动代码		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/3/06
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									   
//////////////////////////////////////////////////////////////////////////////////	 
 	    
//按键初始化函数 
//PA0.15和PC5 设置成输入
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA,PORTC时钟
	
	//a13 a14 a15    b3 b4
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
	
	
	
	
//	//group1
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
// 	GPIO_Init(GPIOC, &GPIO_InitStructure);//

	//group2  b6
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//
	
	
	
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//PA2
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOC5

	
} 


//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//返回值：
//0，没有任何按键按下
//KEY0_PRES，KEY0按下
//KEY1_PRES，KEY1按下
//WKUP_PRES，WK_UP按下 
//注意此函数有响应优先级,KEY0>KEY1>WK_UP!!
//close
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY2==0||KEY4==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY2==0)
			return KEY2_PRES;
		else if(KEY4==0)
			return KEY4_PRES;
	}
	else if(KEY2==1&&KEY4==1)
		key_up=1; 	     
	return 0;// 无按键按下
}




u8 key_Level=0;

//close
u8 KEY_close_Scan()
{	   
	if((key_Level==0)&&(KEY2==0||KEY4==0))
	{
		delay_ms(10);//去抖动 
		//key_Level=0;
		if(KEY2==0)
		{
			//key_Level =1;
			return KEY2_PRES;
		}
		else if(KEY4==0)
		{
			//key_Level =1;
			return KEY4_PRES;
		}
	}    
	return 0;// 无按键按下
}


//open
u8 KEY_open_Scan(void)
{	   
	if(key_Level&&(KEY2==1||KEY4==1))
	{
		delay_ms(10);//去抖动 
		//key_Level=0;
		if(KEY2==1)
		{
			//key_Level =0;
			return KEY2_PRES;
		}
		else if(KEY4==1)
		{
			//key_Level =0;
			return KEY4_PRES;
		}
	}    
	return 0;// 无按键按下
}



/**
  ******************************************************************************
  * @file    KEY.c
  * @author  XinLi
  * @version v1.0
  * @date    24-October-2017
  * @brief   KEY module driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>Copyright &copy; 2017 XinLi</center></h2>
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <https://www.gnu.org/licenses/>.
  *
  ******************************************************************************
  */

/* Header includes -----------------------------------------------------------*/
//#include "KEY.h"
#include <string.h>
#include <stdbool.h>

/* Macro definitions ---------------------------------------------------------*/
/* Type definitions ----------------------------------------------------------*/
/* Variable declarations -----------------------------------------------------*/
/* Variable definitions ------------------------------------------------------*/
static      GPIO_TypeDef    *KEY_GPIO[KEYn]                      = {KEY0_GPIO, KEY1_GPIO, KEY2_GPIO};
static      uint16_t         KEY_GPIO_Pin[KEYn]                  = {KEY0_GPIO_Pin, KEY1_GPIO_Pin, KEY2_GPIO_Pin};
//static      GPIOPuPd_TypeDef KEY_GPIO_PuPd[KEYn]                 = {KEY0_GPIO_PuPd, KEY1_GPIO_PuPd, KEY2_GPIO_PuPd};
static      BitAction        KEY_PRESS_STATUS[KEYn]              = {KEY0_PRESS_STATUS, KEY1_PRESS_STATUS, KEY2_PRESS_STATUS};
static      uint32_t         KEY_RCC_AHB1Periph_GPIO[KEYn]       = {KEY0_RCC_AHB1Periph_GPIO, KEY1_RCC_AHB1Periph_GPIO, KEY2_RCC_AHB1Periph_GPIO};
static __IO bool             keyInitFlag[KEYn]                   = {false};
static __IO uint32_t         keyInputHighCount[KEYn]             = {0};
static __IO uint32_t         keyInputLowCount[KEYn]              = {0};
static __IO KEY_Status       keyStatus[KEYn]                     = {KEY_NoPress};
static __IO KEY_Status       keyGetStatus[KEYn]                  = {KEY_NoPress};
static __IO void           (*keyPressCallback[KEYn])(KEY_Status) = {NULL};
static __IO bool             timInitFlag                         = false;

/* Function declarations -----------------------------------------------------*/
/* Function definitions ------------------------------------------------------*/

/**
  * @brief  Key initialize.
  * @param  [in] pin: That key.
  * @return None.
  */
void KEY_Init1(KEY_Pin pin)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};
	    
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};
	NVIC_InitTypeDef NVIC_InitStructure = {0};
  if(keyInitFlag[pin] == false)
  {
    keyInitFlag[pin]       = true;
    keyInputHighCount[pin] = 0;
    keyInputLowCount[pin]  = 0;
    keyStatus[pin]         = KEY_NoPress;
    keyGetStatus[pin]      = KEY_NoPress;
    keyPressCallback[pin]  = NULL;
    
    
    RCC_APB2PeriphClockCmd(KEY_RCC_AHB1Periph_GPIO[pin], ENABLE);
    
    GPIO_InitStructure.GPIO_Pin  = KEY_GPIO_Pin[pin];
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    //GPIO_InitStructure.GPIO_PuPd = KEY_GPIO_PuPd[pin];
    GPIO_Init(KEY_GPIO[pin], &GPIO_InitStructure);
  }
  
  if(timInitFlag == false)
  {
    timInitFlag = true;
    
    RCC_APB1PeriphClockCmd(KEY_RCC_APB1Periph_TIM, ENABLE);
    
    TIM_TimeBaseInitStructure.TIM_Prescaler     = KEY_TIM_Prescaler;
    TIM_TimeBaseInitStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period        = KEY_TIM_Period;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(KEY_TIM, &TIM_TimeBaseInitStructure);
    
    TIM_ClearFlag(KEY_TIM, TIM_FLAG_Update);
    TIM_ITConfig(KEY_TIM, TIM_IT_Update, ENABLE);
    TIM_Cmd(KEY_TIM, ENABLE);
    

    
    NVIC_InitStructure.NVIC_IRQChannel                   = KEY_TIM_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = KEY_TIM_IRQ_PreemptionPriority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = KEY_TIM_IRQ_SubPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
  }
}

/**
  * @brief  Key de-initialize.
  * @param  [in] pin: That key.
  * @return None.
  */
void KEY_DeInit(KEY_Pin pin)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};
	NVIC_InitTypeDef NVIC_InitStructure = {0};
	uint32_t i;
  if(keyInitFlag[pin] == true)
  {
    keyInitFlag[pin]       = false;
    keyInputHighCount[pin] = 0;
    keyInputLowCount[pin]  = 0;
    keyStatus[pin]         = KEY_NoPress;
    keyGetStatus[pin]      = KEY_NoPress;
    keyPressCallback[pin]  = NULL;
    

    
    GPIO_InitStructure.GPIO_Pin  = KEY_GPIO_Pin[pin];
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(KEY_GPIO[pin], &GPIO_InitStructure);
  }
  
  if(timInitFlag == true)
  {
    bool timDeInitFlag = true;
    
    for(i = 0; i < KEYn; i++)
    {
      if(keyInitFlag[i] == true)
      {
        timDeInitFlag = false;
      }
    }
    
    if(timDeInitFlag == true)
    {
      timInitFlag = false;
      
      TIM_DeInit(KEY_TIM);
      RCC_APB1PeriphClockCmd(KEY_RCC_APB1Periph_TIM, DISABLE);
      

      
      NVIC_InitStructure.NVIC_IRQChannel                   = KEY_TIM_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = KEY_TIM_IRQ_PreemptionPriority;
      NVIC_InitStructure.NVIC_IRQChannelSubPriority        = KEY_TIM_IRQ_SubPriority;
      NVIC_InitStructure.NVIC_IRQChannelCmd                = DISABLE;
      NVIC_Init(&NVIC_InitStructure);
    }
  }
}

/**
  * @brief  Get key status.
  * @param  [in] pin: That key.
  * @return Key status.
  */
KEY_Status KEY_GetStatus(KEY_Pin pin)
{
  KEY_Status status = KEY_NoPress;
  
  if(keyGetStatus[pin] != KEY_NoPress)
  {
    status            = keyGetStatus[pin];
    keyGetStatus[pin] = KEY_NoPress;
  }
  
  return status;
}

/**
  * @brief  Set key press callback.
  * @param  [in] pin: That key.
  * @param  [in] fun: Function pointer.
  * @return None.
  */
void KEY_SetPressCallback(KEY_Pin pin, void (*fun)(KEY_Status))
{
  keyPressCallback[pin] = (__IO void (*)(KEY_Status))fun;
}

/**
  * @brief  This function handles TIM handler.
  * @param  None.
  * @return None.
  */
void KEY_TIM_IRQHandler(void)
{
	uint32_t i;
	//SEGGER_RTT_printf(0, "KEY_TIM_IRQHandler\n"); 
  if(TIM_GetITStatus(KEY_TIM, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(KEY_TIM, TIM_IT_Update);
    
    for(i = 0; i < KEYn; i++)
    {
      if(GPIO_ReadInputDataBit(KEY_GPIO[i], KEY_GPIO_Pin[i]) == KEY_PRESS_STATUS[i])
      {
        keyInputLowCount[i]++;
        
        if(keyInputLowCount[i] > 1)
        {
          keyInputHighCount[i] = 0;
        }
        
        if(keyInputLowCount[i] > 200)//100
        {
          keyInputLowCount[i] = 0;
          keyStatus[i]        = KEY_LongPress;
          keyGetStatus[i]     = KEY_LongPress;
          
          if(keyPressCallback[i] != NULL)
          {
            keyPressCallback[i](KEY_LongPress);
          }
        }
      }
      else
      {
        keyInputHighCount[i]++;
        
        if(keyInputHighCount[i] > 1)
        {
          if((keyStatus[i] == KEY_NoPress) && (keyInputLowCount[i] > 1))
          {
            keyInputHighCount[i] = 0;
            keyInputLowCount[i]  = 0;
            keyStatus[i]         = KEY_ShortPress;
            keyGetStatus[i]      = KEY_ShortPress;
            
            if(keyPressCallback[i] != NULL)
            {
              keyPressCallback[i](KEY_ShortPress);
            }
          }
          else
          {
            keyInputHighCount[i] = 0;
            keyInputLowCount[i]  = 0;
            keyStatus[i]         = KEY_NoPress;
          }
        }
      }
    }
  }
}



