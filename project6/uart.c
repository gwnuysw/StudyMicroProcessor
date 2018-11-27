#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>
#include "queue.h"
#include "uart.h"
 FILE Mystdout = FDEV_SETUP_STREAM (uart_putchar, NULL,_FDEV_SETUP_WRITE);
 char uart_busy;

 void uart_init()
 {
	 stdout = &Mystdout;
	 uart_busy = 0; // false
	 q_init();
	 UBRR0H = 0x00; UBRR0L = 0x07;
	 sbi(UCSR0A, U2X0); // UCSR)A |= (1 << U2X0);
	 sbi(UCSR0B, TXEN0);
	 sbi(UCSR0B, TXCIE0);
 }
int uart_putchar(char ch, FILE *stream)
{

	 if (ch == '\n')
	 	uart_putchar('\r', stream);
	 cli(); /* clear interrupt flag */
	 if (!uart_busy) {
	 	UDR0 = ch;
	 	uart_busy = 1;
	 }
	 else {
	 	while(q_insert(ch) == 0) {
	 		sei();
	 		_delay_us(100);
	 		cli();
	 	}
	 }
	 sei(); /* set interrupt flag */
	 return(1);
}
ISR(USART0_TX_vect)
{
	 char ch;
	 if ((ch = q_delete()) == 0)
	 	uart_busy = 0;
	 else
		UDR0 = ch;
} 
