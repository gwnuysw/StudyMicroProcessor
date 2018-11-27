#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <compat/deprecated.h>
#include <stdlib.h>
#include "task.h"
#include "uart.h"
#include "app.h"
#include "list.h"

#include "timer.h"
#include "led.h"

int main()
{
 /*	char cmd[128], *cp, *ap;
//	int tsec;
	uart_init();
	timer_init();
	led_init();
	sei();	
	while(1) {
		while(1){
			tsec = exe_time;
			while(tsec == exe_time);
			app_time();
		}
		printf("$");
		if (fgets(cmd, sizeof(cmd), stdin) == NULL)
 			break;
		if ((cp = strtok(cmd, "\n\r\t ")) == NULL) continue;
 		ap = strtok(NULL, "\n\r\t ");
 		if (!strcmp(cp, "prime")) app_prime(ap);
 		else if (!strcmp(cp, "list")) app_list(ap);
		else if (!strcmp(cp, "timer")) app_timer(ap);
		else if (!strcmp(cp, "time")) app_time();
		else printf("Unknown command...\n");
	 } 
	printf("logout, good bye !!!\n");
 	while(1); */

	int tag;
	struct task task;
	led_init();
	uart_init();
	task_init();
	timer_init();

	printf("$ ");
	while(1){
		cli();
		tag = task_delete(&task);
		sei();
		if(tag)
			((*task.fun))(task.arg);
	}
}

