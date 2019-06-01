#include "reg52.h"
#include "intrins.h"

//晶振频率=12MHZ
//时钟周期=晶振周期=1/12MHZ
//1个机器周期=12个时钟周期 = 1/1MHZ= 1us
//1个指令周期=若干个机器周期 
sbit beep = P1^5;


int i=0;
//  无源蜂鸣器需要IO口输出一个频率，通过三极管放大驱动电流 
//	蜂鸣器的理论频率范围是1.5~2.5kHZ
//  换算是400~666us
//  也就是说 i理论取值是40~66
void delay(unsigned char i){	
while(i--);						//一次循环大约10个机器周期=10us=0.01ms
}

void main(){

	
	 
	while(1){
		beep=~beep;
		//实际i可以	取值 4~300
		delay(50);
		
		
	}
}