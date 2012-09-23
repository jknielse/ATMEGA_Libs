
//The "number" of the pin is based on a concatenated view of the ports
//e.g. the PORTA_6 pin is 6, the PORTB_3 pin is 11 (8+3)

void LCD_SetLCDPins(int rs, int rw, int en, int D1, int D2, int D3, int D4);

void LCD_InitLCD();

void LCD_SetCursor(int x, int y);

void LCD_WriteCharacters(char *chars);

void LCD_Clear();