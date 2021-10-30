/*
 * CFile1.c
 *
 * Created: 9/30/2019 10:42:52 AM
 *  Author: hdpg4c
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include "util/delay.h"
#include "LCD.h"

void lcdInit(void)
{
	lcdCmd(0b00110000);
	_delay_ms(5);
	
	lcdCmd(0b00110000);
	_delay_ms(1);
	
	lcdCmd(0b00110000);
	_delay_ms(1);
	
	//Function set
	lcdCmd(0b00111000); // 0, 0,1,dl = 1, N = 0, F = 0,0
	
	//Display off
	lcdCmd(0b00001000);
	//Display clear
	lcdCmd(0b00000001);
	//Entry mode set
	lcdCmd(0b00000110); //0,0,0,0,0,1,I/D = 1, 0
	//Display on 00001DCB
	lcdCmd(0b00001111); // 0, 0,0,0,1, d = 1, C = 1, B =1
	
}

void lcdCmd(unsigned char cmd)
{
	//rs = 0
	LCD_CONFIG &= ~(1 << RS);
	//Rw = 0
	LCD_CONFIG &= ~(1 << RW);
	LCD_CONFIG |= (1 << EN);
	_delay_ms(10);
	LCD_DATA = cmd;
	_delay_ms(10);
	LCD_CONFIG &= ~(1 << EN);
}

void lcdData(unsigned char data)
{
	//rs = 1
	LCD_CONFIG |= (1 << RS);
	LCD_CONFIG &= ~(1 << RW);
	//RW = 0
	LCD_CONFIG |= (1 << EN);
	_delay_ms(10);
	LCD_DATA = data;
	_delay_ms(10);
	LCD_CONFIG &= ~(1 << EN);
}

//Set DDRAM address so that cursor is positioned 
void setcursor(unsigned char cursor)
{
	cursor = cursor | 0b10000000;
	lcdCmd(cursor);
} 

void displayshift(unsigned char shift) //shift = 0 for shift left
                                       //shift = 1 for shift right
{
	if (shift == 0) //if shift is zero
	{
		lcdCmd(0b00011100);////0, 0, 1,1 S/C = 1, R/L = 1,0,0
	}
	else 
	{
		lcdCmd(0b00011000); //0, 0, 1,1 S/C = 1, R/L = 0,0,0
	}
}

//Print the multiple character on the lcd
void lcd_prntln(unsigned char *string)
{
	while(*string != '\0') 
	{
		lcdData(*string);
		string++;
		
	}
}