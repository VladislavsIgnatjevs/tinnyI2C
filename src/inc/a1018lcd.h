/*
 * a1018lcd.h
 *
 *  Created on: 2014.01.09.
 *      Author: zoon
 */

#ifndef A1018LCD_H_
#define A1018LCD_H_
#endif /* A1018LCD_H_ */

#include <swi2c.h>

char clearscreen(unsigned char data){

char j,i;
char command = 0b00000001;

for(j=0;j<5;j++){
	SW_I2C_Start(device_address);
    SW_I2C_Write(command);
    SW_I2C_Write(0); // X address auto increment
    SW_I2C_Write(data);
    for(i=0;i<100;i++)
    {

    	SW_I2C_Write(data); // display data
    }
command+=32;
}
i2c_stop();

return 0;
}
