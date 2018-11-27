#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart_busy.h"

int main()
{
	int i;
	uart_init();
	sei();
	for(i = 0; i < 10; i++){
		uart_putstart("I love you. \n");
		uart_putstart("You love me. \n");
		uart_putstart("He loves her. \n");
	}
 	uart_putstart("End !!!\n");
 	while(1);
}
