#include "PID.h"

/*
				λ��ʽ PID 
*/

int Position_Zero=10000;            //���������������
float Balance_KP=340,Balance_KD=2600,Position_KP=6.5,Position_KD=320;  //PIDϵ��   350 2500 6.5 210
int ZHONGZHI;
//==== ���ڴ��ڵ���   USMART
void Set_PID_Angle(int Kp,int Kd)
{
				Balance_KP  =  Kp;

				Balance_KD  =  Kd;
}
void Set_PID_Location(int Kp,int Kd)
{
	      Position_KP  =  Kp/10.0;

				Position_KD  =  Kd/10.0;
}

/**************************************************************************
�������ܣ����PD����
��ڲ������Ƕ�
����  ֵ����ǿ���PWM
��    �ߣ�ƽ��С��֮��
**************************************************************************/
int balance(float Angle)
{  
	
			 float Bias;                       //���ƫ��
			 static float Last_Bias,D_Bias;    //PID��ر���
			 int balance;                      //PWM����ֵ 
			 Bias=Angle-ZHONGZHI;              //���ƽ��ĽǶ���ֵ �ͻ�е���
			 D_Bias=Bias-Last_Bias;            //���ƫ���΢�� ����΢�ֿ���
			 balance=-Balance_KP*Bias-D_Bias*Balance_KD;   //===������ǿ��Ƶĵ��PWM  PD����
			 Last_Bias=Bias;                   //������һ�ε�ƫ��
			 return balance;
	
}

/**************************************************************************
�������ܣ�λ��PD���� 
��ڲ�����������
����  ֵ��λ�ÿ���PWM
��    �ߣ�ƽ��С��֮��
**************************************************************************/
int Position(int Encoder)
{  
   static float Position_PWM,Last_Position,Position_Bias,Position_Differential;
	 static float Position_Least;
								Position_Least =Encoder-Position_Zero;             //===
								Position_Bias *=0.8;		   
								Position_Bias += Position_Least*0.2;	             //===һ�׵�ͨ�˲���  
	  Position_Differential=Position_Bias-Last_Position;
	  Last_Position=Position_Bias;
		Position_PWM=Position_Bias*Position_KP+Position_Differential*Position_KD; //===�ٶȿ���	
	  return Position_PWM;
}

