#include <REGX52.H>
#include "port.h"
#include "../libTT/DHT11.h"

void delay20ms()		//delay 20ms
{
	TMOD = 0x01;		
	TH0 = 0xB8;				
	TL0 = 0x0C;				
	TR0 = 1;				
	while(TF0 == 0);	    
	TR0 = 0;				
	TF0 = 0;			
}
void delay30us()	// delay 30us
{
	TMOD = 0x01;			
	TH0 = 0xFF;			
	TL0 = 0xF1;				
	TR0 = 1;			
	while(TF0 == 0);	   
	TR0 = 0;			
	TF0 = 0;				
}

void Request()		// Gui tin hieu yeu cau DHT11 doc gia tri do am nhit do
{
	DHT11 = 0;	
	delay20ms();	
	DHT11 = 1;		
}

void Response()		// Doi DHT11 phan hoi
{
	while(DHT11==1);
	while(DHT11==0);
	while(DHT11==1);
}

int Receive_data()	// 	Nhan du lieu tu DHT11
{
	int q,c=0;	
	for (q=0; q<8; q++)
	{
		while(DHT11==0);
		delay30us();;
		if(DHT11 == 1)	
		c = (c<<1)|(0x01);
		else	
		c = (c<<1);
		while(DHT11==1);
	}
	return c;
}
