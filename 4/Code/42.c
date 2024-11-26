// cspell:ignore lcd_gotoxy lcd_putsf

// LCD project to show a text a 16x2 LCD rotating text

#include <io.h>
#include <mega16.h>
#include <alcd.h>
#include <string.h>
#include "delay.h"

void main() {
	unsigned char displayWidth = 16;
	unsigned char text[16] = "Movahhedi  ";
	unsigned char textToShow[16] = "";
	char i = 0, firstCharacterShownIndex = 0, numberOfSpaces = 3;

	lcd_init(displayWidth);
	lcd_clear();

	// lcd_gotoxy(0, 0);
	// lcd_putsf("Hello");
	// lcd_puts("Hello");
	// lcd_putchar('H');

	while (1) {
		lcd_clear();
		// textToShow = "";
		textToShow[0] = '\0';

		// build the 16 characters to show (with spaces) based on the firstCharacterShownIndex

		// create a substring of the text from the firstCharacterShownIndex to the end
		strcpy(textToShow, text + firstCharacterShownIndex);

		// append spaces (numberOfSpaces) to the end of the textToShow
		for (i = 0; i < numberOfSpaces; i++) {
			textToShow[strlen(textToShow)] = ' ';
		}

		// append the rest of the text from the beginning until 16 characters is reached
		for (i = strlen(textToShow); i < displayWidth; i++) {
			textToShow[strlen(textToShow)] = text[i];
		}

		// show
		lcd_gotoxy(0, 1);
		lcd_puts(textToShow);

		firstCharacterShownIndex++;

		if (firstCharacterShownIndex == strlen(text)) {
			firstCharacterShownIndex = 0;
		}

		delay_ms(100);
	}
}
