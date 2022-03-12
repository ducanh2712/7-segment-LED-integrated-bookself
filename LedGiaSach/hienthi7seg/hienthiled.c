#include <REGX52.H>
#include"main.h"
#include"..\lib\I2C.h"
#include"..\lib\RTC_DS3231.h"
#include "..\lib\delay.h"
#include "..\lib\LCD8.h"

#define led1 P3_2
#define led2 P1
#define led3 P0	
#define led4 P2
#define caidat P3_5
#define tang P3_6
#define giam P3_7

unsigned char gio,phut,giay;
char so[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

void hienThi(){
	bit am_pm;
	unsigned char chuc0,chuc1,donVi1;
	Ds3231_Read_Time(&gio,&phut,&giay,12);
	am_pm = Ds3231_Read_Time(&gio,&phut,&giay,12);
	chuc0 = gio%10;
	chuc1 = phut/10;donVi1 = phut%10;
	if(gio == 0 && am_pm == 0)
	{
		led1 = 1;
		led2 = so[2];
		led3 = so[chuc1];
		led4 = so[donVi1];	
	}
	else
	{
		led2 = so[chuc0];
		led3 = so[chuc1];
		led4 = so[donVi1];
		if(gio/10 == 1)led1 = 0;
		if(gio/10 != 1)led1 = 1;
	}
}

void SetTime(mode)
{
	if(tang == 0)
	{
		while(tang==0);
		if(mode	== 1) { gio++;if(gio>11)gio=0;}
		if(mode	== 2) { phut++;if(phut>59)phut=0;}
		Ds3231_Write_Time(gio,phut,giay,12,0);
	}
	if(giam == 0)
	{
		while(giam==0);


		if(mode	== 1 && gio != 0) { gio--;}
		else if(mode	== 2 && phut !=0) { phut--;}
		else if(mode == 1 && gio == 0) gio = 11;
		else if(mode == 2 && phut == 0) phut = 59;
		Ds3231_Write_Time(gio,phut,giay,12,0);
	}
}

void main(){
	unsigned char mode = 0;
	I2c_Init();
	Ds3231_Init();
	led1 = 0;
 //	Ds3231_Write_Time(9,07,00,12,1);

	while(1){	
	hienThi();
}	
//			if(caidat == 0) {while(caidat==0);mode=mode+1;mode=mode%3;}
//	if(mode ==1)
//		{
//			while(mode ==1)
//			{
//			//	Ds3231_Read_Time(&gio, &phut, &giay, 12);
//				for(i=0;i<10;i++){
//				if(caidat == 0) {while(caidat==0);mode=mode+1;mode=mode%3;}
//				led1=0;
//				led2=0x00;
//				SetTime(1);
//				delay(50);}
//				for(i=0;i<10;i++){
//				if(caidat == 0) {while(caidat==0);mode=mode+1;mode=mode%3;}
//				hienThi();
//				SetTime(1);
//				delay(50);}
//			}	
//		}
//		else if(mode ==2)
//		{
//			while(mode ==2)
//			{
//				for(i=0;i<10;i++){
//			//	Ds3231_Read_Time(&gio, &phut, &giay, 12);
//				if(caidat == 0) {while(caidat==0);mode=mode+1;mode=mode%3;}
//				led3=0x00;
//				led4=0x00;
//				delay(50);}
//				for(i=0;i<10;i++){
//				if(caidat == 0) {while(caidat==0);mode=mode+1;mode=mode%3;}
//				hienThi();
//				SetTime(2);
//				delay(50);}
//			}	
//		}	
//		else
//		{
//		//	Ds3231_Read_Time(&gio, &phut, &giay, 12);
//			if(caidat == 0) {while(caidat==0);mode=mode+1;mode=mode%3;}
//			hienThi();
//		}
	}
//}