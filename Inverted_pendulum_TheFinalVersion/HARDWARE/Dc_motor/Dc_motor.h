#ifndef __Dc_motor_H
#define __Dc_motor_H	 
#include "sys.h"
/***********************************
*L298N    ֱ�����
*  EN   PWM    speed 
*		L_EN  PB0     E_EN   PB1
*   IN1  PB12      IN2    PB13         ����  LEFT
*   IN3  PB14      IN4      PB15       ����  RIGHT
************************************/


//  Left     IN1   IN2
#define  L_IN_1     PBout(14)
#define  L_IN_2     PBout(15)

//  Right     IN1   IN2
#define  R_IN_1     PBout(12)
#define  R_IN_2     PBout(13)


void Dc_motor_Init(void) ;//IO��ʼ��



/******************Left    motor******************/
void L_motor_forward(void)	;   //   ˳ʱ��
void L_motor_backward(void);	   //   ��ʱ��


/******************Right   motor******************/
void R_motor_forward(void)	 ;  //   ˳ʱ��
void R_motor_backward(void)	 ;  //   ��ʱ��

#endif
