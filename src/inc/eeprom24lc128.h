/*
 * eeprom24lc128.h
 *
 *  Created on: 2014.01.15.
 *      Author: zoon
 */
#include<swi2c.h>
void eeprom_writebyte(unsigned short int address,char data)
{
SW_I2C_Start(eeprom_address_W);
SW_I2C_Write(address>>8);
SW_I2C_Write(address);
SW_I2C_Write(data);
I2C_Stop();
}
//WIP
