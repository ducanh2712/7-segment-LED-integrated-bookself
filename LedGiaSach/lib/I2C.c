#include"main.h"
#include"I2c.h"
#include "..\lib\delay.h"
#define I2C_SCL P3_3
#define I2C_SDA P3_4

bit I2c_Get_Ack();
void I2c_Ack();
void I2c_Nak();

void I2c_Init() //Khoi tao I2C
{
 	I2C_SCL=1;
	I2C_SDA=1;
}

void I2c_Start() //Bat dau I2C
{
	I2C_SCL = 1;
	
	I2C_SDA = 0;
	
	I2C_SCL = 0;
}

bit I2c_Get_Ack() //Master nhan 
{
	bit result;
    I2C_SDA = 1;
	
    I2C_SCL = 1;
	
	result = I2C_SDA;
    I2C_SCL = 0;
	return result;
}

bit I2c_Write(unsigned char dat) //Gui du lieu tu Master
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
	    I2C_SDA = (bit)(dat&0x80);	
	    I2C_SCL = 1;
		
		I2C_SCL = 0;
	    dat<<=1;
	}
	return(I2c_Get_Ack());
}

void I2c_Ack() //Bao Ack tu Master
{
	I2C_SDA = 0;
	
	I2C_SCL = 1;
	
    I2C_SCL = 0;
}

void I2c_Nak() //Bao NAck tu Master
{
    I2C_SDA = 1;
	
    I2C_SCL = 1;
	
    I2C_SCL = 0;
}

unsigned char I2c_Read(bit ack) //Doc du lieu tu Master
{
    unsigned char i, dat=0;
    for(i=0;i<8;i++)
	{
	    I2C_SDA = 1;
		
	    I2C_SCL = 1;
		
	    dat <<= 1;
		if(I2C_SDA)
		{
		 	dat |= 0x01;
		}
		I2C_SCL = 0;
    }
	if(ack)
	{
	 	I2c_Ack();
	}
	else
	{
	 	I2c_Nak();
	}
    return dat;
}

void I2c_Stop() // Dung I2C
{ 	
	I2C_SDA = 0;
	
	I2C_SCL = 1;
	
	I2C_SDA = 1;
}