#include "stm32f10x.h"
#include "string.h"
#include "delay.h"
#include "usart.h"	
#include "sys.h"
#include "timer.h"
#include "key.h"
#include "motor.h"
#include "adc.h"
#include "encoder.h"
#include "PID.h"
#include "pwm.h"
#include "usart.h"
#include "usmart.h"
/*****************************
anthor: Che_hongshu
***********************/
int KEY_MODE;//====   ������־
int FUNCTION_1;//===  ����
int KEY_RESET; //===  ��λ
extern int   Draw_circle_FLAG;  //=== ��Ȧ   ˳ʱ��
extern int 	 Draw_circle_FLAG_opposite;// ��Բ   ��ʱ��
extern int   ZHONGZHI;//=== ��ֵ�� ������ֵ
extern int   Angle;
extern int   Position_Zero;

int main()
{
/*****************��ʼ����*************************/

			int key;


			delay_init();                        //==== ��ʱ��ʼ��
	    uart_init(9600);					        //==== ���ڳ�ʼ��
		  usmart_dev.init(72);           //===    ��Ƭ��   ����Ƶ  72M    USMART ������
			Adc_Init();													//====  ADC��ʼ��
			TIM3_PWM_Init(7200-1,0);						//====Timer3��PWM��ʼ�� arr=7200   fenpin = 0   10KHZ �� PWM   
		  Motor_BSP_Init();              //====  ֱ�������ʼ��
			Timer5_Init(49,7199);			  //====Timer5��ʼ��,1Khz�ļ���Ƶ��,������5ms 
			TIM4_Init();												//==== �������ĳ�ʼ��
			Set_PID_Angle(0,0);  
	    Set_PID_Location(0,0);
      KEY_Init();													//====  ������ʼ��
	
			while(1)
			{
									
				
							//**********   key****************/
   								 key = KEY_Scan(1);		
									 switch(key)
										{	
											
																	case KEY1_PRES:
																		
																	      ZHONGZHI  = Angle;			//=== ��ֵ �����趨  ��  �������  �Ƕȴ�������ֵ
																						break;
																	case KEY2_PRES:
																				
																	       KEY_MODE = 1;     			//===���ڹ���
																						break;
																	case KEY3_PRES:				
																        Draw_circle_FLAG = 1;		//=== תȦ���ܣ����Ա��ֲ����£� ���о�λ�û���target
																						break;
																	case KEY4_PRES:
																		    Draw_circle_FLAG_opposite  = 1;	   //=== תȦ���ܣ����Ա��ֲ����£� ���о�λ�û���target
																				   break;
																	case KEY5_PRES:
																							KEY_RESET = 1;
																	         break;
																		  
										}
													 if(KEY_MODE == 1)
													 {
																				FUNCTION_1 = 1;
													 }	
													 if(KEY_RESET == 1)
													 {
																			Draw_circle_FLAG = 0;
														          Draw_circle_FLAG_opposite = 0;
																			FUNCTION_1 = 0;
																			KEY_MODE   = 0;
														 
																			KEY_RESET  = 0;
													 }
											

			}
}	
