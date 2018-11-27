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
 	char cmd[128], *cp, *ap;
	uart_init();
	sei();
	
	
	while(1) {
		printf("$");
		if (fgets(cmd, sizeof(cmd), stdin) == NULL)
 			break;
		if ((cp = strtok(cmd, "\n\r\t ")) == NULL) continue;
 		ap = strtok(NULL, "\n\r\t ");
 		if (!strcmp(cmd, "prime")) app_prime(ap);
 		else if (!strcmp(cmd, "list")) app_list(ap);
		else printf("Unknown command...\n");
	 } 
	printf("logout, good bye !!!\n");
 	while(1); 
}
