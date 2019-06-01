/**************************************************************************************
*		              ��ͨ��ʵ��												  *
ʵ���������س���󣬰�����Ƶ������ȷ���ߣ����ֽ�ͨ������
ע�����																				  
***************************************************************************************/

#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���

typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

//--����ʹ�õ�IO��--//
#define GPIO_DIG   P0

#define GPIO_TRAFFIC P1

sbit RED10   = P1^0;   //�����е����
sbit GREEN10 = P1^1;   //�����е��̵�
sbit RED11   = P1^2;
sbit YELLOW11= P1^3;
sbit GREEN11 = P1^4;

sbit RED00   = P3^0;	//�����е����
sbit GREEN00 = P3^1;	//�����е��̵�
sbit RED01   = P1^5;
sbit YELLOW01= P1^6;
sbit GREEN01 = P1^7;

u8 code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//��ʾ0~F��ֵ

u8 DisplayData[8];
u8 Second;

/*******************************************************************************
* �� �� ��         : delay
* ��������		   : ��ʱ������i=1ʱ����Լ��ʱ10us
*******************************************************************************/
void delay(u16 i)
{
	while(i--);	
}

/*******************************************************************************
* �� �� ��         : DigDisplay
* ��������		   : ����ܶ�̬ɨ�躯����ѭ��ɨ��8���������ʾ
*******************************************************************************/
void DigDisplay()
{
	u8 i;
	for(i=0;i<8;i++)
	{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
			case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
			case(2):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
			case(3):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
			case(4):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
			case(5):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
			case(6):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
			case(7):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ	
		}
		GPIO_DIG=DisplayData[i];//���Ͷ���
		delay(100); //���һ��ʱ��ɨ��	
		GPIO_DIG=0x00;//����
	}
}


/*******************************************************************************
* �� �� ��         : Timer0Init
* ��������		   : ��ʱ��0��ʼ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void Timer0Init()
{
	TMOD|=0X01;//ѡ��Ϊ��ʱ��0ģʽ��������ʽ1������TR0��������

	TH0=0XFC;	//����ʱ������ֵ����ʱ1ms
	TL0=0X18;	
	ET0=1;//�򿪶�ʱ��0�ж�����
	EA=1;//�����ж�
	TR0=1;//�򿪶�ʱ��			
}

/*******************************************************************************
* �� �� ��       : main
* ��������		 : ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/
void main()
{	
	Second = 1;

	Timer0Init();

	while(1)
	{
		if(Second == 70)
		{
			Second = 1;
		}

		//--����·ͨ�У�30��--//
		if(Second < 31)
		{
			DisplayData[0] = 0x00;
			DisplayData[1] = 0x00;
			DisplayData[2] = smgduan[(30 - Second) % 100 / 10];
			DisplayData[3] = smgduan[(30 - Second) %10];
			DisplayData[4] = 0x00;
			DisplayData[5] = 0x00;
			DisplayData[6] = DisplayData[2];
			DisplayData[7] = DisplayData[3];
			DigDisplay();

			//--����·ͨ��--//

			GPIO_TRAFFIC = 0xFF;  //�����еĵ�Ϩ��
			RED00 = 1;
			GREEN00 = 1;

			GREEN11 = 0;    //����·�̵���			
			GREEN10	= 0;    //����·���е��̵���

			RED01 = 0;      //ǰ��·�����
			RED00 = 0;      //ǰ��·���е������
		}

		//--�ƵƵȴ��л�״̬��5��--//
		else if(Second < 36) 
		{
			DisplayData[0] = 0x00;
			DisplayData[1] = 0x00;
			DisplayData[2] = smgduan[(35 - Second) % 100 / 10];
			DisplayData[3] = smgduan[(35 - Second) %10];
			DisplayData[4] = 0x00;
			DisplayData[5] = 0x00;
			DisplayData[6] = DisplayData[2];
			DisplayData[7] = DisplayData[3];
			DigDisplay();

			//--�Ƶƽ׶�--//

			GPIO_TRAFFIC = 0xFF;  //�����еĵ�Ϩ��
			RED00 = 1;
			GREEN00 = 1;

			YELLOW11 = 0;    //����·�Ƶ���			
			RED10	= 0;     //����·���е������

			YELLOW01 = 0;    //ǰ��·�����
			RED00 = 0;       //ǰ��·���е������
		}

		//--ǰ��·ͨ��--//
		else if(Second < 66) 
		{
			DisplayData[0] = 0x00;
			DisplayData[1] = 0x00;
			DisplayData[2] = smgduan[(65 - Second) % 100 / 10];
			DisplayData[3] = smgduan[(65 - Second) %10];
			DisplayData[4] = 0x00;
			DisplayData[5] = 0x00;
			DisplayData[6] = DisplayData[2];
			DisplayData[7] = DisplayData[3];
			DigDisplay();

			//--�Ƶƽ׶�--//

			GPIO_TRAFFIC = 0xFF;  //�����еĵ�Ϩ��
			RED00 = 1;
			GREEN00 = 1;

			RED11 = 0;       //����·�����			
			RED10 = 0;       //����·���е������

			GREEN01 = 0;     //ǰ��·�̵���
			GREEN00 = 0;     //ǰ��·���е��̵���
		}

		//--�ƵƵȴ��л�״̬��5��--//
		else 
		{
			DisplayData[0] = 0x00;
			DisplayData[1] = 0x00;
			DisplayData[2] = smgduan[(70 - Second) % 100 / 10];
			DisplayData[3] = smgduan[(70 - Second) %10];
			DisplayData[4] = 0x00;
			DisplayData[5] = 0x00;
			DisplayData[6] = DisplayData[2];
			DisplayData[7] = DisplayData[3];
			DigDisplay();

			//--�Ƶƽ׶�--//

			GPIO_TRAFFIC = 0xFF;  //�����еĵ�Ϩ��
			RED00 = 1;
			GREEN00 = 1;

			YELLOW11 = 0;    //����·�Ƶ���			
			RED10	= 0;     //����·���е������

			YELLOW01 = 0;    //ǰ��·�����
			RED00 = 0;       //ǰ��·���е������
		}
	}					
}


/*******************************************************************************
* �� �� ��         : void Timer0() interrupt 1
* ��������		   : ��ʱ��0�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void Timer0() interrupt 1
{
	static u16 i;
	TH0=0XFC;	//����ʱ������ֵ����ʱ1ms
	TL0=0X18;
	i++;
	if(i==1000)
	{
		i=0;
		Second ++;	
	}	
}
