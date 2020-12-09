#include "led.h"
#include "exti.h" 
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include <stdarg.h>
#include <string.h>
#include "timer.h"
#include "iwdg.h"

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
	RS485_TX_EN();
	while(len--)
	{
		//delay_ms(50);  
		//while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
		USART_SendData(USART1, *str);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); 
		str++;
	}
	RS485_RX_EN();
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
	LED2_CTL = 1;
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


// void lock_all_on_off(void)
// {

// 	GO_1=1; 					//open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_1)//no open
// 	{
// 		//debug_uart_send_data1(0x01);
// 		delay_ms(300);//100
// 	}
// 	//if(1==GI_1)//no open
// 	{
// 		//debug_uart_send_data1(0x02);
// 		//delay_ms(600);
// 	}
// 	GO_1=0;						//close
// 	delay_ms(400);LED1=!LED1;


// 	//LED1 =1;

	
// 	GO_2=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_2)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_2)//no open
// 	{
// 		//delay_ms(600);
// 	}
// 	GO_2=0;	 						 //close
// 	//LED1 =0;
// 	delay_ms(400);LED1=!LED1;

	
	
// 	GO_3=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_3)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_3)//no open
// 	{
// 		//delay_ms(600);
// 	}
// 	GO_3=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_4=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_4)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_4)//no open
// 	{
// 		//delay_ms(600);
// 	} 
// 	GO_4=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_5=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_5)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_5)//no open
// 	{
// 		//delay_ms(600);
// 	} 
// 	GO_5=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_6=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_6)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_6)//no open
// 	{
// 		//delay_ms(600);
// 	}
// 	GO_6=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_7=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_7)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_7)//no open
// 	{
// 		//delay_ms(600);
// 	}
// 	GO_7=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_8=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_8)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_8)//no open
// 	{
// 		//delay_ms(600);
// 	}
// 	GO_8=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;
	

// 	GO_9=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_9)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_9)//no open
// 	{
// 		//delay_ms(600);
// 	}
// 	GO_9=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_10=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_10)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_10)//no open
// 	{
// 		//delay_ms(600);
// 	} 
// 	GO_10=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_11=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_11)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_11)//no open
// 	{
// 		//delay_ms(600);
// 	} 
// 	GO_11=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_12=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_12)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_12)//no open
// 	{
// 		//delay_ms(600);
// 	} 
// 	GO_12=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_13=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_13)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_13)//no open
// 	{
// 		//delay_ms(600);
// 	} 
// 	GO_13=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_14=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_14)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_14)//no open
// 	{
// 		//delay_ms(600);
// 	} 
// 	GO_14=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_15=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_15)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_15)//no open
// 	{
// 		//delay_ms(600);
// 	} 
// 	GO_15=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_16=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_16)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_16)//no open
// 	{
// 		//delay_ms(600);
// 	} 
// 	GO_16=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_17=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_17)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_17)//no open
// 	{
// 		//delay_ms(600);
// 	} 
// 	GO_17=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_18=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_18)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_18)//no open
// 	{
// 		//delay_ms(600);
// 	} 
// 	GO_18=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_19=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_19)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_19)//no open
// 	{
// 		//delay_ms(600);
// 	} 
// 	GO_19=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_20=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_20)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_20)//no open
// 	{
// 		//delay_ms(600);
// 	}   
// 	GO_20=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


	
// 	GO_21=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_21)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_21)//no open
// 	{
// 		//delay_ms(600);
// 	}  
// 	GO_21=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_22=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_22)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_22)//no open
// 	{
// 		//delay_ms(600);
// 	} 
// 	GO_22=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_23=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_23)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_23)//no open
// 	{
// 		//delay_ms(600);
// 	} 
// 	GO_23=0;	 						 //close
// 	delay_ms(400);LED1=!LED1;


// 	GO_24=1;							 //open
// 	delay_ms(100);  //>=20
// 	//if(1==GI_24)//no open
// 	{
// 		delay_ms(300);
// 	}
// 	//if(1==GI_24)//no open
// 	{
// 		//delay_ms(600);
// 	} 
// 	GO_24=0;	 						 //close
	
// 	lock_all_off();

// }

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
	if(board_addr == Uart1_Buffer_T[1])
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
									LED2_CTL = 0;
									GO_1=1; 					//open
									delay_ms(800);  //>=20
									LED2_CTL = 1;
									GO_1=0;						//close

									//LED1 =1;
									//gpio_level= GI_1;
																			SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								
								case 2:
									LED2_CTL = 0;
									GO_2=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;

									GO_2=0;	 						 //close


									//LED1 =0;
									//gpio_level= GI_2;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								
								case 3:
									LED2_CTL = 0;
									GO_3=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;

									GO_3=0;	 						 //close

									//gpio_level= GI_3;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 4:
									LED2_CTL = 0;
									GO_4=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;

									GO_4=0;	 						 //close

									//gpio_level= GI_4;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 5:
									LED2_CTL = 0;
									GO_5=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;

									GO_5=0;	 						 //close

									//gpio_level= GI_5;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 6:
									LED2_CTL = 0;
									GO_6=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;

									GO_6=0;	 						 //close

									//gpio_level= GI_6;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 7:
									LED2_CTL = 0;
									GO_7=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;

									GO_7=0;	 						 //close

									//gpio_level= GI_7;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 8:
									LED2_CTL = 0;
									GO_8=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;
	
									GO_8=0;	 						 //close

									//gpio_level=  GI_8;//GI_2;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 9:
									LED2_CTL = 0;
									GO_9=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;

									GO_9=0;	 						 //close

									//gpio_level=  GI_9;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 10:
									LED2_CTL = 0;
									GO_10=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;

									GO_10=0;	 						 //close

									//gpio_level=  GI_10;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 11:
									LED2_CTL = 0;
									GO_11=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;

									GO_11=0;	 						 //close

									//gpio_level=  GI_11;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 12:
									LED2_CTL = 0;
									GO_12=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;

									GO_12=0;	 						 //close

									//gpio_level=  GI_12;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 13:
									LED2_CTL = 0;
									GO_13=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;

									GO_13=0;	 						 //close

									//gpio_level=  GI_13;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 14:
									LED2_CTL = 0;
									GO_14=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;

									GO_14=0;	 						 //close

									//gpio_level=  GI_14;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 15:
									LED2_CTL = 0;
									GO_15=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;
 
									GO_15=0;	 						 //close

									//gpio_level=  GI_15;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 16:
									LED2_CTL = 0;
									GO_16=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;

									GO_16=0;	 						 //close

									//gpio_level=  GI_16;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 17:
									LED2_CTL = 0;
									GO_17=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;
	
									GO_17=0;	 						 //close

									//gpio_level=  GI_17;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 18:
									LED2_CTL = 0;
									GO_18=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;

									GO_18=0;	 						 //close

									//gpio_level=  GI_18;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 19:
									LED2_CTL = 0;
									GO_19=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;

									GO_19=0;	 						 //close

									//gpio_level=  GI_19;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 20:
									LED2_CTL = 0;
									GO_20=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;
  
									GO_20=0;	 						 //close

									//gpio_level=  GI_20;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 21:
									LED2_CTL = 0;
									GO_21=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;
  
									GO_21=0;	 						 //close

									//gpio_level=  GI_21;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 22:
									LED2_CTL = 0;
									GO_22=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;

									GO_22=0;	 						 //close

									//gpio_level=  GI_22;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 23:
									LED2_CTL = 0;
									GO_23=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;

									GO_23=0;	 						 //close

									//gpio_level=  GI_23;
									//SEGGER_RTT_printf(0, "%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
									break;
								case 24:
									LED2_CTL = 0;
									GO_24=1;							 //open
									delay_ms(800);  //>=20
									LED2_CTL = 1;
	
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
					// case 0x80:
					// 	if(m_data.gu_ding  == 0x33)//process
					// 	{
					// 		if(0x00== m_data.lock_addr)//----4------
					// 		{
					// 			//grp_level_1= GI_1 | (GI_2<<1) | (GI_3<<2) | (GI_4<<3) | (GI_5<<4) | (GI_6<<5) | (GI_7<<6) | (GI_8<<7);
					// 			//grp_level_2= GI_9 | (GI_10<<1) | (GI_11<<2) | (GI_12<<3) | (GI_13<<4) | (GI_14<<5) | (GI_15<<6) | (GI_16<<7);
					// 			//grp_level_3= GI_17 | (GI_18<<1) | (GI_19<<2) | (GI_20<<3) | (GI_21<<4) | (GI_22<<5) | (GI_23<<6) | (GI_24<<7);
					// 			SEGGER_RTT_printf(0, "grp_level_1 = %x\n",grp_level_1);
					// 			SEGGER_RTT_printf(0, "grp_level_2 = %x\n",grp_level_2);
					// 			SEGGER_RTT_printf(0, "grp_level_3 = %x\n",grp_level_3);
								
					// 			memcpy(tx_Buffer,"star",4);
					// 			tx_Buffer[4]= m_data.opcode;
					// 			tx_Buffer[5]= m_data.board_addr;
					// 			tx_Buffer[6]= grp_level_1;
					// 			tx_Buffer[7]= grp_level_2;
					// 			tx_Buffer[8]= grp_level_3;


								
					// 			bcc_temp = ComputXor(tx_Buffer+4,5);
					// 			tx_Buffer[9]= bcc_temp;
					// 			memcpy(tx_Buffer+10,"end",3);//now is 2?
								
					// 			tx_Buffer[12]='\0';
								
					// 			spear_uart_send_datas(tx_Buffer,12);
					// 			spear_rtt_send_datas(tx_Buffer,12);//to do 13?

					// 			SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
					// 			//spear_uart_send_datas
					// 		}
					// 		else//----3------
					// 		{
								
					// 			switch(m_data.lock_addr)
					// 			{
					// 				case 1:
					// 					//gpio_level=  GI_1;
					// 					break;
					// 				case 2:
					// 					//gpio_level=  GI_2;
					// 					break;
					// 				case 3:
					// 					//gpio_level=  GI_3;
					// 					break;
					// 				case 4:
					// 					//gpio_level=  GI_4;
					// 					break;
					// 				case 5:
					// 					//gpio_level=  GI_5;
					// 					break;
					// 				case 6:
					// 					//gpio_level=  GI_6;
					// 				case 7:
					// 					//gpio_level=  GI_7;
					// 					break;
					// 				case 8:
					// 					//gpio_level=  GI_8;
					// 					break;
					// 				case 9:
					// 					//gpio_level=  GI_9;
					// 					break;
					// 				case 10:
					// 					//gpio_level=  GI_10;
					// 					break;
					// 				case 11:
					// 					//gpio_level=  GI_11;
					// 					break;
					// 				case 12:
					// 					//gpio_level=  GI_12;
					// 					break;
					// 				case 13:
					// 					//gpio_level=  GI_13;
					// 					break;
					// 				case 14:
					// 					//gpio_level=  GI_14;
					// 					break;
					// 				case 15:
					// 					//gpio_level=  GI_15;
					// 				case 16:
					// 					//gpio_level=  GI_16;
					// 					break;
					// 				case 17:
					// 					//gpio_level=  GI_17;
					// 					break;
					// 				case 18:
					// 					//gpio_level=  GI_18;
					// 					break;
					// 				case 19:
					// 					//gpio_level=  GI_19;
					// 					break;
					// 				case 20:
					// 					//gpio_level=  GI_20;
					// 					break;
					// 				case 21:
					// 					//gpio_level=  GI_21;
					// 					break;
					// 				case 22:
					// 					//gpio_level=  GI_22;
					// 					break;
					// 				case 23:
					// 					//gpio_level=  GI_23;
					// 					break;
					// 				case 24:
					// 					//gpio_level=  GI_24;
					// 					break;
									
					// 				default:
					// 					break;

					// 			}
					// 			SEGGER_RTT_printf(0, "--%d:gpio_level = %x\n",m_data.lock_addr,gpio_level);
								
					// 			memcpy(tx_Buffer,"star",4);
					// 			tx_Buffer[4]= m_data.opcode;
					// 			tx_Buffer[5]= m_data.board_addr;
					// 			tx_Buffer[6]= m_data.lock_addr;
								
					// 			if(0x01 == gpio_level)
					// 				tx_Buffer[7]= 0x11;//lock state todo open
					// 			else
					// 				tx_Buffer[7]= 0x00;//lock state todo close

								
					// 			bcc_temp = ComputXor(tx_Buffer+4,4);
					// 			tx_Buffer[8]= bcc_temp;
					// 			memcpy(tx_Buffer+9,"end",3);
								
					// 			tx_Buffer[12]='\0';
								
					// 			spear_uart_send_datas(tx_Buffer,12);
					// 			spear_rtt_send_datas(tx_Buffer,12);

					// 			SEGGER_RTT_printf(0, "--ok,m_data.opcode=%02x\n",m_data.opcode);
					// 		}
							
					// 	}
					// 	else
					// 	{
					// 		SEGGER_RTT_printf(0, "error-2,m_data.opcode=%02x\n",m_data.opcode);
					// 	}
					// 	break;
						

					default:
						SEGGER_RTT_printf(0, "---5---default------\n");
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
						// lock_all_on_off();
						TIM4_Int_Init(999,7199);//2999  10Khz的计数频率，计数到3000为300ms  
						TIM4_Set(1);
						lock_channel=0;

						key_mode = 2;
						mode_nomal =1;
						SEGGER_RTT_printf(0, "1-a-mode_nomal = %d\n",mode_nomal); 

						//grp_level_1= GI_1 | (GI_2<<1) | (GI_3<<2) | (GI_4<<3) | (GI_5<<4) | (GI_6<<5) | (GI_7<<6) | (GI_8<<7);
						//grp_level_2= GI_9 | (GI_10<<1) | (GI_11<<2) | (GI_12<<3) | (GI_13<<4) | (GI_14<<5) | (GI_15<<6) | (GI_16<<7);
						//grp_level_3= GI_17 | (GI_18<<1) | (GI_19<<2) | (GI_20<<3) | (GI_21<<4) | (GI_22<<5) | (GI_23<<6) | (GI_24<<7);
						SEGGER_RTT_printf(0, "grp_level_1 = %x\n",grp_level_1);
						SEGGER_RTT_printf(0, "grp_level_2 = %x\n",grp_level_2);
						SEGGER_RTT_printf(0, "grp_level_3 = %x\n",grp_level_3);
						
						// memcpy(tx_Buffer,"star",4);
						// tx_Buffer[4]= 0x80;//m_data.opcode;
						// tx_Buffer[5]= m_data.board_addr;
						// tx_Buffer[6]= grp_level_1;
						// tx_Buffer[7]= grp_level_2;
						// tx_Buffer[8]= grp_level_3;


						
						// bcc_temp = ComputXor(tx_Buffer+4,5);
						// tx_Buffer[9]= bcc_temp;
						// memcpy(tx_Buffer+10,"end",3);//now is 2?
						
						// tx_Buffer[12]='\0';//tx_Buffer[12]='\0';
						
						// spear_uart_send_datas(tx_Buffer,12);
						break;
					case 0x91://--------2.1---------
						SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
						SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
						// lock_all_on_off();
						TIM4_Int_Init(999,7199);//2999  10Khz的计数频率，计数到3000为300ms  
						TIM4_Set(1);
						lock_channel=0;

						key_mode = 2;
						mode_nomal =1;
						SEGGER_RTT_printf(0, "1-a-mode_nomal = %d\n",mode_nomal); 
					
						//grp_level_1= GI_1 | (GI_2<<1) | (GI_3<<2) | (GI_4<<3) | (GI_5<<4) | (GI_6<<5) | (GI_7<<6) | (GI_8<<7);
						//grp_level_2= GI_9 | (GI_10<<1) | (GI_11<<2) | (GI_12<<3) | (GI_13<<4) | (GI_14<<5) | (GI_15<<6) | (GI_16<<7);
						//grp_level_3= GI_17 | (GI_18<<1) | (GI_19<<2) | (GI_20<<3) | (GI_21<<4) | (GI_22<<5) | (GI_23<<6) | (GI_24<<7);
						SEGGER_RTT_printf(0, "grp_level_1 = %x\n",grp_level_1);
						SEGGER_RTT_printf(0, "grp_level_2 = %x\n",grp_level_2);
						SEGGER_RTT_printf(0, "grp_level_3 = %x\n",grp_level_3);
						
						// memcpy(tx_Buffer,"star",4);
						// tx_Buffer[4]= 0x80;//m_data.opcode;
						// tx_Buffer[5]= m_data.board_addr;
						// tx_Buffer[6]= grp_level_1;
						// tx_Buffer[7]= grp_level_2;
						// tx_Buffer[8]= grp_level_3;


						
						// bcc_temp = ComputXor(tx_Buffer+4,5);
						// tx_Buffer[9]= bcc_temp;
						// memcpy(tx_Buffer+10,"end",3);//now is 2?
						
						// tx_Buffer[12]='\0';//tx_Buffer[12]='\0';
						
						// spear_uart_send_datas(tx_Buffer,12);
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


					case 0xf1://--------2.6---------  software version  add
						SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
						memcpy(tx_Buffer,"star",4);
						tx_Buffer[4]= m_data.opcode;
						tx_Buffer[5]= board_addr;

						tx_Buffer[6]= 0x00;//major  V0.0.1
						tx_Buffer[7]= 0x00;//minor
						tx_Buffer[8]= 0x01;//rev


						
						bcc_temp = ComputXor(tx_Buffer+4,5);
						tx_Buffer[9]= bcc_temp;
						memcpy(tx_Buffer+10,"end",3);//now is 2?
						
						tx_Buffer[13]='\0';//tx_Buffer[12]='\0';
						
						spear_uart_send_datas(tx_Buffer,13);
						break;		

					case 0xf2://--------2.7--------- hardware version and dan/shuang xian type  add
						SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
						memcpy(tx_Buffer,"star",4);
						tx_Buffer[4]= m_data.opcode;
						tx_Buffer[5]= board_addr;

						tx_Buffer[6]= 0x04;//major  V4.0.B_1
						tx_Buffer[7]= 0x00;//minor
						tx_Buffer[8]= 0x0B;//REV
						tx_Buffer[9]= 0x01;//dan:1/shuang:2 xian

						
						bcc_temp = ComputXor(tx_Buffer+4,6);
						tx_Buffer[10]= bcc_temp;
						memcpy(tx_Buffer+11,"end",3);//now is 2?
						
						tx_Buffer[14]='\0';//tx_Buffer[12]='\0';
						
						spear_uart_send_datas(tx_Buffer,14);
						break;
					default:
						SEGGER_RTT_printf(0, "---3---default------\n");
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




u8 key_mode =1;
 int main(void)
 {	
	u8 t;
	u8 len=3;	
	KEY_Status status;
	u32 tick_times=0; 
	u16 timex_t3=0; 
 
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
	IWDG_Init(7,4094);
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
			// RS485_TX_EN();
			SEGGER_RTT_printf(0, "\n");
			SEGGER_RTT_printf(0, "-main-Uart1_Rx = %d\n",Uart1_Rx);      //RTT打印
			SEGGER_RTT_printf(0, "---rcv-datas---"); 
			spear_rtt_send_datas(Uart1_Buffer,Uart1_Rx);
			
			//spear_uart_send_datas(Uart1_Buffer,Uart1_Rx); //debug


			data_parse();
			// RS485_RX_EN();
			
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
					TIM4_Int_Init(999,7199);//2999  10Khz的计数频率，计数到3000为300ms  
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
					lock_all_off();
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
		timex_t3++;
		

		if(timex_t3==75)//0.75s 75
		{
			timex_t3=0;
			IWDG_Feed();//24s must go here
			SEGGER_RTT_printf(0, "------------feed dog ongo-----------\n");	
		}
		if(tick_times%75==0)//100
		{
			if(1== key_mode)
			{
				SEGGER_RTT_printf(0, "---test1---\n"); 
				LED1=!LED1;
			}
		}
		if(tick_times%20==0)//2
		{
			if(2== key_mode)
			{
				SEGGER_RTT_printf(0, "---test2---\n"); 
				LED1=!LED1;
			}
		}
		// if(tick_times%10==0)//3
		// {
		// 	if(3== key_mode)
		// 	{
		// 		SEGGER_RTT_printf(0, "---test3---\n"); 
		// 		LED1=!LED1;
		// 	}
		// }
		
		
		if(tick_times%20==0)//3
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

