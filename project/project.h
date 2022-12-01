#define FOSC 16000000 // Clock frequency
#define BAUD 9600 // Baud rate used
#define MYUBRR (FOSC/16/BAUD-1) // Value for UBRR0

//for speed sensing
enum states { S0, S1 };
extern volatile unsigned long cnt;
extern volatile unsigned char a, b;
extern volatile unsigned char changed ;  // Flag for state change 
extern volatile char state ;
extern volatile unsigned long speed;

//for rotary encoder
extern volatile unsigned char new_state, old_state;
extern volatile unsigned char flag ;  // Flag for state change
extern volatile int count; 		// Count to display
extern volatile unsigned char c, d;
extern char bufs[17];

//for buzzer
extern volatile int buzz ;

//for RX 
extern volatile char rx_data[5];
extern volatile char rx_start;
extern volatile int rx_num;
extern volatile char rx_end;
extern int num1;

//functions to send data through rx
extern void tx_char(char ch);
extern void tx_send(int speed);