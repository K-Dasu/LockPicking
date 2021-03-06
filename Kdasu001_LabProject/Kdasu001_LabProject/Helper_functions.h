/*Keshav Dasu kdasu001@ucr.edu:
* Lab Section 022:
* Assignment: Lab Project
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/
#include <stdlib.h>

#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_


unsigned char generate_random(){
		unsigned char pick = rand() % 16 + 1;
		return pick;
}

char calc_postion(short max, short adc_value)
{
	short spacing = max / 16;
	
	if(adc_value > max){
		return 16;
	}else if(adc_value > (max - (1 * spacing))){
		return 15;
	}else if(adc_value > (max - (2 * spacing))){
		return 14;
	}else if(adc_value > (max - (3 * spacing))){
		return 13;
	}else if(adc_value > (max - (4 * spacing))){
		return 12;
	}else if(adc_value > (max - (5 * spacing))){
		return 11;
	}else if(adc_value > (max - (6 * spacing))){
		return 10;
	}else if(adc_value > (max - (7 * spacing))){
		return 9;
	}else if(adc_value > (max - (8 * spacing))){
		return 8;
	}else if(adc_value > (max - (9 * spacing))){
		return 7;
	}else if(adc_value > (max - (10 * spacing))){
		return 6;
	}else if(adc_value > (max - (11 * spacing))){
		return 5;
	}else if(adc_value > (max - (12 * spacing))){
		return 4;
	}else if(adc_value > (max - (13 * spacing))){
		return 3;
	}else if(adc_value > (max - (14 * spacing))){
		return 2;
	}else if(adc_value > (max - (15 * spacing))){
		return 1;
	}else{
		return 0;
	}
	
}
//528
char get_position(char array_len, short adc_val)
{
	if(array_len >= 17){
		return calc_postion(190, adc_val);
	}else if(array_len >= 15){
		return calc_postion(228, adc_val);
	}else if(array_len >= 11){
		return calc_postion(368, adc_val);
	}else if(array_len >= 7){
		return calc_postion(190, adc_val);
	}else if(array_len >= 3){
		return calc_postion(528, adc_val);
	}
	
	return 1;
}

void display_level(unsigned char level){
	if(level == 3){
		LCD_WriteData('1');
	}else if(level == 4){
		LCD_WriteData('2');
	}else if(level == 5){
		LCD_WriteData('3');
	}else if(level == 6){
		LCD_WriteData('4');
	}else if(level == 7){
		LCD_WriteData('5');
	}else if(level == 8){
		LCD_WriteData('6');
	}else if(level == 9){
		LCD_WriteData('7');
	}else if(level == 10){
		LCD_WriteData('8');
	}else if(level == 11){
		LCD_WriteData('9');
	}else if(level == 12){
		LCD_DisplayString(17,"level 10");
	}else if(level == 13){
		LCD_DisplayString(17,"level 11");
	}else if(level == 14){
		LCD_DisplayString(17,"level 12");
	}else if(level == 15){
		LCD_DisplayString(17,"level 13");
	}else if(level == 16){
		LCD_DisplayString(17,"level 14");
	}else{
		LCD_DisplayString(17,"Wow Congrats..!!");
	}		
}

char itoHEX(unsigned char i)
{	
	if(i == 16){
		return 0x10;
	}else if(i == 15){
		return 0x0F;
	}else if(i == 14){
		return 0x0E;
	}else if(i == 13){
		return 0x0D;
	}else if(i == 12){
		return 0x0C;
	}else if(i == 11){
		return 0x0B;
	}else if(i == 10){
		return 0x0A;
	}else if(i == 9){
		return 0x09;
	}else if(i == 8){
		return 0x08;
	}else if(i == 7){
		return 0x07;
	}else if(i == 6){
		return 0x06;
	}else if(i == 5){
		return 0x05;
	}else if(i == 4){
		return 0x04;
	}else if(i == 3){
		return 0x03;
	}else if(i == 2){
		return 0x02;
	}else if(i == 1){
		return 0x01;
	}else if(i == 0){
		return 0x15;
	}else{
		return 0x1F;
	}
	
}

#endif /* HELPER_FUNCTIONS_H_ */