/******************** (C) COPYRIGHT 2015 WYChen********************************
* File Name          : encoder.c
* Author             : WYChen
* Version            : V1.0.0
* Date               : 06/24/2015
* Description        : The operation of Incremental_Encoder.
*                      This file provides all functions to operate Encoder.
*******************************************************************************/
#include "encoder.h"

//A�� --> PB6 
//B�� --> PB7
//Z�� --> δ��



/**********************************************************
*������TIM3_Mode_Config(void)
*���ܣ�����ʱ��3������ģʽ����
*��������
*���أ���
*��ע����
**********************************************************/
void TIM4_Mode_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
/*----------------------------------------------------------------*/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
	
  GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PA.06,07 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;						//  ��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);

/*----------------------------------------------------------------*/	

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʹ��TIM4
	TIM_DeInit(TIM4);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
  TIM_TimeBaseStructure.TIM_Period =Encoder_BM*4-1;
  TIM_TimeBaseStructure.TIM_Prescaler =0;	    //����Ԥ��Ƶ:
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��:����Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
	/*��ʼ��TIM3��ʱ�� */
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	/*--------------��������---------------------����ģʽ------------------*/
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising�����ز���
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;         //�Ƚ��˲���
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  
	
 // Clear all pending interrupts
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);   //ʹ���ж�
  //Reset counter
  TIM4->CNT =10000;				//  ��ʼֵ����10000
	
	
	TIM_Cmd(TIM4, ENABLE);   //ʹ�ܶ�ʱ��3
}


/**********************************************************
*������TIM3_Init(void)
*���ܣ���ʼ����ʱ��3
*��������
*���أ���
*��ע����
**********************************************************/
void TIM4_Init(void)
{
  TIM4_Mode_Config();
}


/**********************************************************
*������update_angle(void)
*���ܣ�������������ݵõ��Ƕ�ֵ
*��������
*���أ��Ƕ�ֵ
*��ע��Encoder_BM=360; �ֱ���0.25��,��������
**********************************************************/
volatile s16 update_angle(void)
{
	volatile s16  angle=0;
	volatile s16  getangle=0;
	
	angle = TIM_GetCounter(TIM4);
	
	//����Ƕ�
	while(angle >=  Encoder_BM*2)		{angle -= Encoder_BM*4;}
	while(angle <= -Encoder_BM*2)		{angle += Encoder_BM*4;}
	
		getangle = angle*360/(Encoder_BM*4);
	
	return getangle;
}
/**************************************************************************
�������ܣ���λʱ���ȡ����������
��ڲ�������ʱ��
����  ֵ���ٶ�ֵ
**************************************************************************/
int Read_Encoder(u8 TIMX)
{
			int Encoder_TIM;    
			 switch(TIMX)
			 {
				 case 2:  Encoder_TIM= (short)TIM2 -> CNT; break;
				 case 3:  Encoder_TIM= (short)TIM3 -> CNT; break;	
				 case 4:  Encoder_TIM= (short)TIM4 -> CNT; break;	
				 default:  Encoder_TIM=0;
			 }
			return Encoder_TIM;
}
void TIM4_IRQHandler(void)
{   
    if(TIM4->SR&0x0001)//  ����ж�
    {
        ;
    }   
    TIM4->SR&=~(1<<0);// ����жϱ�־λ
}
