/*
 * LCD.h
 *
 * Created: 9/30/2019 10:43:21 AM
 *  Author: hdpg4c
 */ 


#ifndef LCD_H_
#define LCD_H_

#define LCD_DATA PORTB
#define LCD_CONFIG PORTE
#define RS PORTE2
#define RW PORTE3
#define EN PORTE5
#define BUZZ_PIN PORTE4


//for the buzzer
#define C 523
#define D 587
#define E 659
#define F 698
#define G 784

void lcdCmd(unsigned char cmd);

void lcdData(unsigned char data);

void setcursor(unsigned char cursor);

void displayshift(unsigned char shift);

void lcdInit(void);

void lcd_prntln(unsigned char *string);

#endif /* LCD_H_ */  