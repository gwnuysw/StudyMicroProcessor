#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <compat/deprecated.h>
#include <stdlib.h>
#include "uart.h"
#include "queue.h"
#include "app.h"
#include "list.h"
#include "timer.h"
int main()
{
 	char cmd[128], *cp, *ap;
  int n = 0;

	uart_init();
	sei();
	while(1) {
		printf("$");
		if (fgets(cmd, sizeof(cmd), stdin) == NULL)
 		 break;
		if ((cp = strtok(cmd, "\n\r\t ")) == NULL)
      continue;
    //cp is comand, ap is argument
 		ap = strtok(NULL, "\n\r\t ");
    //$prime 100
 		if (!strcmp(cp, "prime"))
      app_prime(ap);
    //$list h 50
 		else if (!strcmp(cp, "list"))
      app_list(ap);
    //$timer
		else if (!strcmp(cp, "timer"))
      app_timer(ap);
		else
      printf("Unknown command...\n");
	}
	printf("logout, good bye !!!\n");
 	while(1);
}
