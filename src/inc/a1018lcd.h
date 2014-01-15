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

char clearscreen(unsigned char sor , char karakterszam ){

char j,i;
char command = 0b00000001;

for(j=0;j<sor;j++){
	SW_I2C_Start(device_address);
    SW_I2C_Write(command);
    SW_I2C_Write(0); // X address auto increment
    SW_I2C_Write(0);
    for(i=0;i<karakterszam;i++)
    {

    	SW_I2C_Write(0); // display data
    }
command+=32;
}
I2C_Stop();
cursor_poz=0;

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
void writesring(const char * string)
{
 while(*string)
	 writechar(*string++);

}
char writenumb(char charachter){

    char command = 0b00000001;
    char i;
    //every char start whit 0
    SW_I2C_Start(device_address);
    SW_I2C_Write(command); //command
    SW_I2C_Write(cursor_poz); // X address
    SW_I2C_Write(0x00);

    for(i=0;i<6;i++)
    {
    	SW_I2C_Write(numbtable[((unsigned)(charachter*6))+i]); // display data
    }

    SW_I2C_Write(0x00);
    I2C_Stop();
    cursor_poz+=8;
    return 0;
}
char write_int(int number)
{
		//hány jegyű a szám
	int oszto=1;
	char jegy_hossz=1,i;
	while((number+1) / oszto > 9 )

	    {
	    oszto=oszto*10;
	    jegy_hossz++;
	    }

 for(i=0;i<jegy_hossz;i++)
 {
	 writenumb( number/ oszto );
	 number-= number / oszto * oszto;
	 oszto=oszto/10;

 }
return 0;
}
