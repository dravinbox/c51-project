#include "reg52.h"
#include "intrins.h"

//����Ƶ��=12MHZ
//ʱ������=��������=1/12MHZ
//1����������=12��ʱ������ = 1/1MHZ= 1us
//1��ָ������=���ɸ��������� 
sbit relay = P1^4;


/*
void delay(unsigned char i){	
while(i--);						//һ��ѭ����Լ10����������=10us=0.01ms
}
*/
void delay2s(void)   //��� 0us
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