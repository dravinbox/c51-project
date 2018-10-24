#include "reg52.h"
#include "intrins.h"

#define led P0
#define selector P2

typedef unsigned char u8;

u8 nres[8];

void delay(int i){while(i--);}

  /*
   //����Ϊʲô���λ����2�أ�
   //��Ϊ���Խ�38��������ʱ��ʹ�õ���P2^2,P2^3,P2^4 
   //������Ҫ����2λ��P2�ܽŵ�������ܶԵ���38������
   */
void display(u8 *num,int pos){
   unsigned char a=0x00;
   a=a+pos;
   selector=a<<2;
 
   led=num[pos];

}


//��ʾ�����������
void dynamicLED(u8 *nr){
		u8 x=0x00;		
		for(x=0;x<8;x++){
			
			display(nr,x);
			delay(250); //��ʱ 2500us = 2.5 ms ��ʾ����
		
		
		}
}

//������ת��Ϊ����ܱ���
u8 getLEDCodeByNum(int num){
   u8 n[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
   if(num<0||num>9){
   		return 0x40;  //����������֣��򷵻�-�ı���
   }else{
   		return 	n[num];
   }

}

//�����ֵ�����  ת��Ϊ  ����ܱ��������
u8* changeNumArr2LedCodeArr(int *num){
		
		int i;
		for(i=0;i<8;i++){
		   nres[i]=getLEDCodeByNum(*(num+i));
		}
		return nres;

}
void main(){
	while(1){
		//u8 ne[8]={0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f};
		//dynamicLED(ne);

		int num[8]={7,9,-1,5,5,-1,3,2};
		u8 *np=changeNumArr2LedCodeArr(num);
		dynamicLED(np);
		

		
		
	}
	
}