/**************************************************************************************
*		              交通灯实验												  *
实现现象：下载程序后，按照视频操作正确接线，呈现交通灯现象
注意事项：																				  
***************************************************************************************/

#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

//--定义使用的IO口--//
#define GPIO_DIG   P0

#define GPIO_TRAFFIC P1

sbit RED10   = P1^0;   //上人行道红灯
sbit GREEN10 = P1^1;   //上人行道绿灯
sbit RED11   = P1^2;
sbit YELLOW11= P1^3;
sbit GREEN11 = P1^4;

sbit RED00   = P3^0;	//右人行道红灯
sbit GREEN00 = P3^1;	//右人行道绿灯
sbit RED01   = P1^5;
sbit YELLOW01= P1^6;
sbit GREEN01 = P1^7;

u8 code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值

u8 DisplayData[8];
u8 Second;

/*******************************************************************************
* 函 数 名         : delay
* 函数功能		   : 延时函数，i=1时，大约延时10us
*******************************************************************************/
void delay(u16 i)
{
	while(i--);	
}

/*******************************************************************************
* 函 数 名         : DigDisplay
* 函数功能		   : 数码管动态扫描函数，循环扫描8个数码管显示
*******************************************************************************/
void DigDisplay()
{
	u8 i;
	for(i=0;i<8;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
			case(1):
				LSA=1;LSB=0;LSC=0; break;//显示第1位
			case(2):
				LSA=0;LSB=1;LSC=0; break;//显示第2位
			case(3):
				LSA=1;LSB=1;LSC=0; break;//显示第3位
			case(4):
				LSA=0;LSB=0;LSC=1; break;//显示第4位
			case(5):
				LSA=1;LSB=0;LSC=1; break;//显示第5位
			case(6):
				LSA=0;LSB=1;LSC=1; break;//显示第6位
			case(7):
				LSA=1;LSB=1;LSC=1; break;//显示第7位	
		}
		GPIO_DIG=DisplayData[i];//发送段码
		delay(100); //间隔一段时间扫描	
		GPIO_DIG=0x00;//消隐
	}
}


/*******************************************************************************
* 函 数 名         : Timer0Init
* 函数功能		   : 定时器0初始化
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void Timer0Init()
{
	TMOD|=0X01;//选择为定时器0模式，工作方式1，仅用TR0打开启动。

	TH0=0XFC;	//给定时器赋初值，定时1ms
	TL0=0X18;	
	ET0=1;//打开定时器0中断允许
	EA=1;//打开总中断
	TR0=1;//打开定时器			
}

/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
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

		//--宝田路通行，30秒--//
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

			//--宝田路通行--//

			GPIO_TRAFFIC = 0xFF;  //将所有的灯熄灭
			RED00 = 1;
			GREEN00 = 1;

			GREEN11 = 0;    //宝田路绿灯亮			
			GREEN10	= 0;    //宝田路人行道绿灯亮

			RED01 = 0;      //前进路红灯亮
			RED00 = 0;      //前进路人行道红灯亮
		}

		//--黄灯等待切换状态，5秒--//
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

			//--黄灯阶段--//

			GPIO_TRAFFIC = 0xFF;  //将所有的灯熄灭
			RED00 = 1;
			GREEN00 = 1;

			YELLOW11 = 0;    //宝田路黄灯亮			
			RED10	= 0;     //宝田路人行道红灯亮

			YELLOW01 = 0;    //前进路红灯亮
			RED00 = 0;       //前进路人行道红灯亮
		}

		//--前进路通行--//
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

			//--黄灯阶段--//

			GPIO_TRAFFIC = 0xFF;  //将所有的灯熄灭
			RED00 = 1;
			GREEN00 = 1;

			RED11 = 0;       //宝田路红灯亮			
			RED10 = 0;       //宝田路人行道红灯亮

			GREEN01 = 0;     //前进路绿灯亮
			GREEN00 = 0;     //前进路人行道绿灯亮
		}

		//--黄灯等待切换状态，5秒--//
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

			//--黄灯阶段--//

			GPIO_TRAFFIC = 0xFF;  //将所有的灯熄灭
			RED00 = 1;
			GREEN00 = 1;

			YELLOW11 = 0;    //宝田路黄灯亮			
			RED10	= 0;     //宝田路人行道红灯亮

			YELLOW01 = 0;    //前进路红灯亮
			RED00 = 0;       //前进路人行道红灯亮
		}
	}					
}


/*******************************************************************************
* 函 数 名         : void Timer0() interrupt 1
* 函数功能		   : 定时器0中断函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void Timer0() interrupt 1
{
	static u16 i;
	TH0=0XFC;	//给定时器赋初值，定时1ms
	TL0=0X18;
	i++;
	if(i==1000)
	{
		i=0;
		Second ++;	
	}	
}
