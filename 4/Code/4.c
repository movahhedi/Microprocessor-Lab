// cspell:ignore lcd_gotoxy lcd_putsf

// LCD project to show a text a 16x2 LCD rotating text

#include <io.h>
#include <mega16.h>
#include <alcd.h>
#include <string.h>
#include "delay.h"

void main() {
	unsigned char displayWidth = 16;
	unsigned char text[16] = "Movahhedi ";
	char i = displayWidth;
	char j = 0;

	lcd_init(displayWidth);
	lcd_clear();

	// lcd_gotoxy(0, 0);
	// lcd_putsf("Hello");
	// lcd_puts("Hello");
	// lcd_putchar('H');

	while (1) {
		lcd_gotoxy(0, 1);
		// start write from left (0)
		for (j = 0; j < displayWidth; j++) {
			char index = (j + i) % strlen(text);
			lcd_putchar(text[index]);
		}

		// start write from right (displayWidth)
		// for (j = displayWidth; j > 0; j--) {
		// 	char index = (j + i) % 16;
		// 	lcd_putchar(text[index]);
		// }

		delay_ms(100);

		i--;

		if (i == 0) {
			i = displayWidth;
		}
	}
}
