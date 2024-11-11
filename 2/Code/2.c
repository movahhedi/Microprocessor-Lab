#include <io.h>
#include <mega16.h>
#include "delay.h"

void main(void)
{
	unsigned char numbers[10] = { 0b01000000, 0b11111001, 0b00100100, 0b00110000, 0b00011001, 0b00010010, 0b00000010, 0b01111000, 0b00000000, 0b00010000 };

	unsigned char currentNumber = 0;

	DDRB = 0x00;
	DDRC = 0xFF;

	while (1) {
		if ((PINB & 0b00000001) == 0) {
			currentNumber++;
			if (currentNumber > 9) {
				currentNumber = 0;
			}
		}
		else if ((PINB & 0b00000010) == 0) {
			currentNumber--;
			if (currentNumber < 0) {
				currentNumber = 9;
			}
		}

		PORTC = numbers[currentNumber];

		delay_ms(300);
	}
}
