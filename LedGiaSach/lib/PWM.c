#include <REGX52.H>
#include "PWM.h"
#include "port.h"

int T,Ton,Toff;
char Ton_h_reload,Ton_l_reload,Toff_h_reload,Toff_l_reload; 

void PWM_Init (int ck)	//Khoi tao voi khoang tgian cua 1 lan dem xung nhip
{
	PWM_PIN = 1;

	TMOD &= 0xF0;	//Xoa di cac bit chon mode cua Timer0
	TMOD |= 0x01;	//Timer0 hoat dong o mode1

	ET0 = 1;		//Cho phep ngat Timer0
	EA = 1;			//Cho phep ngat toan cuc

	T = ck;
	Ton = T/2;
	Toff = T - Ton;

	Ton_h_reload = (65536 - Ton)>>8;
	Ton_l_reload = (65536 - Ton) &0x00FF;

	Toff_h_reload = (65536 - Toff)>>8;
	Toff_l_reload = (65536 - Toff) &0x00FF;

	TH0 = Ton_h_reload;
	TL0 = Ton_l_reload;
}

void PWM_Start ()
{
	TR0 = 1;		//Timer0 bat dau dem
}

void PWM_End ()
{
	TR0 = 0;		//Timer0 ngung dem
}

//duty; 0 den 100
void PWM_Set_Duty (char duty)	//%Ton va %Toff
{
	if(duty == 0)
	{
		PWM_PIN = 0;
		ET0 = 0;
	}
	else if(duty == 100)
	{
	 	PWM_PIN = 1;
		ET0 = 0;
	}
	else
	{
		Ton = ((unsigned long)T)*duty/100;
		Toff = T - Ton;
	
		Ton_h_reload = (65536 - Ton)>>8;
		Ton_l_reload = (65536 - Ton) &0x00FF;
	
		Toff_h_reload = (65536 - Toff)>>8;
		Toff_l_reload = (65536 - Toff) &0x00FF;

		ET0 = 1;
	}
}

	void TimerOverflow() interrupt 1
	{
	PWM_PIN = !PWM_PIN;
	if(PWM_PIN == 0)
	{
		TH0 = Toff_h_reload;
		TL0 = Toff_l_reload;
	}
	else
	{
		TH0 = Ton_h_reload;
		TL0 = Ton_l_reload;
	}
}	