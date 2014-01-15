/*
 * adcmeansure.h
 *
 *  Created on: 2014.01.14.
 *      Author: zoon
 */

#ifndef ADCMEANSURE_H_
#define ADCMEANSURE_H_
//-------------------------------------------
void ADInit(){
//-------------------------------------------
	DIDR0  |= (1<<ADC2D);
	ADMUX |= (0<<REFS1)
		  |  (0<<REFS0);

	ADCSRA |= (1<<ADEN)  //enable AD
		   |  (0<<ADSC)
		   |  (0<<ADATE)
		   |  (0<<ADSC)
		   |  (1<<ADPS2)
		   |  (1<<ADPS1)
		   |  (1<<ADPS0);
}

//------------------------------------
unsigned int MeasureADC(unsigned char channel) {
//------------------------------------
	ADMUX &= 0b11100000;         //fentieket nembántod, alját nullázod
	ADMUX |= channel;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));   // waiting for the measuring
	return ADC;
}


#endif /* ADCMEANSURE_H_ */
