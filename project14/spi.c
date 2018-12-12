#include <stdio.h>
#include<avr/io.h>
#include<avr/interrupt.h>
#include<stdlib.h>
#include <compat/deprecated.h>
#include"spi.h"
#include "task.h"
void spi_init(){
	sbi(DDRB, 0);
	sbi(DDRB, 1);
	sbi(DDRB, 2);
	cbi(DDRB, 3);

	sbi(SPSR, SPI2X);
	SPCR = ( (1 << MSTR) | (1 << SPE) | (1 << SPIE) ); 
	//sbi(SPCR, MSTR);
	//sbi(SPCR, SPE);
	//sbi(SPCR, SPIE);
}
void spi_select() { cbi(PORTB, 0); }
void spi_release() { sbi(PORTB, 0); }
void spi_write(uint8_t data) { SPDR = data; }
ISR(SPI_STC_vect)
 {
	 struct task task;
	 uint8_t data;
	 data = SPDR;

	 task.fun = task_tc77;
	 sprintf(task.arg, "%d", data);
	 task_insert(&task);
 } 
