#include "sys.h"
#include "usart.h"	  
#include "timer.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/8/18
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 



/*****************  ����һ���ֽ� **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/****************** ����8λ������ ************************/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* ����һ���ֽ����ݵ�USART */
	    Usart_SendByte(pUSARTx,array[i]);	
  
  }
	/* �ȴ�������� */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  ����һ��16λ�� **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}



#endif 

 
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
  

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

void uart_init(u32 bound, usart_recv_callback cb){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
	//if(cb)
	{
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	}
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}

void SdkEvalComIOConfig(IO_RECEIVE_DATA_USER_CALLBACK_TYPE io_receive_function)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	IO_Receive_Data.IO_user_application = io_receive_function;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
	//if(cb)
	{
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	}
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = 9600;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
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
////			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);// ȫ���������
////		}
//    USART_ClearITPendingBit(USART1, USART_IT_TXE); 
//  }
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		/* Read one byte from the receive data register */
		ch = USART_ReceiveData(USART1);
		SEGGER_RTT_printf(0, "ch = %02x\n",ch);      //RTT��ӡ
		
		
		Uart1_Buffer[Uart1_Rx] = ch; 
		
		if(Uart1_Rx>13)//4+5+4
			Uart1_Rx=0;
		
//		SEGGER_RTT_printf(0, "Uart1_Buffer[Uart1_Rx] = %02x, Uart1_Rx=%d\n",
//																	Uart1_Buffer[Uart1_Rx],Uart1_Rx);      //RTT��ӡ
		if(('s'== Uart1_Buffer[0])
			&&('t'== Uart1_Buffer[1])
			&&('a'== Uart1_Buffer[2])
			&&('r'== Uart1_Buffer[3])
			&& (Uart1_Rx >4))
		{
			SEGGER_RTT_printf(0, "1-Uart1_Buffer[Uart1_Rx] = %02x, Uart1_Rx=%d\n",
															Uart1_Buffer[Uart1_Rx],Uart1_Rx);      //RTT��ӡ
			switch(Uart1_index_flag_end)
			{
				case 0:
					if(ch == 'e')//process
					{
//						SEGGER_RTT_printf(0, "2-Uart1_Buffer[Uart1_Rx] = %02x, Uart1_Rx=%d\n",
//						Uart1_Buffer[Uart1_Rx],Uart1_Rx);      //RTT��ӡ
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
												Uart1_Buffer[Uart1_Rx],Uart1_Rx);      //RTT��ӡ
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


