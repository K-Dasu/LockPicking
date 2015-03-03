/*Keshav Dasu kdasu001@ucr.edu:
* Lab Section 022:
* Assignment: Custom Lab Project
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/


#include <avr/io.h>
#include "Utilities.h"
#include "io.h"

/*      Global Variables          */


unsigned short value = 0x0000;
unsigned char display = 0x07;


/*     Functions          */

void LP_LCD_init(){
	LCD_init();
	LCD_DisplayString(1,"||||||||||||||||");
	LCD_Cursor(17);
}

void ADC_init() {
ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
// ADEN: setting this bit enables analog-to-digital conversion.
// ADSC: setting this bit starts the first conversion.
// ADATE: setting this bit enables auto-triggering. Since we are
// in Free Running Mode, a new conversion will trigger
// whenever the previous conversion completes.
}

/*     Main          */

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x03; PORTB = 0xFC;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	

	ADC_init();
	LP_LCD_init();
		
    while(1)
    {
		value = ADC;
								
		if(value > 800){
			display = 0x0F;
		}else if(value > 750){
			display = 0x0E;
		}else if(value > 700){
			display = 0x0D;
		}else if(value > 650){
			display = 0x0C;
		}else if(value > 550){
			display = 0x0B;
		}else if(value > 500){
			display = 0x0A;
		}else if(value > 450){
			display = 0x09;
		}else if(value > 400){
			display = 0x08;
		}else if(value > 350){
			display = 0x07;
		}else if(value > 300){
			display = 0x06;
		}else if(value > 250){
			display = 0x05;
		}else if(value > 200){
			display = 0x04;
		}else if(value > 150){
			display = 0x03;
		}else if(value > 100){
			display = 0x02;
		}else if(value > 5){
			display = 0x01;
		}else{
			display = 0x00;
		}																										
        //TODO:: Please write your application code 
		PORTC = display;
    }
}