#include "LCD.h"

int LCD_RS;
int LCD_RW;
int LCD_EN;
int LCD_D4;
int LCD_D5;
int LCD_D6;
int LCD_D7;

//Internal helper functions here:

void LCD_DrivePin(int pin, int val)
{
	int mask = 1<<(pin%8);
	
	switch(pin/8)
	{		
#ifdef PORTA
		case 0:
			if(val)
				PORTA = PORTA|mask;
			else
				PORTA = PORTA&(~mask);
			break;
#endif
#ifdef PORTB
		case 1:
			if(val)
				PORTB = PORTB|mask;
			else
				PORTB = PORTB&(~mask);
			break;
#endif
#ifdef PORTC
		case 2:
			if(val)
				PORTC = PORTC|mask;
			else
				PORTC = PORTC&(~mask);
			break;
#endif
#ifdef PORTD
		case 3:
			if(val)
				PORTD = PORTD|mask;
			else
				PORTD = PORTD&(~mask);
			break;
#endif
			
	}
}

void LCD_ClockEN()
{
	LCD_DrivePin(LCD_EN,1);
	LCD_DrivePin(LCD_EN,0);
}

void LCD_DriveInterface(int rs, int rw, int d4, int d5, int d6, int d7)
{
	LCD_DrivePin(LCD_RS,rs);
	LCD_DrivePin(LCD_RW,rw);
	LCD_DrivePin(LCD_D4,d4);
	LCD_DrivePin(LCD_D5,d5);
	LCD_DrivePin(LCD_D6,d6);
	LCD_DrivePin(LCD_D7,d7);
	LCD_ClockEN();
}

void LCD_WriteData(int rs, int rw, int data)
{
	int d4 = data&1;
	int d5 = data&2;
	int d6 = data&4;
	int d7 = data&8;
	LCD_DriveInterface(rs,rw,d4,d5,d6,d7);
}

void LCD_SetLCDPins(int rs, int rw, int en, int D4, int D5, int D6, int D7)
{
	LCD_RS = rs;
	LCD_RW = rw;
	LCD_EN = en;
	LCD_D4 = D4;
	LCD_D5 = D5;
	LCD_D6 = D6;
	LCD_D7 = D7;
}

void LCD_InitLCD()
{
	LCD_DriveInterface(0,0,0,1,0,0);
	LCD_DriveInterface(0,0,0,1,0,0);
	LCD_DriveInterface(0,0,0,0,1,1);
	_delay_us(40);
	LCD_DriveInterface(0,0,0,0,0,0);
	LCD_DriveInterface(0,0,1,1,1,1);
	_delay_us(40);
	LCD_DriveInterface(0,0,0,0,0,0);
	LCD_DriveInterface(0,0,1,0,0,0);
	_delay_us(1530);
	LCD_DriveInterface(0,0,0,0,0,0);
	LCD_DriveInterface(0,0,0,1,1,0);
}

LCD_SendCommand(int command)
{
	LCD_WriteData(0,0,command/16);
	LCD_WriteData(0,0,command);
}

LCD_SendCharacter(char character)
{
	LCD_WriteData(1,0,character/16);
	LCD_WriteData(1,0,character);
}

void LCD_SetCursor(int x, int y)
{
	int command = 0x80;
	if(y)
		command+= 0x40;
	command+=x;
	LCD_SendCommand(command);
}

void LCD_WriteCharacters(char *chars)
{
	int i = 0;
	while(chars[i])
	{
		LCD_SendCharacter(chars[i]);
		i++;
	}
}

void LCD_Clear()
{
	LCD_SendCommand(1);
}