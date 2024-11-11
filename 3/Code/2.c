#include <io.h>
#include <mega16.h>
#include "delay.h"

// Two 7-segment countdown from 99 to 0. both 7 segs are connected to PORTC.
// since both 7 segs are connected to the same port, we can't display two different numbers at the same time, with a small delay between each number.
// so the first 7 seg will display the first number, then the second 7 seg will display the second number, then the first 7 seg will display the first number, and so on.

unsigned char numbers[10] = { 0b01000000, 0b11111001, 0b00100100, 0b00110000, 0b00011001, 0b00010010, 0b00000010, 0b01111000, 0b00000000, 0b00010000 };
unsigned char currentNumber = 0;
int isRunning = 0;

// Start button
interrupt [EXT_INT0] void myISR0() {
	isRunning = 1;
	if (currentNumber == 0) {
		currentNumber = 99;
	}
}

// pause button
interrupt [EXT_INT1] void myISR1() {
	isRunning = 0;
}

// stop and reset button
interrupt [EXT_INT2] void myISR2() {
	isRunning = 0;
	currentNumber = 0;
}

void showCurrentNumber(unsigned char number) {
	unsigned int delay = 100;

	PORTC = numbers[number / 10];
	// Since the 7-segment is common cathode, we need to set the PD0 to 0 to enable the 7-segment A, and set the PD1 to 0 to enable the 7-segment B.
	PORTD = 0b00000001;
	delay_ms(delay);
	PORTC = numbers[number % 10];
	PORTD = 0b00000010;
	delay_ms(delay);
	PORTD = 0b10000001;
}

void main() {
	// isRunning = 1;

	// DDRA is input
	DDRA = 0x00;

	// DDRC is output
	DDRC = 0xff;

	// PD0 & PD1 are output, others are input
	DDRD = 0b00000011;

	MCUCR &= ~(1 << ISC10);
	MCUCR &= ~(1 << ISC11);
	MCUCR &= ~(1 << ISC00);
	MCUCR |= (1 << ISC01);

	MCUCSR |= (1 << ISC2);

	GICR = 0b11100000;

	#asm("sei")

	while (1) {
		if (isRunning == 1) {
			showCurrentNumber(currentNumber);
			currentNumber--;
			if (currentNumber == 0) {
				isRunning = 0;
			}
		} else {
			showCurrentNumber(currentNumber);
		}
	}
}
