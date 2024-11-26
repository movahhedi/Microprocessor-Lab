// cspell:ignore lcd_gotoxy lcd_putsf DDRA DDRB DDRC DDRD PORTA PORTB PORTC PORTD PINA PINB PINC PIND

// Calculator

#include <io.h>
#include <mega16.h>
#include <alcd.h>
#include <string.h>
#include "delay.h"

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

// Key map array
unsigned char keyMap[16] = {
	'C',
	'0',
	'=',
	'+',
	'1',
	'2',
	'3',
	'-',
	'4',
	'5',
	'6',
	'*',
	'7',
	'8',
	'9',
	'/'
};

unsigned char getNumberFromKeypad() {
	// unsigned char col = 0, row = 0;
	unsigned char key = 0;

	// unsigned char debug = (PINC | ~(1 << PINC4));
	// lcd_putchar('1');
	// lcd_putchar(debug);
	// lcd_putchar(debug ? '1' : '0');

	// Column 0
	PORTC |= setOne(PORTC3);
	PORTC &= setZero(PORTC0);
	if ((PINC & (1 << PINC4)) == 0) {
		key = '7';
		return key;
	} else if ((PINC & (1 << PINC5)) == 0) {
		key = '4';
		return key;
	} else if ((PINC & (1 << PINC6)) == 0) {
		key = '1';
		return key;
	} else if ((PINC & (1 << PINC7)) == 0) {
		key = 'C';
		return key;
	}

	// delay_ms(250);

	// Column 1
	PORTC |= setOne(PORTC0);
	PORTC &= setZero(PORTC1);
	if ((PINC & (1 << PINC4)) == 0) {
		key = '8';
		return key;
	} else if ((PINC & (1 << PINC5)) == 0) {
		key = '5';
		return key;
	} else if ((PINC & (1 << PINC6)) == 0) {
		key = '2';
		return key;
	} else if ((PINC & (1 << PINC7)) == 0) {
		key = '0';
		return key;
	}

	// delay_ms(250);

	// Column 2
	PORTC |= setOne(PORTC1);
	PORTC &= setZero(PORTC2);
	if ((PINC & (1 << PINC4)) == 0) {
		key = '9';
		return key;
	} else if ((PINC & (1 << PINC5)) == 0) {
		key = '6';
		return key;
	} else if ((PINC & (1 << PINC6)) == 0) {
		key = '3';
		return key;
	} else if ((PINC & (1 << PINC7)) == 0) {
		key = '=';
		return key;
	}

	// delay_ms(250);

	// Column 3
	PORTC |= setOne(PORTC2);
	PORTC &= setZero(PORTC3);
	if ((PINC & (1 << PINC4)) == 0) {
		key = '/';
		return key;
	} else if ((PINC & (1 << PINC5)) == 0) {
		key = '*';
		return key;
	} else if ((PINC & (1 << PINC6)) == 0) {
		key = '-';
		return key;
	} else if ((PINC & (1 << PINC7)) == 0) {
		key = '+';
		return key;
	}

	// delay_ms(250);

	return key;
}

unsigned char getNumberFromKeypadWithDelay() {
	unsigned char key = 0;

	// do {
		key = getNumberFromKeypad();
	// } while (key == 0);

	if (key != 0) {
		delay_ms(250);
	}

	return key;
}

void addCharToLcd(unsigned char key) {
	lcd_putchar(key);
}

void main() {
	unsigned char displayWidth = 16;

	// PORTB is connected to the LCD
	// PORTC is connected to the keypad
	// PORTC PC0-PC3 is connected to the columns of the keypad
	// PORTC PC4-PC7 is connected to the rows of the keypad

	// DDRB is out
	// DDRB = 0b11111111;
	// DDRC PC0-PC3 is output, PC4-PC7 is input
	DDRC = 0b00001111;

	lcd_init(displayWidth);
	lcd_clear();

	lcd_gotoxy(0, 1);

	// lcd_putchar('0');

	PORTC = 0xff;
	while (1) {
		unsigned char key = getNumberFromKeypadWithDelay();

		if (key != 0) {
			lcd_putchar(key);
		}
	}
}
