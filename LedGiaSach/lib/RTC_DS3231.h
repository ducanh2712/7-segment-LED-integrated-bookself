#ifndef	_RTC_DS3231_
#define _RTC_DS3231_

void Ds3231_Init();

// Write a byte into address
void Ds3231_Write(unsigned char add, unsigned char dat);

// Read a byte at address
unsigned char Ds3231_Read(unsigned char add);

// Read a Hour, Minute, Second in Decimal format
// Read mode 12/24
// return AM/PM (0 - AM, 1 - PM) 
bit Ds3231_Read_Time(unsigned char * hour, unsigned char * minute, 
	unsigned char * second, unsigned char * mode);

// Write Hour, Minute, Second in Decimal format
// Write Mode 12/24
// Write AM/PM (0 - AM, 1 - PM) 
void Ds3231_Write_Time(unsigned char hour, unsigned minute, 
	unsigned char second, unsigned char mode, bit apm);

// Read day, date, month, year from Ds3231
void Ds3231_Read_Date(unsigned char * day, unsigned char * date, 
	unsigned char * month, unsigned char * year);

// Write day, date, month, year into Ds3231
void Ds3231_Write_Date(unsigned char day, unsigned char date, 
	unsigned char month, unsigned char year);

// Write array of byte begin at address
void Ds3231_Write_Bytes(unsigned char add, unsigned char * buff,
	unsigned char len);

// Read array of byte into buff at add
void Ds3231_Read_Bytes(unsigned char add,unsigned char * buff,
	unsigned char len);

#endif