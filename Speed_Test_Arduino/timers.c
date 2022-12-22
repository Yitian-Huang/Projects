#include "project.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void timer2_init(void){
    TCCR2A |= (0b11 << WGM00);  // Fast PWM mode, modulus = 256
    TCCR2A |= (0b10 << COM0A0); // Turn D11 on at 0x00 and off at OCR2A
    OCR2A = 35;                // Initial position at 0
    TCCR2B |= (0b111 << CS20);  // Prescaler = 1024 for 16ms period
}

void timer1_init(void){
    // Set to CTC mode
    TCCR1B |= (1 << WGM12);
    // Enable Timer Interrupt
    TIMSK1 |= (1 << OCIE1A);
    // prescalar=1024 4s = 62500/(16MHz/1024)
    OCR1A = 62500;
}
void timer0_init(void){
    // Set to CTC mode
    TCCR0B |= (1 << WGM02);
    // Enable Timer Interrupt
    TIMSK0 |= (1 << OCIE0A);
    //prescalar = 256, 0.002s = 125/(16MHz/256)
    OCR0A = 125;

}
//Timer1 interrupt to detect 4 seconds have reached.
ISR(TIMER1_COMPA_vect){
    TCCR1B &= ~((1 << CS10)|(1<<CS12));
    PORTC &= ~(1<<PC3);
	changed = 3;
    state=S0;
	
}

//Timer0 interrupt for buzzer
ISR(TIMER0_COMPA_vect){
    buzz++;
    if(PORTC&(1<<PC5)){
        PORTC &= ~(1<<PC5);
    }
    else{
        PORTC |= (1<<PC5);
    }
    if(buzz==500){
        buzz=0;
        TCCR0B &= ~(1 << CS02);
        TCNT0=0;
    }
}