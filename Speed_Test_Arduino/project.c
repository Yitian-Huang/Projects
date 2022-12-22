
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "lcd.h"
#include "timers.h"
#include "encoder.h"
#include "project.h"
#include "rx.h"


void tx_char(char ch);
void tx_send(int speed);

//for speed sensing

volatile unsigned long cnt=0;
volatile unsigned char a, b;
volatile unsigned char changed = 0;  // Flag for state change 
volatile char state = S0;
volatile unsigned long speed;

//for rotary encoder
volatile unsigned char new_state, old_state;
volatile unsigned char flag = 0;  // Flag for state change
volatile int count = 1;		// Count to display
volatile unsigned char c, d;
char bufs[17];

//for buzzer
volatile int buzz = 0;

//for RX 
volatile char rx_data[5]="";
volatile char rx_start=0;
volatile int rx_num=0;
volatile char rx_end=0;
int num1=0;

int main(void){
    //initialization
	lcd_init();
	DDRC |= ((1<<PC3)|(1<<PC5));
    DDRB |= (1<<PB3);
    DDRB |= ((1<<PB4)|(1<<PB5));
    //pullup resistor for two sensors
	PORTC |= (1<<PC1|1<<PC2);
    
    //tri-state gate
    DDRC |=(1<<PC4);
    PORTC &= ~(1<<PC4);

    //Timer init
    timer0_init();
    timer1_init();
    timer2_init();

    //enable pin change interrupt
    PCICR |= ((1<<PCIE1)|(1<<PCIE2));
	PCMSK1 |= ((1<<PCINT9)|(1<<PCINT10));
    //RX TX init
    rx_init();
    
    sei();
    lcd_writecommand(0x01);
    //eeprom init
    unsigned char x;
    x = eeprom_read_byte((void *) 100);
    if(x>99){
        x=1;
    }
    count=x;
    // Write a spash screen to the LCD
	lcd_writecommand(0x01);
    lcd_moveto(0,0);
    char buf[17];
    snprintf(buf, 17, "EE%d Project",109);
    lcd_stringout(buf);
    lcd_moveto(1,0);
    lcd_stringout("Yitian Huang");
    _delay_ms(1000);
    lcd_writecommand(0x01);

    //Initialize rotary encoder
    encoder_init();

    while(1){

        if(changed==1){
            changed =0;
            lcd_moveto(0,0);
            lcd_stringout("timing...       ");

        }
        //Stop sensor triggered before 4s
        else if (changed==2){
            changed =0;
            char buffer[17];
            snprintf(buffer, 17,"%5ldms = %4ld.%ld",cnt,speed/10,speed%10);
            lcd_moveto(0,0);
            lcd_stringout(buffer);
            tx_send(speed);
            if(speed/10>count){
                TCCR0B |= (1 << CS02);
            }
            if(speed/10>100){
                OCR2A=12;
            }
            else{
                int temp=speed/10;
                int reduc = (23*temp)/100;
                OCR2A=35-reduc;

            }
            if(num1!=0){
                if(speed>num1){
                    PORTB |= (1<<PB5);
                    PORTB &= ~(1<<PB4);
                }
                else if (speed<num1){
                    PORTB |= (1<<PB4);
                    PORTB &= ~(1<<PB5);
                }
                else{
                    PORTB  &= ~(1<<PB5);
                    PORTB &= ~(1<<PB4);
                }
            }
        }
        //Over 4s, expired
        else if(changed ==3){
            changed =0;
            lcd_moveto(0,0);
            lcd_stringout("Max time expired");
        }
        //Change in max speed value
        if(flag==1){
            flag=0;
            eeprom_update_byte((void *) 100, count);
            lcd_moveto(1,0);
            snprintf(bufs, 17, "Max=%2d", count);
            lcd_stringout(bufs);
        }
        if(rx_end==1){
            rx_end=0;
            sscanf(rx_data, "%d", &num1);
            lcd_moveto(1,11);
            snprintf(bufs, 17,"%3d.%d",num1/10,num1%10);
            lcd_stringout(bufs);
            rx_data[0]='\0';rx_data[1]='\0';rx_data[2]='\0';rx_data[3]='\0';
            rx_num=0;
        }
    }



}
//Detect PINC change(detect change in sensors)
ISR(PCINT1_vect){
    unsigned char pin = PINC;
	a = pin&(1<<PC1);
	b = pin&(1<<PC2);

    //start sensor triggered when at rest, start timing
    if(state==S0 && !a){
        TCNT1=0;
        TCCR1B |= ((1 << CS12)|(1<<CS10));
        PORTC |=(1<<PC3);
        state = S1;
        changed=1;
    }
    //stop sensor triggered when timing, stop timing
    else if(state == S1 && !b){
        cnt = TCNT1;
        cnt = cnt *1000/15625;
        TCCR1B &= ~((1 << CS10)|(1<<CS12));
        speed = 50800/(cnt);
        PORTC &= ~(1<<PC3);
        state = S0;
        changed=2;
    }
    
}






