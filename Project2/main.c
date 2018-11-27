#include <avr/io.h>
#include "led.h"
#include "uart_busy.h"

int main()
{
	char c;
	uart_init();
	for (c ='A'; c <='Z'; c++)
		uart_putchar(c);
 	uart_putchar('\n');

	uart_putstr("ABCD\n");
 	while(1);
}
