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
#include <util/delay.h>
#include "timer.h"
#include "led.h"
void  adc_init() {
	cbi(DDRF, PF0);   // make input PF0(=ADC0) GPIO
	ADMUX = 0x80 | 0x00; // Ref. : 1.1v, Port : PF0
}
void adc_start(){
	sbi(ADCSRA, ADEN);    // ADC enable
	_delay_us(120);
	sbi(ADCSRA, ADIE);     // Interrupt Enable
	sbi(ADCSRA, ADSC);    // Start conversion
}
ISR(ADC_vect)  {
 	struct  task  task;
	uint16_t       data;
  data = ADCW & 0x03ff;
	cbi(ADCSRA, ADEN);
	task.fun = task_tc1047a;
	sprintf(task.arg, "%d", data);
  task_insert(&task);
}
