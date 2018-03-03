#include "timer.h"
#include "adc.h"
#include "motor.h"
#include "PID.h"
#include "encoder.h"

/////        ɨ��ʹ�á�

//ͨ�ö�ʱ���жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��5!
void Timer5_Init(u16 arr,u16 psc)
{
				TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
				NVIC_InitTypeDef NVIC_InitStructure;

				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //ʱ��ʹ��

				TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
				TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
				TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
				TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
				TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
		 
				  TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
					TIM5, //TIM5
					TIM_IT_Update ,
					ENABLE  //ʹ��
					);
					NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM5�ж�
					NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
					NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
					NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
					NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

					TIM_Cmd(TIM5, ENABLE);  //ʹ��TIMx����
									 
}

///  Set_PID_Angle(340,2600);
///  Set_PID_Location(65,3200);
extern int Position_Zero;   //===��������������� Ŀ��ֵ
int  	  Angle;  					 	       //===�Ƕ� 
int      LAST_Angle;				 //=== ��һ�εĽǶ�
int    	Angle_PWM; 			   //=== �Ƕȵ�PWM
int		  Encoder;               //=== ��������ֵ
int 			Encoder_PWM;		 //=== �������������PWM
int			PWM_VALUE;       //=== PWM����ֵ
int 			XIAN_FU=3100;    //=== �޷�
int 			Encoder_Last;			 //=== ��һ�εı�������ֵ 
int		  Speed;									 //===  �ٶ�
int      delay_25ms;					 //=== ��ʱ25ms
//int      delay_10ms;				 //=== ��ʱ10ms
int      QB_FLAG;						 //=== ���ڵı�־λ
extern int FUNCTION_1;
extern int ZHONGZHI;		  //===  ��ֵ
int      QB_STOP_ANG = 70;  //===  ���ڷ�Χ�ĽǶ� Ϊ70��  ���� �·� 140�� ��������

int    Position_TARGET = 1120;   //===  תȦ�� ���� ��������ֵ
int    count = 0;															//===  ����		
int    Draw_circle_FLAG;							//===  ��Բ�ı�־λ   ˳ʱ��
int    Draw_circle_FLAG_opposite;   	//===  ��Բ�ı�־λ    ��ʱ��
/******************** TIM5  �ж�    ����*************************/
void TIM5_IRQHandler(void)   
{
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
					TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
					//   ɨ�貿�֡�  5msһ��ɨ��
							/******************  תȦ���ܣ�����ڵ���֮��ʹ��*********************/
			
															  if(Draw_circle_FLAG==1) //===�ڸ�˳ʱ���˶�
																{
																			Position_Zero++; 
																				count++;	
																			if(count==Position_TARGET) 	Draw_circle_FLAG=0,count=0;
																}	
																
																
																if(Draw_circle_FLAG_opposite == 1)//===�ڸ���ʱ���˶�
																{
																			Position_Zero--; 
																				count++;	
																			if(count==Position_TARGET) 	Draw_circle_FLAG_opposite=0,count=0;
																	
																}														

						/****************** PD����  �ǶȻ�  λ�û�********************/
															LAST_Angle = Angle;//=== ��һ�εĽǶ�ֵ���������
															Angle = Angle_Get();//===  �Ƕȸ���
															Encoder = Read_Encoder(4);//=== λ�ø���
					           	if((Angle > (ZHONGZHI-QB_STOP_ANG))&&(Angle<(ZHONGZHI+QB_STOP_ANG)))
											{
																						Angle_PWM =balance(Angle);            //===�Ƕ�PD����	
																									delay_25ms++;
																					 if(delay_25ms == 5)
																					 {
																									Encoder_PWM=Position(Encoder);
																									//==== �Ա������޷�
																								  if(Encoder_PWM>2000){ Encoder_PWM = 2000;}
																									if(Encoder_PWM<-2000){Encoder_PWM = -2000;}
																									delay_25ms = 0;
																					 }
																				 					PWM_VALUE=Angle_PWM-Encoder_PWM;        //===����������PWM
																					 //=== �����յ�PWM�޷�
																						if(PWM_VALUE>XIAN_FU) PWM_VALUE = XIAN_FU;
																						if(PWM_VALUE< -XIAN_FU) PWM_VALUE = -XIAN_FU;

																
																						motor_pwm(PWM_VALUE);
																						// ===  �����ڵ���
																						if((Angle>=(ZHONGZHI-1))&&(Angle<=(ZHONGZHI+1)))
																						{
																												motor_stop();
																						}
															}
											         /********************����165����***********************/
																if(FUNCTION_1 == 0)
																{
																							if((Angle>(ZHONGZHI+15))||(Angle<(ZHONGZHI-15)))
																							{
																													motor_stop();
																							}
																}		
																if(FUNCTION_1 == 1)
																{	
																					//====   �ҵı�����������������������
																	         //==== �Ƕȴ��� ֻҪ���� �������Ǹ���ĽǶ� ���ҷֱ�Ϊ  һ�߼�  һ�߼����� ����ڷ�Χ��
																								if((Angle>0 )&&(Angle<ZHONGZHI-QB_STOP_ANG))
																								{
																										 Angle += 360;
																								}
																			/******************************  ��ڹ���*********************************/					
																								if((Angle > (ZHONGZHI-QB_STOP_ANG))&&(Angle<(ZHONGZHI+QB_STOP_ANG)))
																									{
																															if(QB_FLAG == 0)
																															{
																																	 TIM4->CNT =Position_Zero;	
																																	 QB_FLAG = 1;
																															}
																									}else
																									{
																															  QB_FLAG = 0;
																																Encoder_PWM = 0;
																																Angle_PWM = 0;
																																PWM_VALUE = 0;
																															if(LAST_Angle>Angle)
																															{
																																					motor_Anticlockwise(1800);         
																															}
																															else
																															{
																																					 motor_Clockwise(1800);	
																															} 
																									}
																									
																		}
					 
	

		}
}
		

