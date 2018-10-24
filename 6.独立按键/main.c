#include "reg52.h"
#include "intrins.h"



typedef unsigned char u8;

sbit btn=P2^0;
sbit led=P0^0;

void delay(u8 i){while(i--){};}	  //10us

void checkBtn(){
	if(btn==0){
		delay(1000);
		if(btn==0){
		  led=~led;
		}
		while(!btn);
	}

}

void main(){
	while(1){
	
		checkBtn();
		
		
	}
	
}