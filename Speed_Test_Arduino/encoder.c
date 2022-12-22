#include "project.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "lcd.h"

void encoder_init(void){
    //enable pin change interrupt
    PCMSK2 |=((1<<PCINT18)|(1<<PCINT19));
    //pull up resistor for rotary encoder
    PORTD |= ((1<<PD2)|(1<<PD3));
    unsigned char input = PIND;
	c = input&(1<<PD2);
	d = input&(1<<PD3); 

    if (!c && !d)
	old_state = 0;
    else if (!d && c)
	old_state = 1;
    else if (d && !c)
	old_state = 2;
    else
	old_state = 3;

    new_state = old_state;
	//Display initial max value on LCD at the beginning
	lcd_moveto(1,0);
	char bufs[17];
	snprintf(bufs, 17, "Max=%d", count);
	lcd_stringout(bufs);
}

//PIND interrupt for detecting change in rotary encoder, taken from lab 7
ISR(PCINT2_vect){
	// Read the input bits and determine A and B.
	unsigned char pin = PIND;
	c = pin&(1<<PD3);
	d = pin&(1<<PD2);
	
	// For each state, examine the two input bits to see if state
	// has changed, and if so set "new_state" to the new state,
	// and adjust the count value.
	if (old_state == 0) {
	    // Handle A and B inputs for state 0
		if(c&&!d){
			new_state =1;
			count++;
		}
		else if(d&&!c){
			new_state = 3;
			count--;
		}

	}
	else if (old_state == 1) {

	    // Handle A and B inputs for state 1
		if(d&&c){
			new_state =2;
			count++;
		}
		else if(!c&&!d){
			new_state = 0;
			count--;
		}

	}
	else if (old_state == 2) {

	    // Handle A and B inputs for state 2
		if(d&&!c){
			new_state =3;
			count++;
		}
		else if(!d&&c){
			new_state=1;
			count--;
		}

	}
	else {   // old_state = 3

	    // Handle A and B inputs for state 3
		if(!d&&!c){
			new_state=0;
			count++;
		}
		else if(c&&d){
			new_state=2;
			count--;
		}

	}
    if(count>99){
        count=99;
    }
    if(count<1){
        count=1;
    }

	// If state changed, update the value of old_state,
	// and set a flag that the state has changed.
	if (new_state != old_state) {
	    flag = 1;
	    old_state = new_state;
	}
}