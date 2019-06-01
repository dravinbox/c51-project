#include "reg52.h"
#include "intrins.h"

//晶振频率=12MHZ
//时钟周期=晶振周期=1/12MHZ
//1个机器周期=12个时钟周期 = 1/1MHZ= 1us
//1个指令周期=若干个机器周期 
sbit relay = P1^4;


/*
void delay(unsigned char i){	
while(i--);						//一次循环大约10个机器周期=10us=0.01ms
}
*/
void delay2s(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=127;c>0;c--)
        for(b=235;b>0;b--)
            for(a=32;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}

void main(){

	
	relay=0;
	while(1){
		delay2s();
		relay=~relay;	
		
		
	}
}