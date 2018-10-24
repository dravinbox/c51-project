#include "reg52.h"
#include "intrins.h"

typedef unsigned char u8;
typedef unsigned int u16;

#define GPIO_DIG P0
#define GPIO_KEY P1

u8 code smgduan[16]={0x3f,0x06,0x5b,0x4f,
					0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,
					0x39,0x5e,0x79,0x71};
u8 keyValue;
void delay(u16 i){while(i--);}

//这个函数能修改KeyValue的值0-15
void keyDown(){
	char a=0;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f){
		delay(1000);
		if(GPIO_KEY!=0x0f){
			 switch(GPIO_KEY){
			 	case(0x07) :keyValue=0;break;
				case(0x0b) :keyValue=1;break;
				case(0x0d) :keyValue=2;break;
				case(0x0e) :keyValue=3;break;
			 }
			 GPIO_KEY=0xf0;
			 switch(GPIO_KEY){
			 	case(0x70) :keyValue=keyValue;break;
				case(0xb0) :keyValue=keyValue+4;break;
				case(0xd0) :keyValue=keyValue+8;break;
				case(0xe0) :keyValue=keyValue+12;break;
			 }
			 while((a<50)&&(GPIO_KEY!=0xf0)){
			 	 delay(1000);
				 a++;
			 }
		}
	}
}		  

void main(){

	while(1){
	
		keyDown();	
		GPIO_DIG=~smgduan[keyValue];
	}
	
}