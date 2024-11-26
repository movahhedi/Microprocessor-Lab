// cspell:ignore lcd_gotoxy lcd_putsf DDRA DDRB DDRC DDRD PORTA PORTB PORTC PORTD PINA PINB PINC PIND

#include <io.h>
#include <mega16.h>
#include <alcd.h>
#include <string.h>
#include "delay.h"
#include "stdlib.h"
#include "stdio.h"

/**
PORTD &= ~(1 << PD6);   ->   PORTD &= setZero(PD6);
*/
int setZero(int t) {
	return ~(1 << t);
}

/**
PORTD |= (1 << PD6);   ->   PORTD |= setOne(PD6);
*/
int setOne(int t) {
	return (1 << t);
}

// ADC with potentiometer.

int data = 0;
char text[16] = "";
float voltage = 0;

void main() {
	unsigned char displayWidth = 16;

	// PORTB is connected to the LCD

	lcd_init(displayWidth);
	lcd_clear();

	lcd_gotoxy(0, 0);

	// // Enable ADC
	// ADEN = 1;
	// // Start conversion
	// ADSC = 1;
	// ADATE = 0;
	// ADIF = 1;
	// ADIE = 0;
	// ADPS0 = 1;
	// ADPS1 = 1;
	// ADPS2 = 0;


	// REFS0 = 1;
	// REFS1 = 0;
	// ADLAR = 0;
	// MUX0 = 0;
	// MUX1 = 0;
	// MUX2 = 0;
	// MUX3 = 0;
	// MUX4 = 0;



	while (1) {
		ADCSRA = 0b11010110;
		ADMUX = 0b01000000;

		// ADCSRA |= setOne(ADEN);
		ADCSRA |= setOne(ADSC);
		ADCSRA &= setZero(ADIF);
		delay_us(1000);

		while (ADCSRA & (1 << ADIF) == 0);

		ADCSRA |= setOne(ADIF);

		ADCSRA &= setZero(ADSC);
		// ADCSRA &= setZero(ADEN);

		// data |= ADCL;
		// data |= (8 << ADCH);

		voltage = ADCW * 0.004;

		ftoa(voltage, 2, text);
		lcd_puts(text);

		delay_ms(100);


		lcd_clear();
	}
}
