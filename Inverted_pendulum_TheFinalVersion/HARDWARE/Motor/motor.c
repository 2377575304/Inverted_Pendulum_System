#include "motor.h"

//===  �е��š�===//

/****************����  ʹ��*****************/// 0 -- 7200
void motor_Anticlockwise(float right_duty)   //====��ת
{
					TIM_SetCompare3(TIM3, right_duty);//����ռ�ձ�
					GPIO_SetBits(GPIOA,GPIO_Pin_5);
}

void motor_Clockwise(float contray_duty)    //====��ת
{
					TIM_SetCompare3(TIM3, contray_duty);
					GPIO_ResetBits(GPIOA,GPIO_Pin_5);
}

/**************��������ʹ��*****************/
void motor_pwm(float duty)     //0 -- 7200
{
					if(duty>=0)
					{
							GPIO_SetBits(GPIOA,GPIO_Pin_5);//====�����ת����ʱ��
//							GPIO_SetBits(GPIOA,GPIO_Pin_4);
							TIM_SetCompare3(TIM3, duty);
					}
					else
					{
//					  	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
							GPIO_ResetBits(GPIOA,GPIO_Pin_5);//====�����ת��˳ʱ��
							TIM_SetCompare3(TIM3, (0-duty));
					}
	
}

void motor_stop(void)    //���ֹͣ
{
					TIM_SetCompare3(TIM3, 0);
}


void Motor_BSP_Init(void)  // �̵�����  ����
{
					GPIO_InitTypeDef GPIO_InitStructure;
						
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
						
					GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 
					GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
					GPIO_Init(GPIOA, &GPIO_InitStructure);
					
//					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
//					GPIO_Init(GPIOA, &GPIO_InitStructure);
//					
//					GPIO_SetBits(GPIOB,GPIO_Pin_1);//�̵�����ʼ������
}
