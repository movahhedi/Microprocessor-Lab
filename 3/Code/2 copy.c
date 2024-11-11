#include <io.h>
#include <mega16.h>
#include "delay.h"

void main(void)
{
	unsigned char numbers[10] = { 0b01000000, 0b11111001, 0b00100100, 0b00110000, 0b00011001, 0b00010010, 0b00000010, 0b01111000, 0b00000000, 0b00010000 };

	unsigned char currentNumber = 0;

	// DDRA is input
	DDRA = 0x00;
	DDRC = 0xff;
	DDRD = 0xff;

	unsigned char currentNumber = 99;
	bool isRunning = false;

	while (1) {
		if ((PINB & 0x01) == 0) {
			isRunning = true;
		} else if ((PINB & 0x02) == 0) {
			isRunning = false;
		} else if ((PINB & 0x03) == 0) {
			isRunning = false;
			currentNumber = 99;
		}

		PORTC = numbers[currentNumber];

		delay_ms(300);
	}
}
