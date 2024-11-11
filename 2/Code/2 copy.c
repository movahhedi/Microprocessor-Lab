#include <io.h>
#include <mega16.h>
#include "delay.h"

// ATMEGA16 code for controlling a 7-segment display with 2 buttons (up and down)
// Common Anode 7-segment display

void main(void)
{
	// 0 is on, 1 is off
	unsigned char numbers[10] = {
		// 0
		0b01000000,
		// 1
		0b11111001,
		// 2
		0b00100100,
		// 3
		0b00110000,
		// 4
		0b00011001,
		// 5
		0b00010010,
		// 6
		0b00000010,
		// 7
		0b01111000,
		// 8
		0b00000000,
		// 9
		0b00010000
	};

	unsigned char currentNumber = 0;

	// Up button is connected to PB0
	// Down button is connected to PB1
	// 7-segment display is connected to PORTC

	DDRB = 0x00;
	DDRC = 0xFF;

	while (1) {
		if (PINB & 0b00000001 == 0) {
			currentNumber++;
		}
		else if (PINB & 0b00000010 == 0) {
			currentNumber--;
		}

		PORTC = numbers[currentNumber];

		delay_ms(500);
	}

}
