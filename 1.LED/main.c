#include "reg52.h"
#include "intrins.h"

#define led P0

int i=0;

void delay1s(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}

//hello world
void main(){

	//led=0x01;
		
    unsigned char a=0x01;
	unsigned char b=0x00;
	 led=a;
	 
	while(1){
		delay1s();
		i++;
		a=a<<1;
		a=a+1;
		if(i==8){
		  	a=0x01;
			i=0;
		}
		led=a;
		
		
	}
}
