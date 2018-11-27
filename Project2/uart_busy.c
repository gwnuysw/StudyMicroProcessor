#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include "uart_busy.h"

void uart_init()
{
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
