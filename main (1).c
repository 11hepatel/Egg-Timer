/*
 * Lab5.c
 *
 * Created: 10/7/2019 11:01:07 AM
 * Author : hdpg4c
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "LCD.h"


int HR = 14;
int MIN = 90;
int SEC = 60;
 

void outputTime();
ISR(TIMER1_COMPA_vect);
int main(void)
{
	//PortB as output port
	DDRB = 0xff;
	DDRE |= (1<<RS)|(1<<RW)|(1<<EN);
	PORTE &= ~(1<<EN);
    
	DDRA = 0X00; 
	PORTA = 0xff; //input to portA
	
	lcdInit();
	
	sei();
	
	TCCR1B = (1 << WGM12);
	TCCR1B = (1 << CS12) | ( 1 << CS10);
	
	OCR1A = 15625;
	
	TIMSK1 = (1 << OCIE1A);
	
	outputTime();
	
	while (1) 
    {
		if((~PINA & (1 << PINA0)) == (1 << PINA0))
		{
			HR++; //increment the hr value
			if(HR >= 24) //if hr is greater than and equal to 23
			{
				HR =0; //hr is set to 0
			}
			outputTime(); //calling the output time function
			while ((~PINA & (1 << PINA0)) == (1 << PINA0));
		}
		if((~PINA & (1<<PINA5)) == (1 << PINA5))
		{
			 HR--;
			 if(HR < 0)
			 {
				 HR = 23;
			 }
			 outputTime();
			 while((~PINA & (1<< PINA5)) == (1 << PINA5));
        }
    outputTime();
	
	//char arr[] = "AA";
	//lcd_prntln(arr);
}
}


//Function for delay 
//void my_delay(void)
//{
	//calculating the value using the excel sheet depending on the amount of delay you want 
	//OCR1A = 0XF424;
	//TCCR1A = 0x00;
	//TCCR1B = 0b00001100;
	
	//creating more delay by using while loop
	//while((TIFR1 & (1 << OCF1A)) == 0) //while loop till TIFR1 and TOV1 is greater then 1 are equal to zero 
	//{
		
	//}
	//TIFR1 |= (1 << OCF1A);
	
	//TCCR1A = 0;
	//TCCR1B = 0;  
//}

void outputTime()
{
	
	setcursor(0);
	
	//lcdData((HR/10) + '0');
	//lcdData((HR%10) + '0');
	//lcdData(':');
	
	
	lcdData((MIN/10) + '0');
	lcdData((MIN%10) + '0');
	lcdData(':');
	
	
	lcdData((SEC/10) + '0');
	lcdData((SEC%10) + '0');

		setcursor(0);

}

ISR(TIMER1_COMPA_vect)
{
	
	if(SEC == -1)
	{
		MIN--;
		SEC = 59;
	}
	if(MIN == -1)
	{
		HR--;
		MIN = 59;
	}
	if(HR == 0 && MIN == 0 && SEC == 0)
	{
		sound(); 
		//music(); 
	}
	outputTime();
}

void music() //play the music
{
	int duration;
	int note;
	
	int pitches[] = {E, E, E, E, E, E, E, G, C, D, E, F, F, F, F, F, E,
							E, E, E, E, D, D, E, D, G}; 
	int *music_notes = pitches; 
	
	int tempo[] = {8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 2, 8, 8, 8, 8, 8, 8, 8, 16, 16, 
					8, 8, 8, 8, 4, 4};
	int tempo_num = 26;
	
	uint16_t delay = tempo_num * 10000;
	
	while (*music_notes)
	{
		note = *music_notes;
		music_notes++;
		
		duration = *music_notes;
		music_notes++;
		
		for(int i = 0; i < 32/duration; i++)
		{
			
		
		
		
	
}

//just a buzz
void buzzer(float duration, float period)
{
	long cycle;
	float half_period;
	
	cycle = (duration/period);
	half_period = (period/2);
	
	DDRE = (1 << BUZZ_PIN) | DDRE;
	
	for (int i=0; i< cycle ; i++)   // Toggle the speaker the appropriate number of cycles
	{
		 _delay_ms(half_period);                         // Wait a half cycle to toggle port pin
		 PORTE = (1 << BUZZ_PIN) | PORTE;    // Set the port pin
		 _delay_ms(half_period);                         // Wait a half cycle to clear the port pin
		 PORTE = ~(1 << BUZZ_PIN) & PORTE;   // Clear the port pin
	 }
 
	return;
}

void sound()
{
	for (int i = 0; i < 4; i++)
	{
		buzzer(75, 0.5)
		PORTE = 0b00010000 ^ PORTE;
		_delay_ms(500);
	}
	return;
}