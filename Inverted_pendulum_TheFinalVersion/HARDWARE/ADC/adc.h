#ifndef __ADC_H
#define __ADC_H	
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//ADC ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/7 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved					   
//////////////////////////////////////////////////////////////////////////////////	 
#define ADC_COLLECT_TIMES 		50								  
#define REF_Voltage           3.27
#define ANGLE_REF 						2.14    // �ڸ���Ȼ״̬�µĻ�׼��ѹ
#define ANGLE_GRA 						0.00464 // ��ѹ��Ƕȶ�Ӧ��С�̶�
/*
#define ADC_CH0  0 //ͨ��0
#define ADC_CH1  1 //ͨ��1
#define ADC_CH2  2 //ͨ��2
#define ADC_CH3  3 //ͨ��3	   
*/

void Adc_Init(void);
u16  Get_Adc(u8 ch);  
int Angle_Get(void);
int ZHONG_ZHI_GET(void);


#endif 
