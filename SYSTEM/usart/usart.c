#include "sys.h"
#include "usart.h"	  
#include "timer.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/8/18
//版本：V1.5
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
//V1.5修改说明
//1,增加了对UCOSII的支持
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 



/*****************  发送一个字节 **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/****************** 发送8位的数组 ************************/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* 发送一个字节数据到USART */
	    Usart_SendByte(pUSARTx,array[i]);	
  
  }
	/* 等待发送完成 */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

/*****************  发送字符串 **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* 等待发送完成 */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  发送一个16位数 **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* 取出高八位 */
	temp_h = (ch&0XFF00)>>8;
	/* 取出低八位 */
	temp_l = ch&0XFF;
	
	/* 发送高八位 */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* 发送低八位 */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}



#endif 

 
 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  
  

/**
 * @brief  IO_Receive_Data User callback 
 */
typedef struct _IO_ReceiveCallBack
{
  /**
   * callback to notify the applicatio with the received I/O data
   */ 
  IO_RECEIVE_DATA_USER_CALLBACK_TYPE IO_user_application;
} IO_ReceiveCallBack;

/* IO User Callback used to handle received data from I/O channel*/
static IO_ReceiveCallBack IO_Receive_Data;

usart_recv_callback  usart1_recv_cb;



//void uart_init(u32 bound, usart_recv_callback cb){
//  //GPIO端口设置
//  GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
//  
//	//USART1_TX   GPIOA.9
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
//   
//  //USART1_RX	  GPIOA.10初始化
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

//  //Usart1 NVIC 配置
//	//if(cb)
//	{
//		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
//	}
//  
//   //USART 初始化设置

//	USART_InitStructure.USART_BaudRate = bound;//串口波特率
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
//	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

//  USART_Init(USART1, &USART_InitStructure); //初始化串口1
//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
//  USART_Cmd(USART1, ENABLE);                    //使能串口1 

//}

void SdkEvalComIOConfig(IO_RECEIVE_DATA_USER_CALLBACK_TYPE io_receive_function)
{
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	IO_Receive_Data.IO_user_application = io_receive_function;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
	//if(cb)
	{
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	}
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = 9600;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 
#ifdef __GNUC__
  setvbuf(stdout, NULL, _IONBF, 0);
#endif  
}

/**
 * @brief  Receive data on selected I/O port
 * @param  rx_data pointer to buffer of received
 * @param  data_size number of received data 
 * @retval None
 */
void SdkEvalComIOReceiveData(uint8_t * rx_data, uint16_t data_size)
{
  if(IO_Receive_Data.IO_user_application)
    IO_Receive_Data.IO_user_application(rx_data,data_size);
}



uint8_t Uart1_Buffer[256];        //?????
uint8_t Uart1_Rx = 0;             //Uart1_Buffer??

uint8_t Uart1_Sta;                //???????
uint8_t Uart1_index_flag,Uart1_index_flag_end;                //???????
uint8_t index_flag1;                //???????
uint8_t index_flag4;                //???????

unsigned char recstatu;//??????????????????

unsigned char packerflag;//???????????????

//unsigned char ccnt;      //??

//unsigned char rxbuf[100];//????????
void USART1_IRQHandler(void)
{
	u8 ch;
//	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
//  {   
////    USART_SendData(USART1, TxBuffer[TxCounter++]); 
////    if(TxCounter == count) 
////		{
////			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);// 全部发送完成
////		}
//    USART_ClearITPendingBit(USART1, USART_IT_TXE); 
//  }
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		/* Read one byte from the receive data register */
		ch = USART_ReceiveData(USART1);
		SEGGER_RTT_printf(0, "ch = %02x\n",ch);      //RTT打印
		
		
		Uart1_Buffer[Uart1_Rx] = ch; 
		
		if(Uart1_Rx>13)//4+5+4
			Uart1_Rx=0;
		
//		SEGGER_RTT_printf(0, "Uart1_Buffer[Uart1_Rx] = %02x, Uart1_Rx=%d\n",
//																	Uart1_Buffer[Uart1_Rx],Uart1_Rx);      //RTT打印
		if(('s'== Uart1_Buffer[0])
			&&('t'== Uart1_Buffer[1])
			&&('a'== Uart1_Buffer[2])
			&&('r'== Uart1_Buffer[3])
			&& (Uart1_Rx >4))
		{
			SEGGER_RTT_printf(0, "1-Uart1_Buffer[Uart1_Rx] = %02x, Uart1_Rx=%d\n",
															Uart1_Buffer[Uart1_Rx],Uart1_Rx);      //RTT打印
			switch(Uart1_index_flag_end)
			{
				case 0:
					if(ch == 'e')//process
					{
//						SEGGER_RTT_printf(0, "2-Uart1_Buffer[Uart1_Rx] = %02x, Uart1_Rx=%d\n",
//						Uart1_Buffer[Uart1_Rx],Uart1_Rx);      //RTT打印
						Uart1_index_flag_end =1;
					}
					break;
				case 1:
					if(ch == 'n')//process
						Uart1_index_flag_end =2;
					break;
				case 2:
					if(ch == 'd')//process
						Uart1_index_flag_end =3;
					break;
				case 3:
					if(ch == 'o')//process
					{
						TIM3_Set(0);
						SEGGER_RTT_printf(0, "3-Uart1_Buffer[Uart1_Rx] = %02x, Uart1_Rx=%d\n",
												Uart1_Buffer[Uart1_Rx],Uart1_Rx);      //RTT打印
						Uart1_index_flag_end =0;
						packerflag = 1;                      //

					}
					break;
				default:
					break;
						
				
			}
		
		
		}
		else//timer interrrupt, Uart1_Rx =0;
		{
			TIM3_Set(1);
		}
		Uart1_Rx++;
		
		//printf("ch=%x\r\n",ch);
		/* IO Receive Data: it handles the received data within the  User Application Function 
		defined as parameter of SdkEvalComIOConfig() */
		//SdkEvalComIOReceiveData(&ch,1);

	}

	//USART_ClearITPendingBit(USART1,USART_IT_ORE);

}


#endif	



//		switch(Uart1_index_flag)
//		{
//			case 0:
//				if(ch == 'e')//process
//				{
//					Uart1_index_flag =1;
//					index_flag1 =1;
//				}
//				break;
//			case 1:
//				if(ch == 'n')//process
//					Uart1_index_flag =2;
//				break;
//			case 2:
//				if(ch == 'd')//process
//					Uart1_index_flag =3;
//				break;
//			case 3:
//				if(ch == 'o')//process
//				{
//					Uart1_index_flag =4;
//					index_flag4 =1;
//				}
//				break;
//			default:
//				break;
//				
//		}
//		
//			
//		if(1== index_flag4)
//		{
//			if(1== index_flag1)
//			{
//				SEGGER_RTT_printf(0,"Uart1_index_flag=%d\r\n",Uart1_index_flag);
//				SEGGER_RTT_printf(0,"Uart1_Rx=%d\r\n",Uart1_Rx);
//				index_flag1 =0;
//				index_flag4 =0;
//				Uart1_index_flag =0;
//				Uart1_Rx =0;
//			}
//		}
//		else
//		{
//			if(0== index_flag1)
//			{
//					//Uart1_Buffer[Uart1_Rx] = ch; 
//					Uart1_Rx++; 
//					//Uart1_Rx &= 0xFF; 

//			}
//			else
//			{
//					//SEGGER_RTT_printf(0,"Uart1_Rx=%d\r\n",Uart1_Rx);
//			}
//		}


