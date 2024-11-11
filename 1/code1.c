#include <io.h>
#include <mega16.h>
#include "delay.h"

void main(void) {
	// ATMEGA16 code for 2 alternating blinking LEDs

	/*
	while (1) {
		PORTA = 0x00; // Turn OFF all LEDs
		delay_ms(1000); // 1 second delay
		PORTA = 0xFF; // Turn ON all LEDs
		delay_ms(1000); // 1 second delay
	} */

	// DDRA |= ((1 << DDA0) | (1 << DDA1));
	// DDRB &= ~((1 << DDB0) | (1 << DDB1));

	DDRA = 0x00;
	DDRB = 0xFF;

	while (1) {
		if (PINA & 0x01 == 0) {
			PORTA |= (1 << PORTA0);
		} else {
			PORTA &= ~(1 << PORTA0);
		}
		if (PINB & 0x01 == 0) {
			PORTA |= (1 << PORTA1);
		} else {
			PORTA &= ~(1 << PORTA1);
		}

		/* PORTA |= (1 << PORTA0);
		PORTA &= ~(1 << PORTA1);
		delay_ms(500);

		PORTA &= ~(1 << PORTA0);
		PORTA |= (1 << PORTA1);
		delay_ms(500); */
	}


}
