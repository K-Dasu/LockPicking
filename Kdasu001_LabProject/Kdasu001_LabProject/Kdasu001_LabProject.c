/*Keshav Dasu kdasu001@ucr.edu:
* Lab Section 022:
* Assignment: Custom Lab Project
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/


#include <avr/io.h>
#include "Utilities.h"
#include "Helper_functions.h"
#include "io.h"



/*      Global Variables          */


//Related to the correct pin and which pin is being looked at
unsigned char validate = 0;
unsigned char current_position = 1;
unsigned char previous_position = 0;
unsigned char array_len = 3; // tracks amount of picks to open starting is 3
unsigned char cp_array_pos = 0;
unsigned char array_position = 0; //used for scrolling text
unsigned char correct_pins[50];


// Booleans and other variables
int iter = 0;
short adc_value = 0;
const unsigned char pins[] = {'|','|','|','|','|','|','|','|','|','|','|','|','|','|','|','|'};
const unsigned char sp[] = {'S','u','c','c','e','s','s','f','u','l',' ','P','i','c','k','!'};
const unsigned char pbn[] = {'P','r','e','s','s',' ','B','u','t','t','o','n',' ','N','o','w'};
unsigned char message[]= {'W','e','l','c','o','m','e',' ','T','o',' ','L','o','c','k',' ','P','i','c','k',' ','P','r','e','s','s',' ','T','o',' ','S','t','a','r','t','!','!'};
unsigned char display[16];
unsigned char game_over = 0x00; //bool if 1 game over and therefore proceed with the reset button
unsigned char game_start = 0x00;
unsigned char gs_disply = 0x00;
unsigned char win_disply = 0x00;
unsigned char button1 = 0x00;
unsigned char setarray = 0x00;


/*     Tasks         
	   Task1 = Scrolling
	   Task2 = 

*/ 

enum SM1_States { SM1_start, press, gamestart };
// Monitors button connected to PA0. When the button is
// pressed, shared variable "pause" is toggled.
int TitleScreen(int state) {
	unsigned char LENGTH_OF_LCD = 16;
	unsigned char cursor_position = 1;
	unsigned char counter = 0x00;
	
	//State machine transitions
	switch (state) {
		case SM1_start:
			state = SM1_start;
			if(button1){
				state = press;
			}
			break;
		case press:
			if(button1){
				state = press;
			}else{
				state = gamestart;
			}
			break;
		case gamestart:
			state = gamestart;
			if(game_start = 0x00){
				state = SM1_start;
			}
			break;
		default:
			state = SM1_start;
			break;
	}
	//State machine actions
	switch(state) {
		case SM1_start: 
			for (counter = 0, cursor_position = array_position; counter < LENGTH_OF_LCD; cursor_position = cursor_position + 1, counter = counter + 1) {
				if (cursor_position > sizeof(message)) {
					cursor_position = 1;
				}
				if (cursor_position - 1 >= 0) { display[counter] = message[cursor_position - 1]; }
			}
			
			for (counter = 0, cursor_position = 1; counter < LENGTH_OF_LCD; cursor_position = cursor_position + 1, counter = counter + 1) {
				LCD_Cursor(cursor_position);
				LCD_WriteData(display[counter]);
			}	
			array_position = array_position + 1;
			if (array_position == (int) sizeof(message)) {
				array_position = 0;
			}			
			break;
		case press:
			break;
		case gamestart:
			if(gs_disply == 0x00){
				LCD_DisplayString(1,pins);
				LCD_Cursor(17);
				game_start = 0x01;
				game_over = 0x00;
				gs_disply = 0x01;
			}				
			break;
		default: break;
	}
	return state;
}



enum SM_ScrollStates {idle_sc,sm1_state1};
int SM_Scroll(int state){

	switch(state){ //Transitions
		case idle_sc:
			if(game_start == 0x01){
				state = sm1_state1;
			}else{
				state = idle_sc;
			}
			break;
		case sm1_state1:
			adc_value = ADC;
			current_position = get_position(array_len, adc_value);
			state = sm1_state1;
			if(game_over == 0x01){
				state = idle_sc;
			}else{
				state = sm1_state1;
			}
			break;
		default:
			state = idle_sc;
			break;
	}
	
	switch(state){ //State Actions
		case idle_sc:
			break;
		case sm1_state1:
			if(current_position != previous_position){
				LCD_Cursor(current_position + 16);
				previous_position = current_position;
				//play cursor sound
				if(current_position == correct_pins[cp_array_pos])
				{
					set_PWM(440.0);
				}else{
					set_PWM(25);
				}
			}else{
				set_PWM(0);
			}
			break;
		default:
			break;
	}
	
	return state;
}	


enum GamePlayStates {idleGPS, playing, pressGPS, validateGPS, success, success_press};

int GamePlayLogic(int state){
	switch(state){ //Transitions
		case idleGPS:
			if(game_start == 0x01){
				state = playing;
			}
			break;
		case playing:
			if(game_over == 0x01){
				state = idleGPS;
				array_len = 3;
			}else if(cp_array_pos == array_len){
				state = success;
			}else if(button1){
				state = pressGPS;
			}
			break;
		case pressGPS:
			if(button1){
				state = pressGPS;
			}else{
				state = validateGPS;
			}
			break;
		case validateGPS:
			state = playing;
			break;
		case success:
			if(button1){
				state = success_press;
			}else{
				state = success;
			}
			break;
		case success_press:
			if(button1) {
				state = success_press; 
			}else{
				state = playing;
			} 
			break;
		default:
			state = idleGPS;
			break;
	}
	
	switch(state){//State Actions
		case idleGPS:
			//initialize // for array_len
			iter = 0;
			for(iter = 0; iter < array_len; iter++){
				correct_pins[iter] = generate_random();
			}
			break;
		case playing:
			PORTC = itoHEX(correct_pins[cp_array_pos]);
			break;
		case pressGPS:
			break;
		case validateGPS:
			if(current_position == correct_pins[cp_array_pos] && cp_array_pos < array_len){
				LCD_Cursor(current_position);
				LCD_WriteData('^');
				LCD_Cursor(current_position + 16);
				cp_array_pos++;
			}
			break;
		case success:
			if(win_disply == 0x00){
				LCD_DisplayString(1,sp);
				LCD_DisplayString(17,pbn);
				win_disply = 0x01;
				setarray = 0x00;
			}			
			break;
		case success_press:
			if(setarray == 0x00){
				LCD_ClearScreen();
				LCD_DisplayString(1, pins);
				LCD_Cursor(17);
				cp_array_pos = 0;
				array_len++;
				iter = 0;
				for(iter = 0; iter < array_len; iter++){
					correct_pins[iter] = generate_random();
					PORTC = itoHEX(iter);
				}
				setarray = 0x01;
				win_disply = 0x00;
			}
			break;
		default:
			break;
	}
	return state;
}

/*     Functions          */

void LP_LCD_init(unsigned long int GCD){
	TimerSet(GCD);
	TimerOn();
	ADC_init();
	PWM_on();
	LCD_init();
}



/*     Main          */

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x0F3; PORTB = 0x0C;
	//DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	
	
	unsigned long int SMTick1_calc = 500; // write to screen 
	unsigned long int SMTick2_calc = 50; // scroll
	unsigned long int SMTick3_calc = 50; // validate check
	
	unsigned long int tmpGCD = 1;
	tmpGCD = findGCD(SMTick1_calc, SMTick2_calc);
	tmpGCD = findGCD(tmpGCD, SMTick3_calc);
	
	unsigned long int GCD = tmpGCD;
	
	unsigned long int SMTick1_period = SMTick1_calc/GCD;
	unsigned long int SMTick2_period = SMTick2_calc/GCD;
	unsigned long int SMTick3_period = SMTick3_calc/GCD;
	
	//Declare an array of tasks
	static task task1, task2, task3;
	task *tasks[] = { &task1, &task2, &task3};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	// Task 1
	task1.state = -1;
	task1.period = SMTick1_period;
	task1.elapsedTime = SMTick1_period;
	task1.TickFct = &TitleScreen;
	
	// Task 2
	task2.state = -1;
	task2.period = SMTick2_period;
	task2.elapsedTime = SMTick2_period;
	task2.TickFct = &SM_Scroll;
	
	// Task 3
	task3.state = -1;
	task3.period = SMTick3_period;
	task3.elapsedTime = SMTick3_period;
	task3.TickFct = &GamePlayLogic;
	

	LP_LCD_init(GCD);
	
	unsigned short i;	
	while(1) {
		button1 = GetBit(~PINA, 1);
		// Scheduler code
		//set_PWM(400);
		for ( i = 0; i < numTasks; i++ ) {
			// Task is ready to tick
			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
				// Setting next state for task
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				// Reset elapsed time for next tick.
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}
}
