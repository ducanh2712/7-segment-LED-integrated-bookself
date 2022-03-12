#ifndef	_I2C_H_
#define _I2C_H_

// Init
void I2c_Init();

// Master generate Start signal
void I2c_Start();

// Master generate Stop signal
void I2c_Stop();

// Write data to Slaver, and get ACK/NACK from Slaver
bit I2c_Write(unsigned char dat);

// Read data from Slaver
unsigned char I2c_Read(bit ack);
#endif