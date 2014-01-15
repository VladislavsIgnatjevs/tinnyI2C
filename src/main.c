#include <a1018lcd.h>
#include <adcmeansure.h>

void Setup_PWM()
{
	DDRB |= (1<<PB1) ; // Output on PB1/OC0AB
	// Timer0, Set OC0A on comp. match (inv). Mode 3: Fast PWM
		   TCCR0A = (1<<COM0A1)|(1<<COM0A0)|(1<<COM0B1)|(1<<COM0B0)|(1<<WGM01)|(1<<WGM00);
	// 1:8 presc.
		   TCCR0B = (1<<CS01)|(1<<CS00)|(0<<WGM02);
}


int main()
{

	I2C_Init();
	DDRB&= ~ (1<<PB4); //ADC Input

	ADInit();
	clearscreen(5,101);




while(1){

int adcvalue = MeasureADC(2);

clearscreen(1,5*8);
	write_int(adcvalue);
_delay_ms(100);

}

return 0;
}
