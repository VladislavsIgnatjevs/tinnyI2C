
#define F_CPU 1000000
#ifndef SWI2C_H_
#define SWI2C_H_
#endif /* SWI2C_H_ */

#include <avr/io.h>
#include <util/delay.h>


#define device_address 0x70

#define delay 1

#define I2C_DDR DDRB
#define I2C_PIN PINB
#define I2C_PORT PORTB

// Pins to be used in the bit banging
#define I2C_CLK 2
#define I2C_DAT 0

#define I2C_DATA_HI()\
I2C_DDR &= ~ (1 << I2C_DAT);\
I2C_PORT |= (1 << I2C_DAT);
#define I2C_DATA_LO()\
I2C_DDR |= (1 << I2C_DAT);\
I2C_PORT &= ~ (1 << I2C_DAT);

#define I2C_CLOCK_HI()\
I2C_DDR &= ~ (1 << I2C_CLK);\
I2C_PORT |= (1 << I2C_CLK);
#define I2C_CLOCK_LO()\
I2C_DDR |= (1 << I2C_CLK);\
I2C_PORT &= ~ (1 << I2C_CLK);

void I2C_WriteBit(unsigned char c)
{
    if (c > 0)
    {
        I2C_DATA_HI();
    }
    else
    {
        I2C_DATA_LO();
    }

    I2C_CLOCK_HI();
    while ((I2C_PIN & (1 << I2C_CLK)) == 0);
    _delay_us(delay);

    I2C_CLOCK_LO();
    _delay_us(delay);

    if (c > 0)
    {
        I2C_DATA_LO();
    }

    _delay_us(delay);
}

unsigned char I2C_ReadBit()
{
    I2C_DATA_HI();

    I2C_CLOCK_HI();
    _delay_us(delay);

    unsigned char c = I2C_PIN;

    I2C_CLOCK_LO();
    _delay_us(delay);

    return (c >> I2C_DAT) & 1;
}

// Inits bitbanging port, must be called before using the functions below
//
void I2C_Init()
{
    I2C_PORT |=  ((1 << I2C_DAT) | (1 << I2C_CLK));

    I2C_CLOCK_HI();
    I2C_DATA_HI();

    _delay_us(delay);
}

// Send a START Condition
//
void I2C_Start()
{
    // set both to high at the same time
    I2C_DDR &= ~ ((1 << I2C_DAT) | (1 << I2C_CLK));
    _delay_us(delay);

    I2C_DATA_LO();
    _delay_us(delay);

    I2C_CLOCK_LO();
    _delay_us(delay);
}

// Send a STOP Condition
//
void I2C_Stop()
{
    I2C_CLOCK_HI();
    _delay_us(delay);

    I2C_DATA_HI();
    _delay_us(delay);
}

// write a byte to the I2C slave device
//
unsigned char I2C_Write(unsigned char c)
{
    for (char i = 0; i < 8; i++)
    {
        I2C_WriteBit(c & 128);

        c <<= 1;
    }

    //return I2C_ReadBit();
    return 0;
}


// read a byte from the I2C slave device
//
unsigned char I2C_Read(unsigned char ack)
{
    unsigned char res = 0;

    for (char i = 0; i < 8; i++)
    {
        res <<= 1;
        res |= I2C_ReadBit();
    }

    if (ack > 0)
    {
        I2C_WriteBit(0);
    }
    else
    {
        I2C_WriteBit(1);
    }

    _delay_us(delay);

    return res;
}

void SW_I2C_Start(char i2c_client_address)
{
I2C_Start()	;
I2C_Write(device_address);
I2C_WriteBit(0);           //client will send ACK ,  need 1 more clock

}
void SW_I2C_Write(char data)
{
I2C_Write(data);
I2C_WriteBit(0);
}
