#include <reg52.h>
typedef unsigned int uint;
typedef unsigned char uchar;

sbit RS=P3^5;
sbit RW=P3^6;
sbit EN=P3^4;
//whether lcd is busy,busy wait
void Read_Busy(){
	uchar busy;
	P0=0xff;
	RS=0;
	RW=1;
	do{
		EN=1;
		busy=P0;
		EN=0;
	}while(busy & 0x80);
}
//write command
void Write_Cmd(uchar cmd){
	//busy or not
	Read_Busy();
	RS=0;
	RW=0;
	P0=cmd;
	EN=1;
	EN=0;
}
//write a byte
void Write_Data(uchar dat){
	Read_Busy();
	RS=1;
	RW=0;
	P0=dat;
	EN=1;
	EN=0;
}
//write a string
void max(uchar a,uchar b,uchar *max){
	*max=(a>b)?a:b;
}
//main
void main(){
	//settings
	uchar a;
	uchar *pa;
	uchar **ppa;
	Write_Cmd(0x38);
	Write_Cmd(0x0f);

	//Write_Cmd(0x80);
	Write_Cmd(0x01);
	Write_Cmd(0x05);
	//
	Write_Cmd(0x84);
	//Write_Data(1+'0');
	//Write_Data(2+'0');
	//Write_Data(3+'0');

	Write_Cmd(0xc4);
	//pa=&a;
	//*pa=8;//a=8
	//max(3,6,&a);
	pa=&a;
	ppa=&pa;
	a=5;
	Write_Data(a+'0');
	Write_Data(*pa+'0');
	Write_Data(**ppa+'0');
	//Write_Data('b');
	//Write_Data('c');

	while(1);
}