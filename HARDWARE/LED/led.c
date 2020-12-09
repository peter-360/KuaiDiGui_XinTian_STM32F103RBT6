#include "led.h"
#include "SEGGER_RTT.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK mini?SSTM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC\
												|RCC_APB2Periph_GPIOD, ENABLE);	 //使能PA,PD端口时钟
	

// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PA.8 端口配置
// GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
// GPIO_SetBits(GPIOA,GPIO_Pin_8);						 //PA.8 输出高

// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 端口配置, 推挽输出
// GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
// GPIO_SetBits(GPIOD,GPIO_Pin_2); 						 //PD.2 输出高 
	
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->Pc2 端口配置, 推挽输出
// GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
// GPIO_SetBits(GPIOC,GPIO_Pin_2); 						 //输出高 
	
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	//a13 a14 a15    b3 b4
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
	//LED
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	    		 //LED1-->PB5 端口配置, 推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GPIO_ResetBits(GPIOA,GPIO_Pin_15); 						 //输出高 

	//rs485 RE
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	    		 //LED1-->Pc2 端口配置, 推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	RS485_RX_EN();
	
	//LED2_LOCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PB5 端口配置, 推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GPIO_ResetBits(GPIOB,GPIO_Pin_5); 						 //输出高 


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	    		 //LED1-->PB5 端口配置, 推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GPIO_SetBits(GPIOA,GPIO_Pin_12); 						 //输出高 


//	//i group1
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
// 	GPIO_Init(GPIOC, &GPIO_InitStructure);//
//	//i group2
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
// 	GPIO_Init(GPIOC, &GPIO_InitStructure);//

// ...
	
	
	//o group1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_1=0; 						 //输出高 
	
	//o group2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_2=0;	 						 //输出高 

	//o group3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_3=0;	 						 //输出高 
	//o group4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_4=0;	 						 //输出高 
	//o group5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_5=0;	 						 //输出高 
	//o group6
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_6=0;	 						 //输出高 
	//o group7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_7=0;	 						 //输出高 	
	//o group8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_8=0;	 						 //输出高 	
	//o group9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_9=0;	 						 //输出高 
	//o group10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_10=0;	 						 //输出高 
	//o group11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_11=0;	 						 //输出高 
	//o group12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_12=0;	 						 //输出高 
	//o group13
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_13=0;	 						 //输出高 
	//o group14
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_14=0;	 						 //输出高 
	//o group15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_15=0;	 						 //输出高 
	//o group16
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_16=0;	 						 //输出高 
	//o group17
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_17=0;	 						 //输出高 

	//o group18
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_18=0;	 						 //输出高 

	//o group19
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_19=0;	 						 //输出高 

	//o group20
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_20=0;	 						 //输出高 

	//o group21
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_21=0;	 						 //输出高 

	//o group22
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_22=0;	 						 //输出高 

	//o group23
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_23=0;	 						 //输出高 

	//o group24
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_24=0;	 						 //输出高 




//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试-----
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//Pc3
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
//	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化
	
}











//设置TIM4的开关
//sta:0，关闭;1,开启;
void TIM4_Set(u8 sta)
{
	if(sta)
	{
       
		TIM_SetCounter(TIM4,0);//计数器清空
		TIM_Cmd(TIM4, ENABLE);  //使能TIMx	
	}
	else 
		TIM_Cmd(TIM4, DISABLE);//关闭定时器4	   
}


//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM4_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能
	
	//定时器TIM4初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM4, ENABLE);  //使能TIMx				
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );	
}

#include <stdbool.h>
bool zijian_ongo_flag=0;
u8 lock_channel=0;
//u8 lock_channel_mode2=0;
//定时器3中断服务程序
void TIM4_IRQHandler(void)   //TIM4中断
{
	uint8_t gpio_level;
	uint8_t tx_Buffer[64]={0};        //?????
	uint8_t bcc_temp;
	uint8_t board_addr;
	SEGGER_RTT_printf(0, "TIM4_IRQHandler\n"); 
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //检查TIM4更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx更新中断标志 
		//LED1=!LED1;
		//Uart1_Rx =0 ;
		
		if(zijian_ongo_flag==0) 
		{
			zijian_ongo_flag =1;			
		}
		else if(zijian_ongo_flag==1) 
		{
			zijian_ongo_flag =0;			
		}
		SEGGER_RTT_printf(0, "zijian_ongo_flag= %d\n",zijian_ongo_flag);

		if(2== key_mode)
		{
			SEGGER_RTT_printf(0, "mode2-lock_channel= %d\n",lock_channel);
			if(lock_channel <=24)//<=25
			{
				SEGGER_RTT_printf(0, "------lock_channel<=24------\n");
				switch(lock_channel)
				{
					SEGGER_RTT_printf(0, "lock_channel=%d\n",lock_channel);
					case 1://power on
						if(0==zijian_ongo_flag)
						{
							TIM4_Int_Init(7999,7199);//	
							TIM4_Set(1);	
							SEGGER_RTT_printf(0, "----------1-1----------\n");
							LED2_CTL = 0;
							GO_1=1; 					//open		
		
						}
						else
						{
							TIM4_Int_Init(1999,7199);//
							TIM4_Set(1);
							SEGGER_RTT_printf(0, "----------1-2----------\n");
							LED2_CTL = 1;  
							GO_1=0;						//close

						}

						break;

					case 2://
						if(0==zijian_ongo_flag)
						{
							SEGGER_RTT_printf(0, "----------2-1----------\n");
							LED2_CTL = 0;
							GO_2=1;							 //open
							TIM4_Int_Init(7999,7199);//
							TIM4_Set(1);
						}
						else
						{
							SEGGER_RTT_printf(0, "----------2-2----------\n");
							LED2_CTL = 1; 
							GO_2=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
							TIM4_Set(1);
						}
					
						break;
			
		
					case 3:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_3=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{
							LED2_CTL = 1; 
							GO_3=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}

						break;
					case 4:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_4=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{
							LED2_CTL = 1; 
							GO_4=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}


						break;
					case 5:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_5=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{
							LED2_CTL = 1; 
							GO_5=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}

						break;
					case 6:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_6=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{
							LED2_CTL = 1; 
							GO_6=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}

						break;
					case 7:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_7=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{ 
							LED2_CTL = 1;
							GO_7=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}


						break;
					case 8:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_8=1;						 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{ 
							LED2_CTL = 1;
							GO_8=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}

						break;
					case 9:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_9=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{ 
							LED2_CTL = 1;
							GO_9=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}

						break;
					case 10:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_10=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{ 
							LED2_CTL = 1;
							GO_10=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}


						break;
					case 11:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_11=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{ 
							LED2_CTL = 1; 
							GO_11=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}

						break;
					case 12:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_12=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{ 
							LED2_CTL = 1;  
							GO_12=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}
					
						break;
					case 13:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_13=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{ 
							LED2_CTL = 1; 
							GO_13=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}

						break;
					case 14:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_14=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{ 
							LED2_CTL = 1;
							GO_14=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}

						break;
					case 15:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_15=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{ 
							LED2_CTL = 1;
							GO_15=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}

						break;
					case 16:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_16=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{ 
							LED2_CTL = 1;
							GO_16=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}

						break;
					case 17:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_17=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{ 
							LED2_CTL = 1;
							GO_17=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}

						break;
					case 18:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_18=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{ 
							LED2_CTL = 1;
							GO_18=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}

						break;
					case 19:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_19=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{ 
							LED2_CTL = 1;
							GO_19=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}
					
						break;
					case 20:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_20=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{ 
							LED2_CTL = 1; 
							GO_20=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}

						break;
					case 21:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_21=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{ 
							LED2_CTL = 1;
							GO_21=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}

						break;
					case 22:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_22=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{ 
							LED2_CTL = 1;
							GO_22=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}

						break;
					case 23:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_23=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{ 
							LED2_CTL = 1; 
							GO_23=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}

						break;
					case 24:
						if(0==zijian_ongo_flag)
						{
							LED2_CTL = 0;
							GO_24=1;							 //open
							TIM4_Int_Init(7999,7199);//
						}
						else
						{ 
							LED2_CTL = 1;
							GO_24=0;	 						 //close
							TIM4_Int_Init(1999,7199);//
						}

						break;
					
					
					default:
						break;
				}
				//LED2_CTL = 0;
				// lock_all_off();
				TIM4_Set(1);			//TIM 
			}
			else
			{
				SEGGER_RTT_printf(0, "------lock_channel>24------\n");
				TIM4_Set(0);			//TIM 
				key_mode = 1;
				mode_nomal =0;

				lock_channel=0;
				zijian_ongo_flag =1;//add

				lock_all_off();

				board_addr= DSW_1 | (DSW_2<<1) | (DSW_3<<2) | (DSW_4<<3) | (DSW_5<<4) | (DSW_6<<5) ;
				SEGGER_RTT_printf(0, "-board_addr = %02x\n",board_addr);
				memcpy(tx_Buffer,"star",4);
				tx_Buffer[4]= 0x80;//m_data.opcode;
				tx_Buffer[5]= board_addr;
				tx_Buffer[6]= 0;
				tx_Buffer[7]= 0;
				tx_Buffer[8]= 0;


				
				bcc_temp = ComputXor(tx_Buffer+4,5);
				tx_Buffer[9]= bcc_temp;
				memcpy(tx_Buffer+10,"end",3);//now is 2?
				
				tx_Buffer[12]='\0';//tx_Buffer[12]='\0';
				
				spear_uart_send_datas(tx_Buffer,12);
			}

			if(zijian_ongo_flag==1)
			{
				lock_channel++;				
			}

		}
		
		

		
		if(1== key_mode)
		{
			lock_channel =0;
//			lock_channel_mode2 =0;
			TIM4_Set(0);
		}
		
	}
}





