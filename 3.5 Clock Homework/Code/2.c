// cspell:ignore ATMEGA PORTA PORTB PORTC PORTD DDRA DDRB DDRC DDRD MCUCR GICR

#include <io.h>
#include <mega16.h>
#include "delay.h"

// A clock using ATMEGA16 and 6 7-segment displays (common cathode), (2 for hours, 2 for minutes, 2 for seconds).
// The first 7-segment will display the first digit of the hours, the second 7-segment will display the second digit of the hours, and so on.
// both 7-segments of hours are connected to PORTA,
// both 7-segments of minutes are connected to PORTB,
// both 7-segments of seconds are connected to PORTC.
// since both 7 segs are connected to the same port, we can't display two different numbers at the same time,
// we will display the first number for a short time, then the second number for a short time, and so on.
// on each second, the clock time will increase by 1 second.
// there are 2 buttons, one for increasing the hour, and the other for increasing the minute.
// the hour button is connected to INT0, and the minute button is connected to INT1.
// falling edge for INT0, and low level for INT1.

unsigned char numbers[10] = { 0b01000000, 0b11111001, 0b00100100, 0b00110000, 0b00011001, 0b00010010, 0b00000010, 0b01111000, 0b00000000, 0b00010000 };
int hour = 0;
int minute = 0;
int second = 0;

// Hour increment button
interrupt [EXT_INT0] void myISR0() {
	hour++;
}

// Minute increment button
interrupt [EXT_INT1] void myISR1() {
	minute++;
}

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

// Common cathode controls:
// PORTA7 (PA7) -> 7-segment A (first digit of hours)
// PORTB7 (PB7) -> 7-segment A (second digit of hours)
// PORTD5 (PD5) -> 7-segment B (first digit of minutes)
// PORTD4 (PD4) -> 7-segment B (second digit of minutes)
// PORTD1 (PD1) -> 7-segment C (first digit of seconds)
// PORTD0 (PD0) -> 7-segment C (second digit of seconds)

void disableAll() {
	PORTA |= setOne(PORTA7);
	PORTB |= setOne(PORTB7);
	PORTD |= setOne(PORTD5) | setOne(PORTD4) | setOne(PORTD1) | setOne(PORTD0);
}

// To enable the 7-segment of the first digit of the hours, we need to set the PORTA7 to 0
// And set the rest of the 7 segment cathode control pins to 1.

void showHour1() {
	disableAll();
	PORTA = numbers[hour / 10];
	PORTA &= setZero(PORTA7);
}

void showHour2() {
	disableAll();
	// Setting PORTA should not affect PORTA7
	PORTA = numbers[hour % 10] | setOne(PORTA7);

	PORTB &= setZero(PORTB7);
}

void showMinute1() {
	disableAll();
	// Setting PORTB should not affect PORTB7
	PORTB = numbers[minute / 10] | setOne(PORTB7);

	PORTD &= setZero(PORTD5);
}

void showMinute2() {
	disableAll();
	// Setting PORTB should not affect PORTB7
	PORTB = numbers[minute % 10] | setOne(PORTB7);

	PORTD &= setZero(PORTD4);
}

void showSecond1() {
	disableAll();
	PORTC = numbers[second / 10];
	PORTD &= setZero(PORTD1);
}

void showSecond2() {
	disableAll();
	PORTC = numbers[second % 10];
	PORTD &= setZero(PORTD0);
}

void showTime() {
	unsigned int delay = 1000 / 6;

	showHour1();
	delay_ms(delay);
	showHour2();
	delay_ms(delay);
	showMinute1();
	delay_ms(delay);
	showMinute2();
	delay_ms(delay);
	showSecond1();
	delay_ms(delay);
	showSecond2();
	delay_ms(delay);

	second++;

	if (second == 60) {
		second = 0;
		minute++;
	}

	if (minute == 60) {
		minute = 0;
		hour++;
	}

	if (hour == 24) {
		hour = 0;
	}
}

void main() {
	// only PD2 (INT0) and PD3 (INT1) are inputs, the rest are outputs.
	DDRA = 0b11111111;
	DDRB = 0b11111111;
	DDRC = 0b11111111;
	DDRD = 0b11110011;

	// INT0 -> falling edge
	// INT1 -> low level
	MCUCR &= ~(1 << ISC10);
	MCUCR |= (1 << ISC11);
	MCUCR &= ~(1 << ISC00);
	MCUCR &= ~(1 << ISC01);

	GICR = 0b11000000;

	#asm("sei")

	while (1) {
		showTime();
	}
}
