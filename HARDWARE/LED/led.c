#include "led.h"
#include "SEGGER_RTT.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK mini?SSTM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC\
												|RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��PA,PD�˿�ʱ��
	

// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PA.8 �˿�����
// GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
// GPIO_SetBits(GPIOA,GPIO_Pin_8);						 //PA.8 �����

// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 �˿�����, �������
// GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
// GPIO_SetBits(GPIOD,GPIO_Pin_2); 						 //PD.2 ����� 
	
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->Pc2 �˿�����, �������
// GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
// GPIO_SetBits(GPIOC,GPIO_Pin_2); 						 //����� 
	
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	//a13 a14 a15    b3 b4
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
	//LED
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	    		 //LED1-->PB5 �˿�����, �������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GPIO_ResetBits(GPIOA,GPIO_Pin_15); 						 //����� 

	//rs485 RE
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	    		 //LED1-->Pc2 �˿�����, �������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	RS485_RX_EN();
	
	//LED2_LOCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PB5 �˿�����, �������
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GPIO_ResetBits(GPIOB,GPIO_Pin_5); 						 //����� 


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	    		 //LED1-->PB5 �˿�����, �������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GPIO_SetBits(GPIOA,GPIO_Pin_12); 						 //����� 


//	//i group1
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
// 	GPIO_Init(GPIOC, &GPIO_InitStructure);//
//	//i group2
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
// 	GPIO_Init(GPIOC, &GPIO_InitStructure);//

// ...
	
	
	//o group1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_1=0; 						 //����� 
	
	//o group2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_2=0;	 						 //����� 

	//o group3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_3=0;	 						 //����� 
	//o group4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_4=0;	 						 //����� 
	//o group5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_5=0;	 						 //����� 
	//o group6
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_6=0;	 						 //����� 
	//o group7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_7=0;	 						 //����� 	
	//o group8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_8=0;	 						 //����� 	
	//o group9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_9=0;	 						 //����� 
	//o group10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_10=0;	 						 //����� 
	//o group11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_11=0;	 						 //����� 
	//o group12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_12=0;	 						 //����� 
	//o group13
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_13=0;	 						 //����� 
	//o group14
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_14=0;	 						 //����� 
	//o group15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_15=0;	 						 //����� 
	//o group16
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_16=0;	 						 //����� 
	//o group17
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_17=0;	 						 //����� 

	//o group18
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_18=0;	 						 //����� 

	//o group19
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_19=0;	 						 //����� 

	//o group20
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_20=0;	 						 //����� 

	//o group21
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_21=0;	 						 //����� 

	//o group22
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_22=0;	 						 //����� 

	//o group23
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_23=0;	 						 //����� 

	//o group24
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GO_24=0;	 						 //����� 




//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����-----
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//Pc3
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
//	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��
	
}











//����TIM4�Ŀ���
//sta:0���ر�;1,����;
void TIM4_Set(u8 sta)
{
	if(sta)
	{
       
		TIM_SetCounter(TIM4,0);//���������
		TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx	
	}
	else 
		TIM_Cmd(TIM4, DISABLE);//�رն�ʱ��4	   
}


//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM4_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM4��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx				
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );	
}

#include <stdbool.h>
bool zijian_ongo_flag=0;
u8 lock_channel=0;
//u8 lock_channel_mode2=0;
//��ʱ��3�жϷ������
void TIM4_IRQHandler(void)   //TIM4�ж�
{
	uint8_t gpio_level;
	uint8_t tx_Buffer[64]={0};        //?????
	uint8_t bcc_temp;
	uint8_t board_addr;
	SEGGER_RTT_printf(0, "TIM4_IRQHandler\n"); 
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //���TIM4�����жϷ������
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
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





