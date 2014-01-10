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
#include <a1018lcd_CharTable.h>

unsigned char cursor_poz=0;

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
I2C_Stop();

return 0;
}
char writechar(char charachter){

    char command = 0b00000001,i;

    //every char start whit 0
    SW_I2C_Start(device_address);
    SW_I2C_Write(command); //command
    SW_I2C_Write(cursor_poz); // X address
    SW_I2C_Write(0x00);


    for(i=0;i<6;i++)
    {

    	SW_I2C_Write(chartable[((unsigned)(charachter-65)*6)+i]); // display data
    }


    SW_I2C_Write(0x00);
    I2C_Stop();

    cursor_poz+=8;
    return 0;
}
