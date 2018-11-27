#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart_busy.h"

int main()
{
	int i, j;
	char buf[4] = {0};
 	uart_init();
 	sei();
 	for(i = 0; i < 3; i++){
		for(j = 'A'; j <='Z'; j++){
			buf[0] = j;
			uart_putstart(buf);
		}
		uart_putstart("\n");
	}
 	while(!txend);
 	uart_putstart("End !!!\n");
 	while(1);
}
