#ifndef _motor_H
#define _motor_H
#include "stm32f10x.h"

	
void motor_Anticlockwise(float right_duty);     //�����ʱ��ת
void motor_Clockwise(float contray_duty); 			//���˳ʱ��ת
void motor_stop(void);                //���ֹͣ
void Motor_BSP_Init(void);   
void motor_pwm(float duty);//���ת

#endif
