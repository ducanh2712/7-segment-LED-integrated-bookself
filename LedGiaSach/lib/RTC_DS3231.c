#include"main.h"
#include"..\lib\I2C.h"
#include"RTC_DS3231.h"
#include "..\lib\delay.h"

void Ds3231_Init() //Khoi tao DS3231
{
 	unsigned char tmp;
	tmp = Ds3231_Read(0x00);
	tmp &= 0x7F;
	Ds3231_Write(0x00,tmp);		
}

void Ds3231_Write(unsigned char add, unsigned char dat) //Truyen du lieu vao DS3231 tu Master
{
	I2c_Start();
	I2c_Write(0xD0);
	I2c_Write(add); 
	I2c_Write(dat); 
	I2c_Stop();
}

unsigned char Ds3231_Read(unsigned char add) // Master doc du lieu tu DS3231
{
	unsigned char dat;
	I2c_Start();
	I2c_Write(0xD0); 
	I2c_Write(add);
	I2c_Start(); 
	I2c_Write(0xD1); 
	dat = I2c_Read(0);
	I2c_Stop();
	return dat;
}

bit Ds3231_Read_Time(unsigned char * hour, unsigned char * minute, // Doc gio/phut/giay tu DS3231 cho Master
	unsigned char * second, unsigned char * mode)
{
	unsigned char h_tmp, m_tmp, s_tmp;
	bit am_pm;
	I2c_Start();
	I2c_Write(0xD0); 
	I2c_Write(0x00);
	I2c_Start(); 
	I2c_Write(0xD1); 
	s_tmp = I2c_Read(1);
	m_tmp = I2c_Read(1);
	h_tmp = I2c_Read(0);
	I2c_Stop();

	s_tmp &= 0x7F;
	*second = (s_tmp>>4)*10+(s_tmp&0x0F);
	m_tmp &= 0x7F;
	*minute = (m_tmp>>4)*10+(m_tmp&0x0F);

	if(h_tmp & 0x40) 		// Mode 12h
	{
		*mode = 12;
		if(h_tmp & 0x20)
		{
		 	am_pm = 1;		// PM
		}
		else
		{
		 	am_pm = 0;
		}
		h_tmp &= 0x1F;
	 	*hour = (h_tmp>>4)*10+(h_tmp&0x0F);
	}
	else
	{
		*mode = 24;
		h_tmp &= 0x3F;
	 	*hour = (h_tmp>>4)*10+(h_tmp&0x0F);
		if(*hour<12)
		{
		 	am_pm = 0;		// AM
		}
		else
		{
		 	am_pm = 1;
		}
	}	
	return am_pm;
}

void Ds3231_Write_Time(unsigned char hour, unsigned minute,  // Chinh gio/phut/giay cho DS3231 tu Master
	unsigned char second, unsigned char mode, bit apm)
{
	second = ((second/10)<<4)|(second%10);
	minute = ((minute/10)<<4)|(minute%10);
	hour   = ((hour  /10)<<4)|(hour  %10);
	if(mode==12)
	{
		hour |= 0x40;
		if(apm)		// PM
		{
			hour |= 0x20;
		}
	}
	I2c_Start();
	I2c_Write(0xD0);
	I2c_Write(0x00); 
	I2c_Write(second); 
	I2c_Write(minute);
	I2c_Write(hour);
	I2c_Stop();
}

//void Ds3231_Read_Date(unsigned char * day, unsigned char * date, // Doc ngay/thang/nam tu DS3231 cho Master
//	unsigned char * month, unsigned char * year)
//{
//	I2c_Start();
//	I2c_Write(0xD0); 
//	I2c_Write(0x03);
//	I2c_Start(); 
//	I2c_Write(0xD1); 
//	*day  = I2c_Read(1);
//	*date = I2c_Read(1);
//	*month= I2c_Read(1);
//	*year = I2c_Read(0);
//	I2c_Stop();
//	*day &= 0x07;
//	*date &= 0x3F;
//	*date = (*date>>4)*10 + (*date & 0x0F);
//	*month &= 0x1F;
//	*month = (*month>>4)*10 + (*month & 0x0F);
//	*year = (*year>>4)*10 + (*year & 0x0F);	
//}
//
//void Ds3231_Write_Date(unsigned char day, unsigned char date, // Chinh ngay/thang/nam cho DS3231 tu Master
//	unsigned char month, unsigned char year)
//{
//	date 	= ((date/10)<<4)  | (date%10);
//	month 	= ((month/10)<<4) | (month%10);
//	year	= ((year/10)<<4)  | (year%10);
//
//	I2c_Start();
//	I2c_Write(0xD0);
//	I2c_Write(0x03); 
//	I2c_Write(day); 
//	I2c_Write(date);
//	I2c_Write(month);
//	I2c_Write(year);
//	I2c_Stop();
//}

void Ds3231_Write_Bytes(unsigned char add, unsigned char * buff, // Gui 1byte cho DS3231 tu Master
	unsigned char len)
{
	unsigned char i=0;

	I2c_Start();
	I2c_Write(0xD0);
	I2c_Write(add);
	for(i=0;i<len;i++)
	{ 	 
		I2c_Write(buff[i]); 
	} 
	I2c_Stop();
}

void Ds3231_Read_Bytes(unsigned char add,unsigned char * buff, //Doc 1byte tu DS3231 cho Master
	unsigned char len)
{
 	unsigned char i;

	I2c_Start();
	I2c_Write(0xD0); 
	I2c_Write(add);
	I2c_Start();
	I2c_Write(0xD1);
	for(i=0;i<len-1;i++)
	{ 
		buff[i]  = I2c_Read(1);
	}
	buff[i]  = I2c_Read(0);
	I2c_Stop();
}