#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "task.h"
#include "timer.h"
#include "app.h"
#include "led.h"
#include "adc.h"
#include "spi.h"
#include "tcn75.h"
#define MAX_TASK 16

 #define TC77_WAIT_HI 1
 #define TC77_WAIT_LO 2

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
void task_cmd(void *arg){
	char buf[64], *cp0, *cp1, *cp2, *cp3;
	struct task task;
	int ms;
	if(gets(buf) == NULL){
		printf("$ "); return;
	}
	cp0 = strtok(buf, " \t\n\r");
	cp1 = strtok(NULL, " \t\n\r");
	cp2 = strtok(NULL, " \t\n\r");
	cp3 = strtok(NULL, " \t\n\r");

	if (cp0 == NULL){
		printf("!!!-111\n");
		tour_timer();
		printf("$ "); 
		return;
	}
	if(!strcmp(cp0, "prime")){
		task_prime(cp1);
	}
	else if (!strcmp(cp0, "tc1047a"))
		task_tc1047a(""); 
	else if (!strcmp(cp0, "tc77"))
		task_tc77("");
	else if (!strcmp(cp0, "tcn75_i2c"))
 		task_tcn75_i2c("");
	else if (!strcmp(cp0, "tcn75_twi"))
 		task_tc75_twi("");
	else if(!strcmp(cp0,"timer")){
		if(cp1 == NULL){
			printf("!!!-222\n");
			printf("$ "); 
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
		else if (!strcmp(cp2, "tc77")){
			task.fun = task_tc77;
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
		else{
			printf("!!!-333\n");
		}
	
	}else{
			printf("!!!-444\n");
		}
		printf("$ ");

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
 void  task_tc1047a(void *arg) {
 	int   value; 
 
    if (!strcmp(arg, ""))   // called from task_cmd or timer task
		adc_start();
	else  {                                // called from ISR()
		printf("value : %d",atoi(arg));
	    value = atoi(arg) * (1.1/1024) * 1000;
		value = (value - 500) / 10;
		printf("task_tc1047a() : current temperature ? %d degree.\n", value); 
	}
}
void task_tc77(void *arg){
	static uint8_t state;
	 static uint16_t value;

	 if (!strcmp(arg, "")) {
		 state = TC77_WAIT_HI;
		 spi_select();
		 spi_write(0x00);
	 }
	 else {
		 switch(state) {
			 case TC77_WAIT_HI :
				 value = atoi(arg) << 8; state = TC77_WAIT_LO; spi_write(0x00);
				 break;
			 case TC77_WAIT_LO:
				 value |= atoi(arg); value = (value >> 3) * 0.0625;
				 spi_release();
				printf("task_tc77() : current_temperature ? %d degree.\n", value);
				 break;
			 default:
				 spi_release();
				 printf("task_tc77() : unexpecetd state in task_tc77...\n");
		 }
	 }
}
void task_tcn75_i2c(void *arg)
{
 uint16_t value;

 i2c_tcn75_trans_start();
 if (i2c_tcn75_write_one_byte(0x90) != 0) { // address + write_operation
 i2c_tcn75_trans_stop(); printf("task_tcn75_i2c() : SLA+W write fail・\n");
 return;
 }
 if (i2c_tcn75_write_one_byte(0x00) != 0) { // pointer(TEMP)
 i2c_tcn75_trans_stop(); printf("task_tcn75_i2c() : pointer write fail・\n");
 return;
 }
 i2c_tcn75_trans_start(); // Repeat Start
 if (i2c_tcn75_write_one_byte(0x91) != 0) { // address + read_operation
 i2c_tcn75_trans_stop(); printf("task_tcn75_i2c() : SLA+R write fail・\n");
 return;
 } // read TEMP register
 value = ((i2c_tcn75_read_one_byte(0) << 8) | i2c_tcn75_read_one_byte(1)) >> 7;
 i2c_tcn75_trans_stop();
 value = value >> 1; // value = value * 0.5
 printf("task_tcn75_i2c() : current_temperature ? %d degree.\n", value);
}
void task_tc75_twi(void *arg)
 {
 	uint16_t value; uint8_t hbyte, lbyte;

	 if (twi_start() != TW_START) { 
 		twi_stop(); 
		printf("task_tc75: Start error・\n");
		return; 
	}
 	if (twi_write_one_byte(0x90) != TW_MT_SLA_ACK) { // address + write_operation
 		twi_stop(); 
		printf("task_tc75() : SLA+W write fail・\n"); 
		return;
 	}
 	if (twi_write_one_byte(0x00) != TW_MT_DATA_ACK) { // pointer(TEMP)
 		twi_stop(); printf("task_tc75() : pointer write fail・\n"); return;
	}
 	if (twi_start() != TW_REP_START) {
		twi_stop(); 
		printf("Repeat Start error・\n"); 
		return; 
	}
	 if (twi_write_one_byte(0x91) != TW_MR_SLA_ACK) { // address + read_operation
	 	twi_stop(); 
		printf("task_tc75() : SLA+R write fail・\n"); 
		return;
	 }
 	if (twi_read_one_byte(&hbyte, 1) != TW_MR_DATA_ACK) { // read hi_byte of TEMP register
 		twi_stop(); 
		printf("task_tc75() : read hi_byte fail・\n"); 
		return;
 	}
 	if (twi_read_one_byte(&lbyte, 0) != TW_MR_DATA_NACK) { // read lo_byte of TEMP register
 		twi_stop(); 
		printf("task_tc75()_1 : read lo_byte fail・\n"); 
		return;
 	}
 	twi_stop();
 	value = ((hbyte << 8 | lbyte) >> 7) >> 1; // value = value * 0.5
 	printf("task_tc75()_1 : current_temperature ? %d degree.\n", value);
 }
