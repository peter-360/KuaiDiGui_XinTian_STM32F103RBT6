#include "led.h"
#include "exti.h" 
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include <stdarg.h>
#include <string.h>
#include "timer.h"

//ALIENTEK Mini STM32开发板范例代码3
//串口实验   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

#define CMD_BUFFER_LEN 100
void usart1Printf(char *fmt, ...)
{
    char buffer[CMD_BUFFER_LEN - 1];
    u8 i = 0;
    u8 len;

    va_list arg_ptr; //Define convert parameters variable
    va_start(arg_ptr, fmt); //Init variable
    len = vsnprintf(buffer, CMD_BUFFER_LEN+1, fmt, arg_ptr); //parameters list format to buffer
    
    while ((i < CMD_BUFFER_LEN) && (i < len) && (len > 0))
    {
        USART_SendData(USART1, (u8) buffer[i++]);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }
    va_end(arg_ptr);
}



void spear_rtt_send_datas(uint8_t* str, uint8_t len)
{
	SEGGER_RTT_printf(0, "rtt-temp====="); 
	//SEGGER_RTT_printf(0, "spear_rtt_send_datas="); 
	while(len--)
	{
		SEGGER_RTT_printf(0, "%02x ",*str); 
		str++;
	}
	SEGGER_RTT_printf(0, "\n"); 
	
}

//0
void spear_uart_send_data(uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(USART1,ch);
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	
}
//1
void spear_uart_send_datas(uint8_t* str, uint8_t len)
{
	while(len--)
	{
		//delay_ms(50);  
		//while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
		USART_SendData(USART1, *str);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); 
		str++;
	}
}

//2
void UartSendString(char* Str)
{
	while(*Str)
	{
		//while(!UART_GetFlagStatus(UART_FLAG_TXFE));
		USART_SendData(USART1, *Str);
		while(!USART_GetFlagStatus(USART1,USART_FLAG_TC));
		Str++;
		//while(SdkEvalComUARTBusy() == SET);//203400
	}
}





void Process_InputData(uint8_t* data_buffer, uint16_t Nb_bytes)
{

//	printf("*********Process_InputData*************\r\n");
//	usart1Printf("data_buffer=%x %d",data_buffer[0],Nb_bytes);
	//USART1_Puts("----\r\n");
	//SEGGER_RTT_printf(0,"----\r\n");
	//spear_uart_send_datas((uint8_t*)"123\r\n",5);
//	usart1Printf("-------\r\n");
	//USART1_Puts("-----\r\n");


	USART_SendData(USART1, *data_buffer);
	

	
	//if(spear_uart_process_data(*data_buffer))//packege start
	{
		////send event to 
		//spear_sched_set_evt(NULL, 0,user_cmd_process_event_handle);
	 
	 //os_timer_create(&TimersUartRcv, "TimersUartRcv", 1, 10, false, user_cmd_process_event_handle);//10ms
	 //os_timer_start(&TimersUartRcv);
	 

	 //user_cmd_process_event_handle(pxTimer);
	 //user_cmd_process_event_handle(& rx_char, 1);
	}

}
void HCHO_Test(uint8_t recv_data)
{
	printf("recv_data=%x\r\n",recv_data);
}

///command struct
typedef struct
{
	//uint8_t type;
	uint8_t opcode;
	
	uint8_t board_addr;
	uint8_t lock_addr;//-------
	uint8_t gu_ding;//---
	
	uint8_t bcc;
}command1_struct;

/////start process the data in

command1_struct m_data;

uint8_t ComputXor(uint8_t *InData, uint16_t Len)
{
	uint8_t Sum = 0;
	uint16_t i;
	for(i = 0; i < Len; i++)
	{
		Sum ^= InData[i];	
	}
	return Sum;
}




void lock_all_off(void)
{
	GO_1=0;
	//GI_1=0;

	GO_2=0;
	//GI_2=0;

	GO_3=0;
	//GI_3=0;


	GO_4=0;
	//GI_4=0;

	GO_5=0;
	//GI_5=0;

	GO_6=0;
	//GI_6=0;

	GO_7=0;
	//GI_7=0;

	GO_8=0;
	//GI_8=0;

	GO_9=0;
	//GI_9=0;

	GO_10=0;
	//GI_10=0;

	GO_11=0;
	//GI_11=0;

	GO_12=0;
	//GI_12=0;

	GO_13=0;
	//GI_13=0;

	GO_14=0;
	//GI_14=0;

	GO_15=0;
	//GI_15=0;

	GO_16=0;
	//GI_16=0;

	GO_17=0;
	//GI_17=0;

	GO_18=0;
	//GI_18=0;

	GO_19=0;
	//GI_19=0;

	GO_20=0;
	//GI_20=0;

	GO_21=0;
	//GI_21=0;

	GO_22=0;
	//GI_22=0;

	GO_23=0;
	//GI_23=0;

	GO_24=0;
	//GI_24=0;  

}
void lock_all_on_off(void)
{

	GO_1=1; 					//open
	delay_ms(100);  //>=20
	//if(1==GI_1)//no open
	{
		//debug_uart_send_data1(0x01);
		delay_ms(300);//100
	}
	//if(1==GI_1)//no open
	{
		//debug_uart_send_data1(0x02);
		//delay_ms(600);
	}
	GO_1=0;						//close
	delay_ms(400);LED1=!LED1;


	//LED1 =1;

	
	GO_2=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_2)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_2)//no open
	{
		//delay_ms(600);
	}
	GO_2=0;	 						 //close
	//LED1 =0;
	delay_ms(400);LED1=!LED1;

	
	
	GO_3=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_3)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_3)//no open
	{
		//delay_ms(600);
	}
	GO_3=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_4=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_4)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_4)//no open
	{
		//delay_ms(600);
	} 
	GO_4=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_5=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_5)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_5)//no open
	{
		//delay_ms(600);
	} 
	GO_5=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_6=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_6)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_6)//no open
	{
		//delay_ms(600);
	}
	GO_6=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_7=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_7)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_7)//no open
	{
		//delay_ms(600);
	}
	GO_7=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_8=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_8)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_8)//no open
	{
		//delay_ms(600);
	}
	GO_8=0;	 						 //close
	delay_ms(400);LED1=!LED1;
	

	GO_9=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_9)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_9)//no open
	{
		//delay_ms(600);
	}
	GO_9=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_10=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_10)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_10)//no open
	{
		//delay_ms(600);
	} 
	GO_10=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_11=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_11)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_11)//no open
	{
		//delay_ms(600);
	} 
	GO_11=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_12=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_12)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_12)//no open
	{
		//delay_ms(600);
	} 
	GO_12=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_13=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_13)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_13)//no open
	{
		//delay_ms(600);
	} 
	GO_13=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_14=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_14)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_14)//no open
	{
		//delay_ms(600);
	} 
	GO_14=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_15=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_15)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_15)//no open
	{
		//delay_ms(600);
	} 
	GO_15=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_16=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_16)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_16)//no open
	{
		//delay_ms(600);
	} 
	GO_16=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_17=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_17)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_17)//no open
	{
		//delay_ms(600);
	} 
	GO_17=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_18=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_18)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_18)//no open
	{
		//delay_ms(600);
	} 
	GO_18=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_19=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_19)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_19)//no open
	{
		//delay_ms(600);
	} 
	GO_19=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_20=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_20)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_20)//no open
	{
		//delay_ms(600);
	}   
	GO_20=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	
	GO_21=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_21)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_21)//no open
	{
		//delay_ms(600);
	}  
	GO_21=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_22=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_22)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_22)//no open
	{
		//delay_ms(600);
	} 
	GO_22=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_23=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_23)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_23)//no open
	{
		//delay_ms(600);
	} 
	GO_23=0;	 						 //close
	delay_ms(400);LED1=!LED1;


	GO_24=1;							 //open
	delay_ms(100);  //>=20
	//if(1==GI_24)//no open
	{
		delay_ms(300);
	}
	//if(1==GI_24)//no open
	{
		//delay_ms(600);
	} 
	GO_24=0;	 						 //close
	
	lock_all_off();

}
void data_parse()
{
	uint8_t bcc_temp;
	uint8_t tx_Buffer[256]={0};        //?????
	//uint8_t length = 0;             //??
	uint8_t gpio_level=0;//add
	uint8_t grp_level_1=0;
	uint8_t grp_level_2=0;
	uint8_t grp_level_3=0;
	uint8_t board_addr;
	
	uint8_t Uart1_Buffer_T[256]={0};        //?????
	uint8_t Uart1_Rx_T = 0;             //??
	
	SEGGER_RTT_printf(0, "-parse-Uart1_Rx = %d\n",Uart1_Rx);      //RTT打印
	Uart1_Rx_T = Uart1_Rx - 8;
	SEGGER_RTT_printf(0, "-Uart1_Rx_T = %d\n",Uart1_Rx_T);      //RTT打?
	memcpy(Uart1_Buffer_T,Uart1_Buffer+4,Uart1_Rx_T);
	

	board_addr= DSW_1 | (DSW_2<<1) | (DSW_3<<2) | (DSW_4<<3) | (DSW_5<<4) | (DSW_6<<5) ;//| (DSW_7<<6) | (DSW_8<<7);
	SEGGER_RTT_printf(0, "-board_addr = %02x\n",board_addr);
	SEGGER_RTT_printf(0, "-Uart1_Buffer_T[1] = %02x\n",Uart1_Buffer_T[1]);
	//if(board_addr == Uart1_Buffer_T[1])
	{
		if(5==Uart1_Rx_T)
		{
			m_data.opcode = Uart1_Buffer_T[0];
			m_data.board_addr = Uart1_Buffer_T[1];// to do
			m_data.lock_addr = Uart1_Buffer_T[2];//
			m_data.gu_ding = Uart1_Buffer_T[3];//
			m_data.bcc = Uart1_Buffer_T[4];

			bcc_temp = ComputXor(Uart1_Buffer_T,4);
			SEGGER_RTT_printf(0, "bcc_temp = %x\n",bcc_temp);
			if(bcc_temp == m_data.bcc)
			{
				switch(m_data.opcode)
				{
					case 0x8A:
						//----1------
						if(m_data.gu_ding  == 0x11)//process
						{
							switch(m_data.lock_addr)
							{
								case 1:
									GO_1=1; 					//open
									delay_ms(100);  //>=20
									//if(1==GI_1)//no open
									{
										SEGGER_RTT_printf(0, "----1111-----\n");
										delay_ms(300);
									}
									//if(1==GI_1)//no open
									{
										SEGGER_RTT_printf(0, "----2222-----\n");
										//delay_ms(600);
									}
									GO_1=0;						//close

									//LED1 =1;
									//gpio_level= GI_1;
																			SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								
								case 2:
									GO_2=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_2)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_2)//no open
									{
										//delay_ms(600);
									}
									GO_2=0;	 						 //close


									//LED1 =0;
									//gpio_level= GI_2;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								
								case 3:
									GO_3=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_3)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_3)//no open
									{
										//delay_ms(600);
									}
									GO_3=0;	 						 //close

									//gpio_level= GI_3;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 4:
									GO_4=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_4)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_4)//no open
									{
										//delay_ms(600);
									} 
									GO_4=0;	 						 //close

									//gpio_level= GI_4;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 5:
									GO_5=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_5)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_5)//no open
									{
										//delay_ms(600);
									} 
									GO_5=0;	 						 //close

									//gpio_level= GI_5;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 6:
									GO_6=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_6)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_6)//no open
									{
										//delay_ms(600);
									}
									GO_6=0;	 						 //close

									//gpio_level= GI_6;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 7:
									GO_7=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_7)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_7)//no open
									{
										//delay_ms(600);
									}
									GO_7=0;	 						 //close

									//gpio_level= GI_7;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 8:
									GO_8=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_8)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_8)//no open
									{
										//delay_ms(600);
									}
									GO_8=0;	 						 //close

									//gpio_level=  GI_8;//GI_2;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 9:
									GO_9=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_9)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_9)//no open
									{
										//delay_ms(600);
									}
									GO_9=0;	 						 //close

									//gpio_level=  GI_9;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 10:
									GO_10=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_10)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_10)//no open
									{
										//delay_ms(600);
									} 
									GO_10=0;	 						 //close

									//gpio_level=  GI_10;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 11:
									GO_11=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_11)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_11)//no open
									{
										//delay_ms(600);
									} 
									GO_11=0;	 						 //close

									//gpio_level=  GI_11;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 12:
									GO_12=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_12)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_12)//no open
									{
										//delay_ms(600);
									} 
									GO_12=0;	 						 //close

									//gpio_level=  GI_12;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 13:
									GO_13=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_13)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_13)//no open
									{
										//delay_ms(600);
									} 
									GO_13=0;	 						 //close

									//gpio_level=  GI_13;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 14:
									GO_14=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_14)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_14)//no open
									{
										//delay_ms(600);
									} 
									GO_14=0;	 						 //close

									//gpio_level=  GI_14;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 15:
									GO_15=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_15)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_15)//no open
									{
										//delay_ms(600);
									} 
									GO_15=0;	 						 //close

									//gpio_level=  GI_15;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 16:
									GO_16=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_16)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_16)//no open
									{
										//delay_ms(600);
									} 
									GO_16=0;	 						 //close

									//gpio_level=  GI_16;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 17:
									GO_17=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_17)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_17)//no open
									{
										//delay_ms(600);
									} 
									GO_17=0;	 						 //close

									//gpio_level=  GI_17;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 18:
									GO_18=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_18)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_18)//no open
									{
										//delay_ms(600);
									} 
									GO_18=0;	 						 //close

									//gpio_level=  GI_18;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 19:
									GO_19=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_19)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_19)//no open
									{
										//delay_ms(600);
									} 
									GO_19=0;	 						 //close

									//gpio_level=  GI_19;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 20:
									GO_20=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_20)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_20)//no open
									{
										//delay_ms(600);
									}   
									GO_20=0;	 						 //close

									//gpio_level=  GI_20;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 21:
									GO_21=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_21)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_21)//no open
									{
										//delay_ms(600);
									}  
									GO_21=0;	 						 //close

									//gpio_level=  GI_21;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 22:
									GO_22=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_22)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_22)//no open
									{
										//delay_ms(600);
									} 
									GO_22=0;	 						 //close

									//gpio_level=  GI_22;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 23:
									GO_23=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_23)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_23)//no open
									{
										//delay_ms(600);
									} 
									GO_23=0;	 						 //close

									//gpio_level=  GI_23;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 24:
									GO_24=1;							 //open
									delay_ms(100);  //>=20
									//if(1==GI_24)//no open
									{
										delay_ms(300);
									}
									//if(1==GI_24)//no open
									{
										//delay_ms(600);
									} 
									GO_24=0;	 						 //close

									//gpio_level=  GI_24;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;

								
								default:
									break;

							}
							lock_all_off();
							SEGGER_RTT_printf(0, "lock = %d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
							
							memcpy(tx_Buffer,"star",4);
							tx_Buffer[4]= m_data.opcode;
							tx_Buffer[5]= m_data.board_addr;
							tx_Buffer[6]= m_data.lock_addr;
							
							if(0x01 == gpio_level)
								tx_Buffer[7]= 0x11;//lock state todo open
							else
								tx_Buffer[7]= 0x00;//lock state todo close
							
							bcc_temp = ComputXor(tx_Buffer+4,4);
							tx_Buffer[8]= bcc_temp;
							memcpy(tx_Buffer+9,"end",3);
							
							tx_Buffer[12]='\0';
							
							spear_uart_send_datas(tx_Buffer,12);
							spear_rtt_send_datas(tx_Buffer,12);

							SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
						}
						else
						{
							SEGGER_RTT_printf(0, "error-2,m_data.opcode=%02x\n",m_data.opcode);
						}
						break;
					case 0x80:
						if(m_data.gu_ding  == 0x33)//process
						{
							if(0x00== m_data.lock_addr)//----4------
							{
								//grp_level_1= GI_1 | (GI_2<<1) | (GI_3<<2) | (GI_4<<3) | (GI_5<<4) | (GI_6<<5) | (GI_7<<6) | (GI_8<<7);
								//grp_level_2= GI_9 | (GI_10<<1) | (GI_11<<2) | (GI_12<<3) | (GI_13<<4) | (GI_14<<5) | (GI_15<<6) | (GI_16<<7);
								//grp_level_3= GI_17 | (GI_18<<1) | (GI_19<<2) | (GI_20<<3) | (GI_21<<4) | (GI_22<<5) | (GI_23<<6) | (GI_24<<7);
								SEGGER_RTT_printf(0, "grp_level_1 = %x\n",grp_level_1);
								SEGGER_RTT_printf(0, "grp_level_2 = %x\n",grp_level_2);
								SEGGER_RTT_printf(0, "grp_level_3 = %x\n",grp_level_3);
								
								memcpy(tx_Buffer,"star",4);
								tx_Buffer[4]= m_data.opcode;
								tx_Buffer[5]= m_data.board_addr;
								tx_Buffer[6]= grp_level_1;
								tx_Buffer[7]= grp_level_2;
								tx_Buffer[8]= grp_level_3;


								
								bcc_temp = ComputXor(tx_Buffer+4,5);
								tx_Buffer[9]= bcc_temp;
								memcpy(tx_Buffer+10,"end",3);//now is 2?
								
								tx_Buffer[12]='\0';
								
								spear_uart_send_datas(tx_Buffer,12);
								spear_rtt_send_datas(tx_Buffer,12);//to do 13?

								SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
								//spear_uart_send_datas
							}
							else//----3------
							{
								
								switch(m_data.lock_addr)
								{
									case 1:
										//gpio_level=  GI_1;
										break;
									case 2:
										//gpio_level=  GI_2;
										break;
									case 3:
										//gpio_level=  GI_3;
										break;
									case 4:
										//gpio_level=  GI_4;
										break;
									case 5:
										//gpio_level=  GI_5;
										break;
									case 6:
										//gpio_level=  GI_6;
									case 7:
										//gpio_level=  GI_7;
										break;
									case 8:
										//gpio_level=  GI_8;
										break;
									case 9:
										//gpio_level=  GI_9;
										break;
									case 10:
										//gpio_level=  GI_10;
										break;
									case 11:
										//gpio_level=  GI_11;
										break;
									case 12:
										//gpio_level=  GI_12;
										break;
									case 13:
										//gpio_level=  GI_13;
										break;
									case 14:
										//gpio_level=  GI_14;
										break;
									case 15:
										//gpio_level=  GI_15;
									case 16:
										//gpio_level=  GI_16;
										break;
									case 17:
										//gpio_level=  GI_17;
										break;
									case 18:
										//gpio_level=  GI_18;
										break;
									case 19:
										//gpio_level=  GI_19;
										break;
									case 20:
										//gpio_level=  GI_20;
										break;
									case 21:
										//gpio_level=  GI_21;
										break;
									case 22:
										//gpio_level=  GI_22;
										break;
									case 23:
										//gpio_level=  GI_23;
										break;
									case 24:
										//gpio_level=  GI_24;
										break;
									
									default:
										break;

								}
								SEGGER_RTT_printf(0, "--%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
								
								memcpy(tx_Buffer,"star",4);
								tx_Buffer[4]= m_data.opcode;
								tx_Buffer[5]= m_data.board_addr;
								tx_Buffer[6]= m_data.lock_addr;
								
								if(0x01 == gpio_level)
									tx_Buffer[7]= 0x11;//lock state todo open
								else
									tx_Buffer[7]= 0x00;//lock state todo close

								
								bcc_temp = ComputXor(tx_Buffer+4,4);
								tx_Buffer[8]= bcc_temp;
								memcpy(tx_Buffer+9,"end",3);
								
								tx_Buffer[12]='\0';
								
								spear_uart_send_datas(tx_Buffer,12);
								spear_rtt_send_datas(tx_Buffer,12);

								SEGGER_RTT_printf(0, "--ok,m_data.opcode=%02x\n",m_data.opcode);
							}
							
						}
						else
						{
							SEGGER_RTT_printf(0, "error-2,m_data.opcode=%02x\n",m_data.opcode);
						}
						break;
						

					default:
						break;
				}
				
				SEGGER_RTT_printf(0, "m_data.bcc = %x\n",m_data.bcc);
			}
			else
			{
				SEGGER_RTT_printf(0, "error-1-m_data.bcc = %x\n",m_data.bcc);
			}
			
		}
		else if(3==Uart1_Rx_T)
		{
			m_data.opcode = Uart1_Buffer_T[0];
			m_data.board_addr = Uart1_Buffer_T[1];

			m_data.bcc = Uart1_Buffer_T[2];
			
			bcc_temp = ComputXor(Uart1_Buffer_T,2);
			SEGGER_RTT_printf(0, "bcc_temp = %x\n",bcc_temp);
			if(bcc_temp == m_data.bcc)
			{
				switch(m_data.opcode)
				{
					case 0x90://--------2---------
						SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
						lock_all_on_off();
					
						//grp_level_1= GI_1 | (GI_2<<1) | (GI_3<<2) | (GI_4<<3) | (GI_5<<4) | (GI_6<<5) | (GI_7<<6) | (GI_8<<7);
						//grp_level_2= GI_9 | (GI_10<<1) | (GI_11<<2) | (GI_12<<3) | (GI_13<<4) | (GI_14<<5) | (GI_15<<6) | (GI_16<<7);
						//grp_level_3= GI_17 | (GI_18<<1) | (GI_19<<2) | (GI_20<<3) | (GI_21<<4) | (GI_22<<5) | (GI_23<<6) | (GI_24<<7);
						SEGGER_RTT_printf(0, "grp_level_1 = %x\n",grp_level_1);
						SEGGER_RTT_printf(0, "grp_level_2 = %x\n",grp_level_2);
						SEGGER_RTT_printf(0, "grp_level_3 = %x\n",grp_level_3);
						
						memcpy(tx_Buffer,"star",4);
						tx_Buffer[4]= 0x80;//m_data.opcode;
						tx_Buffer[5]= m_data.board_addr;
						tx_Buffer[6]= grp_level_1;
						tx_Buffer[7]= grp_level_2;
						tx_Buffer[8]= grp_level_3;


						
						bcc_temp = ComputXor(tx_Buffer+4,5);
						tx_Buffer[9]= bcc_temp;
						memcpy(tx_Buffer+10,"end",3);//now is 2?
						
						tx_Buffer[12]='\0';//tx_Buffer[12]='\0';
						
						spear_uart_send_datas(tx_Buffer,12);
						break;
					case 0x91://--------2.1---------
						SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
						SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
						lock_all_on_off();
					
						//grp_level_1= GI_1 | (GI_2<<1) | (GI_3<<2) | (GI_4<<3) | (GI_5<<4) | (GI_6<<5) | (GI_7<<6) | (GI_8<<7);
						//grp_level_2= GI_9 | (GI_10<<1) | (GI_11<<2) | (GI_12<<3) | (GI_13<<4) | (GI_14<<5) | (GI_15<<6) | (GI_16<<7);
						//grp_level_3= GI_17 | (GI_18<<1) | (GI_19<<2) | (GI_20<<3) | (GI_21<<4) | (GI_22<<5) | (GI_23<<6) | (GI_24<<7);
						SEGGER_RTT_printf(0, "grp_level_1 = %x\n",grp_level_1);
						SEGGER_RTT_printf(0, "grp_level_2 = %x\n",grp_level_2);
						SEGGER_RTT_printf(0, "grp_level_3 = %x\n",grp_level_3);
						
						memcpy(tx_Buffer,"star",4);
						tx_Buffer[4]= 0x80;//m_data.opcode;
						tx_Buffer[5]= m_data.board_addr;
						tx_Buffer[6]= grp_level_1;
						tx_Buffer[7]= grp_level_2;
						tx_Buffer[8]= grp_level_3;


						
						bcc_temp = ComputXor(tx_Buffer+4,5);
						tx_Buffer[9]= bcc_temp;
						memcpy(tx_Buffer+10,"end",3);//now is 2?
						
						tx_Buffer[12]='\0';//tx_Buffer[12]='\0';
						
						spear_uart_send_datas(tx_Buffer,12);
						break;
					case 0x92://--------2.2---------
						SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
						break;
					case 0x93://--------2.3---------
						SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
						break;
					case 0x70://--------2.4---------
						SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
						break;
					case 0x71://--------2.5---------
						SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
						break;					
					default:
						break;
				}
				
				SEGGER_RTT_printf(0, "m_data.bcc = %x\n",m_data.bcc);
			}
			else
			{
				SEGGER_RTT_printf(0, "error-1-m_data.bcc = %x\n",m_data.bcc);
			}
		
		}
	}

}


#include "KEY.h"
#include <stdbool.h>
static __IO int key1ShortPressCount = 0;
static __IO int key1LongPressCount  = 0;
static __IO int key2ShortPressCount = 0;
static __IO int key2LongPressCount  = 0;

bool mode_nomal;

/* Function declarations -----------------------------------------------------*/
static void key1PressCallback(KEY_Status status);
/**
  * @brief  Key 1 press callback.
  * @param  None.
  * @return None.
  */
static void key1PressCallback(KEY_Status status)
{
  if(status == KEY_ShortPress)
  {
    key1ShortPressCount++;
  }
  else if(status == KEY_LongPress)
  {
    key1LongPressCount++;
  }
}
u8 key1_flag=0;
u8 key2_flag=0;
u8 key3_flag=0;
u8 key4_flag=0;
u8 key5_flag=0;
u8 key6_flag=0;
u8 key7_flag=0;
u8 key8_flag=0;
u8 key9_flag=0;
u8 key10_flag=0;
u8 key11_flag=0;
u8 key12_flag=0;
u8 key13_flag=0;
u8 key14_flag=0;
u8 key15_flag=0;
u8 key16_flag=0;
u8 key17_flag=0;
u8 key18_flag=0;
u8 key19_flag=0;
u8 key20_flag=0;
u8 key21_flag=0;
u8 key22_flag=0;
u8 key23_flag=0;
u8 key24_flag=0;

#define lock_1 1
#define lock_2 2
#define lock_3 3
#define lock_4 4
#define lock_5 5
#define lock_6 6
#define lock_7 7
#define lock_8 8
#define lock_9 9
#define lock_10 10
#define lock_11 11
#define lock_12 12
#define lock_13 13
#define lock_14 14
#define lock_15 15
#define lock_16 16
#define lock_17 17
#define lock_18 18
#define lock_19 19
#define lock_20 20
#define lock_21 21
#define lock_22 22
#define lock_23 23
#define lock_24 24

#if 0
void key_fun(void)
{
	uint8_t tx_Buffer[256]={0};
	uint8_t bcc_temp;
	uint8_t board_addr;
	board_addr= DSW_1 | (DSW_2<<1) | (DSW_3<<2) | (DSW_4<<3) | (DSW_5<<4) | (DSW_6<<5) | (DSW_7<<6) | (DSW_8<<7);
	
	//grp1
	if((0==key1_flag)&&(GI_1==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_1==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key1_flag= %d\n",key1_flag); 
			key1_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_1;//lock addr
			
			if(0x01 == GI_1)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key1_flag&&(GI_1==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_1==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key1_flag= %d\n",key1_flag); 
			key1_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_1;//lock addr
			
			if(0x01 == GI_1)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp2-ok
	if((0==key2_flag)&&(GI_2==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_2==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key2_flag= %d\n",key2_flag); 
			key2_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_2;//lock addr
			
			if(0x01 == GI_2)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key2_flag&&(GI_2==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_2==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key2_flag= %d\n",key2_flag); 
			key2_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_2;//lock addr
			
			if(0x01 == GI_2)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	
	//grp3
	if((0==key3_flag)&&(GI_3==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_3==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key3_flag= %d\n",key3_flag); 
			key3_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_3;//lock addr
			
			if(0x01 == GI_3)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key3_flag&&(GI_3==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_3==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key3_flag= %d\n",key3_flag); 
			key3_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_3;//lock addr
			
			if(0x01 == GI_3)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	
		
	//grp4
	if((0==key4_flag)&&(GI_4==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_4==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key4_flag= %d\n",key4_flag); 
			key4_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_4;//lock addr
			
			if(0x01 == GI_4)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key4_flag&&(GI_4==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_4==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key4_flag= %d\n",key4_flag); 
			key4_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_4;//lock addr
			
			if(0x01 == GI_4)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp5
if((0==key5_flag)&&(GI_5==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_5==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key5_flag= %d\n",key5_flag); 
			key5_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_5;//lock addr
			
			if(0x01 == GI_5)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key5_flag&&(GI_5==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_5==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key5_flag= %d\n",key5_flag); 
			key5_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_5;//lock addr
			
			if(0x01 == GI_5)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp6
if((0==key6_flag)&&(GI_6==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_6==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key6_flag= %d\n",key6_flag); 
			key6_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_6;//lock addr
			
			if(0x01 == GI_6)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key6_flag&&(GI_6==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_6==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key6_flag= %d\n",key6_flag); 
			key6_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_6;//lock addr
			
			if(0x01 == GI_6)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp7
if((0==key7_flag)&&(GI_7==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_7==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key7_flag= %d\n",key7_flag); 
			key7_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_7;//lock addr
			
			if(0x01 == GI_7)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key7_flag&&(GI_7==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_7==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key7_flag= %d\n",key7_flag); 
			key7_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_7;//lock addr
			
			if(0x01 == GI_7)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp8
if((0==key8_flag)&&(GI_8==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_8==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key8_flag= %d\n",key8_flag); 
			key8_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_8;//lock addr
			
			if(0x01 == GI_8)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key8_flag&&(GI_8==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_8==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key8_flag= %d\n",key8_flag); 
			key8_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_8;//lock addr
			
			if(0x01 == GI_8)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp9
	if((0==key9_flag)&&(GI_9==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_9==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key9_flag= %d\n",key9_flag); 
			key9_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_9;//lock addr
			
			if(0x01 == GI_9)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key9_flag&&(GI_9==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_9==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key9_flag= %d\n",key9_flag); 
			key9_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_9;//lock addr
			
			if(0x01 == GI_9)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp10
	if((0==key10_flag)&&(GI_10==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_10==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key10_flag= %d\n",key10_flag); 
			key10_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_10;//lock addr
			
			if(0x01 == GI_10)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key10_flag&&(GI_10==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_10==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key10_flag= %d\n",key10_flag); 
			key10_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_10;//lock addr
			
			if(0x01 == GI_10)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp11
	if((0==key11_flag)&&(GI_11==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_11==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key11_flag= %d\n",key11_flag); 
			key11_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_11;//lock addr
			
			if(0x01 == GI_11)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key11_flag&&(GI_11==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_11==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key11_flag= %d\n",key11_flag); 
			key11_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_11;//lock addr
			
			if(0x01 == GI_11)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp12
if((0==key12_flag)&&(GI_12==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_12==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key12_flag= %d\n",key12_flag); 
			key12_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_12;//lock addr
			
			if(0x01 == GI_12)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key12_flag&&(GI_12==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_12==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key12_flag= %d\n",key12_flag); 
			key12_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_12;//lock addr
			
			if(0x01 == GI_12)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp13
	if((0==key13_flag)&&(GI_13==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_13==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key13_flag= %d\n",key13_flag); 
			key13_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_13;//lock addr
			
			if(0x01 == GI_13)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key13_flag&&(GI_13==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_13==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key13_flag= %d\n",key13_flag); 
			key13_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_13;//lock addr
			
			if(0x01 == GI_13)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp14
	if((0==key14_flag)&&(GI_14==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_14==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key14_flag= %d\n",key14_flag); 
			key14_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_14;//lock addr
			
			if(0x01 == GI_14)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key14_flag&&(GI_14==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_14==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key14_flag= %d\n",key14_flag); 
			key14_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_14;//lock addr
			
			if(0x01 == GI_14)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp15
	if((0==key15_flag)&&(GI_15==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_15==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key15_flag= %d\n",key15_flag); 
			key15_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_15;//lock addr
			
			if(0x01 == GI_15)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key15_flag&&(GI_15==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_15==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key15_flag= %d\n",key15_flag); 
			key15_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_15;//lock addr
			
			if(0x01 == GI_15)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp16
	if((0==key16_flag)&&(GI_16==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_16==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key16_flag= %d\n",key16_flag); 
			key16_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_16;//lock addr
			
			if(0x01 == GI_16)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key16_flag&&(GI_16==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_16==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key16_flag= %d\n",key16_flag); 
			key16_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_16;//lock addr
			
			if(0x01 == GI_16)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp17
	if((0==key17_flag)&&(GI_17==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_17==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key17_flag= %d\n",key17_flag); 
			key17_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_17;//lock addr
			
			if(0x01 == GI_17)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key17_flag&&(GI_17==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_17==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key17_flag= %d\n",key17_flag); 
			key17_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_17;//lock addr
			
			if(0x01 == GI_17)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp18
	if((0==key18_flag)&&(GI_18==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_18==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key18_flag= %d\n",key18_flag); 
			key18_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_18;//lock addr
			
			if(0x01 == GI_18)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key18_flag&&(GI_18==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_18==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key18_flag= %d\n",key18_flag); 
			key18_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_18;//lock addr
			
			if(0x01 == GI_18)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp19
	if((0==key19_flag)&&(GI_19==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_19==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key19_flag= %d\n",key19_flag); 
			key19_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_19;//lock addr
			
			if(0x01 == GI_19)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key19_flag&&(GI_19==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_19==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key19_flag= %d\n",key19_flag); 
			key19_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_19;//lock addr
			
			if(0x01 == GI_19)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp20
	if((0==key20_flag)&&(GI_20==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_20==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key20_flag= %d\n",key20_flag); 
			key20_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_20;//lock addr
			
			if(0x01 == GI_20)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key20_flag&&(GI_20==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_20==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key20_flag= %d\n",key20_flag); 
			key20_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_20;//lock addr
			
			if(0x01 == GI_20)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp21
	if((0==key21_flag)&&(GI_21==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_21==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key21_flag= %d\n",key21_flag); 
			key21_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_21;//lock addr
			
			if(0x01 == GI_21)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key21_flag&&(GI_21==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_21==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key21_flag= %d\n",key21_flag); 
			key21_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_21;//lock addr
			
			if(0x01 == GI_21)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp22
	if((0==key22_flag)&&(GI_22==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_22==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key22_flag= %d\n",key22_flag); 
			key22_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_22;//lock addr
			
			if(0x01 == GI_22)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key22_flag&&(GI_22==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_22==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key22_flag= %d\n",key22_flag); 
			key22_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_22;//lock addr
			
			if(0x01 == GI_22)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp23
	if((0==key23_flag)&&(GI_23==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_23==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key23_flag= %d\n",key23_flag); 
			key23_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_23;//lock addr
			
			if(0x01 == GI_23)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key23_flag&&(GI_23==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_23==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key23_flag= %d\n",key23_flag); 
			key23_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_23;//lock addr
			
			if(0x01 == GI_23)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	//grp24
	if((0==key24_flag)&&(GI_24==0))
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_24==0)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "close-key24_flag= %d\n",key24_flag); 
			key24_flag=1;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_24;//lock addr
			
			if(0x01 == GI_24)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
		}
		RS485_RX_EN();
	}
	if(key24_flag&&(GI_24==1))//default
	{
		RS485_TX_EN();
		delay_ms(10);//去抖动 
		if(GI_24==1)
		{
			SEGGER_RTT_printf(0, "board_addr = %02x\n",board_addr);//bo ma
			SEGGER_RTT_printf(0, "open-key24_flag= %d\n",key24_flag); 
			key24_flag=0;
			
			memcpy(tx_Buffer,"star",4);
			tx_Buffer[4]= 0x60;
			tx_Buffer[5]= board_addr;//board addr
			tx_Buffer[6]= lock_24;//lock addr
			
			if(0x01 == GI_24)
				tx_Buffer[7]= 0x11;//lock state todo open
			else
				tx_Buffer[7]= 0x00;//lock state todo close
			
			bcc_temp = ComputXor(tx_Buffer+4,4);
			tx_Buffer[8]= bcc_temp;
			memcpy(tx_Buffer+9,"end",3);
			
			tx_Buffer[12]='\0';
			
			spear_uart_send_datas(tx_Buffer,12);
			spear_rtt_send_datas(tx_Buffer,12);
			
		}
		RS485_RX_EN();
	}
	
	
	
	
//	
//	
//	if((0==key4_flag)&&(GI_4==0))
//	{
//		delay_ms(10);//去抖动 
//		if(GI_4==0)
//		{
//			SEGGER_RTT_printf(0, "close-key4_flag= %d\n",key4_flag); 
//			key4_flag=1;
//		}
//	}
//	if(key4_flag&&(GI_4==1))//default
//	{
//		delay_ms(10);//去抖动 
//		if(GI_4==1)
//		{
//			SEGGER_RTT_printf(0, "open-key4_flag= %d\n",key4_flag); 
//			key4_flag=0;
//		}
//	}

}




#endif

u8 key_mode =1;
 int main(void)
 {	
	u8 t;
	u8 len=3;	
	KEY_Status status;
	u32 tick_times=0; 
 
	delay_init();	    	 //延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	//uart_init(9600,HCHO_Test);	 //串口初始化为9600
	SdkEvalComIOConfig(Process_InputData);
	 
	//lock duanlu jiance io
	KEY_Init();
	EXTIX_Init();		//外部中断初始化
	 
	LED_Init();		  	 //初始化与LED连接的硬件接口 

	 //TIM4 led->  mode3: key long push:lock on one by one
	TIM4_Int_Init(499,7199);//10Khz的计数频率，计数到3000为0.3s     2999
	TIM4_Set(0);			//定时器4
	 
	//TIM2 key
	KEY_Init1(KEY_Pin2);
	KEY_SetPressCallback(KEY_Pin2, key1PressCallback);
	//TIM3 uart
	TIM3_Int_Init(99,7199);//10Khz的计数频率，计数到100为10ms  
	TIM3_Set(0);			//关闭定时器3
	 
//	RS485_RX_EN();
//	//printf("1-len=%d\r\n",len);
//	delay_ms(1300);
//	printf("--------------\r\n");
	SEGGER_RTT_printf(0,"*****************************************************************\n");
	
//	RS485_TX_EN();
//	UartSendString("1234567\r\n");
//	RS485_RX_EN();
//	 

	while(1)
	{
		if((1== packerflag))
		{
			RS485_TX_EN();
			SEGGER_RTT_printf(0, "\n");
			SEGGER_RTT_printf(0, "-main-Uart1_Rx = %d\n",Uart1_Rx);      //RTT打印
			SEGGER_RTT_printf(0, "---rcv-datas---"); 
			spear_rtt_send_datas(Uart1_Buffer,Uart1_Rx);
			
			//spear_uart_send_datas(Uart1_Buffer,Uart1_Rx); //debug


			data_parse();
			RS485_RX_EN();
			
			memset(Uart1_Buffer,0,13);//max =4+5+4 =13
			Uart1_Rx   = 0 ;
			packerflag = 0;
			//Uart1_index_flag_end =0;
		}
			
		status = KEY_GetStatus(KEY_Pin2);
		if(status != KEY_NoPress)
		{
			if(status == KEY_ShortPress)
			{
				//mode_nomal= ~mode_nomal;
				key2ShortPressCount++;
				if(0== mode_nomal)//mode2
				{
					TIM4_Int_Init(9999,7199);//2999  10Khz的计数频率，计数到3000为300ms  
					TIM4_Set(1);
					key_mode = 2;
					mode_nomal =1;
					SEGGER_RTT_printf(0, "1mode_nomal = %d\n",mode_nomal); 

					//jiance if off ,on lock
				}
				else//mode1, nomal ==1   clear to normal
				{
				//					TIM4_Int_Init(9999,7199);//10Khz的计数频率，计数到10000为1s  
				//					TIM4_Set(1);
					key_mode = 1;
					mode_nomal =0;
					SEGGER_RTT_printf(0, "2mode_nomal = %d\n",mode_nomal); 
				}
				SEGGER_RTT_printf(0, "key2ShortPressCount = %d\n",key2ShortPressCount); 
			}
			else//mode 3
			{
				// TIM4_Int_Init(9999,7199);//1s   10Khz的计数频率，计数到5000为500ms  
				// TIM4_Set(1);
				// if(1==key_mode)
				// {
				// 	SEGGER_RTT_printf(0, "---key_mode =3---\n"); 
				// 	key_mode = 3;
				// 	TIM4_Set(1);
				// }
				// mode_nomal =1;
				// key2LongPressCount++;
				// SEGGER_RTT_printf(0, "key2LongPressCount = %d\n",key2LongPressCount); 
				key_mode = 1;
				mode_nomal =0;		
				SEGGER_RTT_printf(0, "----key2LongPress----\n"); 
			}
		}


		tick_times++;
		if(tick_times%100==0)
		{
			if(1== key_mode)
			{
				SEGGER_RTT_printf(0, "---test1---\n"); 
				LED1=!LED1;
			}
		}
		if(tick_times%10==0)//2
		{
			if(2== key_mode)
			{
				SEGGER_RTT_printf(0, "---test2---\n"); 
				LED1=!LED1;
			}
		}
		if(tick_times%10==0)//3
		{
			if(3== key_mode)
			{
				SEGGER_RTT_printf(0, "---test3---\n"); 
				LED1=!LED1;
			}
		}
		
		
		if(tick_times%10==0)//3
		{
			if(1== lock_jiance_flag)
			{
				SEGGER_RTT_printf(0, "---test4  lock_jiance_flag---\n"); 
				LED2_LOCK = !LED2_LOCK;
			}
		}
		delay_ms(10); 
		
		
		//SEGGER_RTT_printf(0, "---test---\n"); 
		//key_fun();
		
		
	}	 
}







//		
//		t=KEY_close_Scan();		//得到键值
//		
//		if(key_Level==0)
//		{
//			key_Level=1;
//			switch(t)
//			{				 
//				case KEY2_PRES:
//					SEGGER_RTT_printf(0, "KEY_PRES_CLOSE = %d\n",t); 
//					break;
//				case KEY4_PRES:
//					SEGGER_RTT_printf(0, "KEY_PRES_CLOSE = %d\n",t); 
//					break;

//				default:
//					delay_ms(10);	
//			} 
//		}
//		
//		t=KEY_open_Scan();		//得到键值
//		if(key_Level==1)
//		{
//			key_Level = 0;
//			switch(t)
//			{				 
//				case KEY2_PRES:
//					SEGGER_RTT_printf(0, "KEY_PRES_OPEN = %d\n",t); 
//					break;
//				case KEY4_PRES:
//					SEGGER_RTT_printf(0, "KEY_PRES_OPEN = %d\n",t); 
//					break;

//				default:
//					delay_ms(10);	
//			}

//		}		









//		if(USART_RX_STA&0x8000)
//		{					   
//			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
//			printf("\r\n您发送的消息为:\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART1->DR=USART_RX_BUF[t];
//				while((USART1->SR&0X40)==0);//等待发送结束
//			}
//			printf("\r\n\r\n");//插入换行
//			USART_RX_STA=0;
//		}else
//		{
//			times++;
//			if(times%5000==0)
//			{
//				printf("\r\nALIENTEK MiniSTM32开发板 串口实验\r\n");
//				printf("正点原子@ALIENTEK\r\n\r\n\r\n");
//			}
//			if(times%200==0)printf("请输入数据,以回车键结束\r\n");  
//			if(times%30==0)LED0=!LED0;//闪烁LED,提示系统正在运行.
//			delay_ms(10);   
//		}

