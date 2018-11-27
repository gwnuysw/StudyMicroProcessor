#include <avr/io.h>
#include<stdio.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include "uart_busy.h"
int uart_putchar_1(char ch, FILE *stream);
int uart_putchar_2(char ch, FILE *stream);
FILE Mystdout =  FDEV_SETUP_STREAM (uart_putchar_2, NULL,_FDEV_SETUP_WRITE);

void uart_init()
{
	stdout = &Mystdout; 
	UBRR0H = 0x00; UBRR0L = 0x07; // 115.2Kbps
	sbi(UCSR0A, U2X0); // 115.2Kbps
	sbi(UCSR0B, TXEN0); // TX enable
}
int uart_putchar(char ch)
{
	if (ch == '\n')
		uart_putchar('\r');
	_delay_ms(100);
	UDR0 = ch;
 	return(1);
}
int uart_putstr(char *sp)
{
	for ( ; *sp; sp++)
 		uart_putchar(*sp);
 	return(1);
} 
int uart_putchar_1(char ch, FILE *stream) 
{
	 if (ch == '\n')
	     uart_putchar_1('\r', stream);
	 _delay_ms(5);
	 UDR0 = ch;
	 return(1);
}
int uart_putchar_2(char ch, FILE *stream) 
{
	 if (ch == '\n')
	     uart_putchar_1('\r', stream);
	 while(!(UCSR0A & (1 << UDRE0)))
	 ;
	 UDR0 = ch;
	 return(1);
}
