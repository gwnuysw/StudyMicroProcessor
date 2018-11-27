#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <compat/deprecated.h>
#include "uart.h"
#include "queue.h"
#include "app.h"

int main()
{
 	char cmd[128], ch;
	int n = 0;
	uart_init();
	sei();
	printf("$ ");
	printf("$ ");
	while(1) {
		cli();
		ch = qi_delete();
		sei();
		if (ch) {
			if (ch == '\r') continue;
			if (ch == '\n') {	
				cmd[n] = 0;
				if (!strcmp(cmd, "app"))
					app_prime(2000);
				else printf("Merong...\n");
				n = 0;
				printf("$ ");
			}
			else
				cmd[n++] = ch;
		 }
	 } 
}
