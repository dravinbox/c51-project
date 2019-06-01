#include "reg52.h"
#include "intrins.h"

typedef unsigned char u8;
typedef unsigned int u16;

#define GPIO_DIG P0

sbit IN_PL=P1^6;
sbit IN_DATA=P1^7;
sbit SCK=P3^6;

u8 read74hc165(){
	u8 indata=0;
	u8 i=0;
	IN_PL=0;
	_nop_();
	IN_PL=1;
	_nop_();
	for(i=0;i<8;i++){
	   indata=indata<<1;
	   SCK=0;
	   _nop_();
	   indata|=IN_DATA;
	   SCK=1;
	}
	return indata;

}
void delay(u16 i){while(i--);}
	  

void main(){
	u8 h165Value;
	GPIO_DIG=0;
	while(1){
	   h165Value=read74hc165();
	   if(h165Value!=0xff){
	   		GPIO_DIG=~h165Value;
	   }
	
	}
	
}