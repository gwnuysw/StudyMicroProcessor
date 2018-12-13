#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "task.h"
#include "timer.h"
#include "app.h"
#include "led.h"
#define MAX_TASK 16
struct task Task_q[MAX_TASK];
volatile int Task_f, Task_r;

void task_init(){
	Task_f = Task_r = 0;
}
int task_insert(struct task *tskp){
	if((Task_r + 1) % MAX_TASK == Task_f)
		return(0);
	Task_r = (Task_r + 1) % MAX_TASK;
	Task_q[Task_r] = *tskp;
	return(1);
}
int task_delete(struct task *tskp)
{
	if(Task_r == Task_f)
		return(0);
	Task_f = (Task_f + 1) % MAX_TASK;
	*tskp = Task_q[Task_f];
	return(1);
}
//there is no loop in task_cmd function
void task_cmd(void *arg){
	char buf[64], *cp0, *cp1, *cp2, *cp3;
	struct task task;
	int ms;
	if(gets(buf) == NULL){
		printf("$ ");
		return;
	}
	cp0 = strtok(buf, " \t\n\r");
	cp1 = strtok(NULL, " \t\n\r");
	cp2 = strtok(NULL, " \t\n\r");
	cp3 = strtok(NULL, " \t\n\r");

	if (cp0 == NULL){
		printf("!!!-111\n");
		tour_timer();
		return;
	}
	//using tsk_prime
	if(!strcmp(cp0, "prime")){
		task_prime(cp1);
	}
	//not using app_timer
	else if(!strcmp(cp0, "timer")){
		if(cp1 == NULL){
			printf("!!!-222\n");
			return;
		}
		ms = atoi(cp1)/256;
		if(!strcmp(cp2, "prime")){
			task.fun = task_prime;
			if(cp3){
				strcpy(task.arg, cp3);
			}
			else{
				strcpy(task.arg, "");
			}
			cli();
			insert_timer(&task, ms);
			sei();
		}
		else if(!strcmp(cp2, "led")){
			task.fun = task_led;
			if(cp3){
				strcpy(task.arg, cp3);
			}
			else{
				strcpy(task.arg,"");
			}
			cli();
			insert_timer(&task, ms);
			sei();
		}
		else{
			printf("!!!-333\n");
		}
	}else{
			printf("!!!-444\n");
	}
}
void task_prime(char *ap){
	int t=2000, count = 0, n;
	if(ap &&*ap) t = atoi(ap);
	for(n = 2; n <= t; n++){
		if(is_prime(n)){
			count++;
			printf("%d is a prime number!!!\n",n);
		}
 	}
	printf("count=%d\n",count);
}
