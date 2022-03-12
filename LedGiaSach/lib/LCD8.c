#include <REGX52.H>
#include "port.h"
#include"..\libTT\delay.h"
#include"..\libTT\LCD8.h"

unsigned char Change_Bit( unsigned char n)
{
	unsigned char tmp=0x00;
	int i;
	for(i=0;i<8;i++)
	{
		if ( (n & 0x01) == 1)
			{
				tmp = tmp <<1 | 0x01;
				n = n >>1;
			}	
		else
			{
				tmp = tmp <<1 | 0x00;
				n = n >>1;
			}
		}
	return tmp;
}

void Lcd_Cmd(unsigned char cmd) //Gui lenh LCD
{
	LCD_RS = 0;
	LCD_DATA = Change_Bit(cmd);
	LCD_EN = 0;
	LCD_EN = 1;

	if(cmd<=0x02)
	{
	 	delay(2);
	}
	else
	{
	 	delay(1);
	}
}

void Lcd_Chr_Cp(char c)		// Xuat ra man hinh LCD ki tu tai vi tri con tro
{
 	LCD_RS = 1;
	LCD_DATA = Change_Bit(c);
	LCD_EN = 0;
	LCD_EN = 1;
	delay(1);
}


void Lcd_Chr(unsigned char row, unsigned char col, char c) // Xuat ra man hinh LCD 1 ky tu, ngay tai vi tri dong row, cot col
{
	unsigned char cmd;

	// Di chuyen co tro den vi tri can thiet
	cmd = (row==1?0x80:0xC0) + col - 1;
	Lcd_Cmd(cmd);

	// Xuat ky tu
	Lcd_Chr_Cp(c);
}	

void Lcd_Out_Cp(char *str) // Xuat ra man hinh LCD chuoi ki tu dai vi tri con tro
{
 	unsigned char i = 0;
	while(str[i]!=0)
	{
	 	Lcd_Chr_Cp(str[i]);
		i++;
	}
}

void Lcd_Out(unsigned char row, unsigned char col, char *str) // Xuat ra man hinh LCD chuoi ky tu, ngay tai vi tri dong row, cot col
{
 	unsigned char cmd;

	// Di chuyen co tro den vi tri can thiet
	cmd = (row==1?0x80:0xC0) + col - 1;
	Lcd_Cmd(cmd);

	Lcd_Out_Cp(str);
}

void Lcd_Init() //Khoi tao LCD 16x2 (2 dong 16 o)
{
 	Lcd_Cmd(0x30);
	delay(5);
	Lcd_Cmd(0x30);
	delay(1);
	Lcd_Cmd(0x30);

	Lcd_Cmd(0x38); 		// So dong hien thi la 2, font 5x8

	Lcd_Cmd(0x01);		// Xoa noi dung hien thi
	Lcd_Cmd(0x0C);	  	// Bat hien thi va tat con tro
}