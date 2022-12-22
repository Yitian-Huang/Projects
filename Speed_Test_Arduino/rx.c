#include "project.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void rx_init(void){
    UBRR0 = MYUBRR;// Set baud rate
    UCSR0B |= (1 << TXEN0 | 1 << RXEN0); // Enable RX and TX
    UCSR0C = (3 << UCSZ00); // Async., no parity, 1 stop bit, 8 data bits
    UCSR0B |= (1<<RXCIE0 );//Enable RX interrupt
}

//for RX 
ISR(USART_RX_vect){
    char temp =  UDR0;
    if(temp=='['){
        rx_start=1;
        rx_data[0]='\0';rx_data[1]='\0';rx_data[2]='\0';rx_data[3]='\0';
        rx_num=0;
        rx_end=0;
    }
    else if(rx_start==1){
        if(temp==']'){
            rx_start=0;
            if(rx_num!=0){
                rx_end=1;
            }
            else{
                rx_data[0]='\0';rx_data[1]='\0';rx_data[2]='\0';rx_data[3]='\0';
            }
        }
        else if(temp>'9'||temp<'0'){
            rx_start=0;
            rx_num=0;
            rx_data[0]='\0';rx_data[1]='\0';rx_data[2]='\0';rx_data[3]='\0';
            rx_end=0;
        }
        else{
            if(rx_num>3){
                rx_start=0;
                rx_data[0]='\0';rx_data[1]='\0';rx_data[2]='\0';rx_data[3]='\0';
                rx_num=0;
                rx_end=0;
            }
            else{
                rx_data[rx_num]=temp;
                rx_num++;
            }
        }
    }

}


//Send the speed by using the format[xxxx]
void tx_send(int speed){
    tx_char(91); //send [
    // while(speed>0){
    //     tx_char((speed%10)+'0');
    //     speed/=10;
    // }
    if(speed>1000){
        tx_char(speed/1000+'0');
        tx_char((speed/100)%10+'0');
        tx_char((speed/10)%10+'0');
        tx_char(speed%10+'0');
    }
    else if(speed>100){
        tx_char(speed/100+'0');
        tx_char((speed/10)%10+'0');
        tx_char(speed%10+'0');
    }
    else if(speed>10){
        tx_char(speed/10+'0');
        tx_char(speed%10+'0');
    }
    else{
        tx_char(speed+'0');
    }
    tx_char(93);//send ]
}

//Send a byte from TX
void tx_char(char ch)
{
    // Wait for transmitter data register empty
    while ((UCSR0A & (1<<UDRE0)) == 0) {}
    UDR0 = ch;
}