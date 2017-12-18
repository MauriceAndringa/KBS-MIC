// 
// 
// 

#include "IR.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>


int main(void){
	
	//setting up timers and interrupts
	
	//set digital pin 11 as output
	DDRB |= 1<<5;
	//configure timer 1 ctc mode
	TCCR1B |= (1 << WGM12);
	// Enable CTC interrupt
	TIMSK1 |= (1 << OCIE1A); 
	// Enable global interrupts
	sei(); 
	// Set CTC compare value to 38kHz at 2.45MHz external resonator, with a prescaler of 8
	OCR1A = 7; 
	// Set up timer at Fcpu/8
	TCCR1B |= (1 << CS11);	
}

ISR(TIMER1_COMPA_vect)
{
	//set code to send here
}
