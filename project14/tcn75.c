#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <compat/deprecated.h>
#include <stdlib.h>
#include <util/twi.h>
#include "tcn75.h"


 void twi_init()
 {
 cbi(DDRD, 0); sbi(PORTD, 0); // SCL ? 1 : enable pull-up register
 cbi(DDRD, 1); sbi(PORTD, 1); // SDA ? 1 : enable pull-up register
 TWSR = 0x00; // prescaler value==40==1
 TWBR = (F_CPU)/(200*1024L-16)/(2*40
); // 2.5us==400KHz?200KHz
 sbi(DDRH, 1); cbi(PORTH, 1); // A0 ? 0 TCN75 id bits
 sbi(DDRH, 3); cbi(PORTH, 3); // A1 ? 0
 sbi(DDRH, 5); cbi(PORTH, 5); // A2 ? 0
 }
void tcn75_i2c_init()
{
	sbi(DDRD, SDA); sbi(PORTD, SDA); // output, hi
 	sbi(DDRD, SCL); sbi(PORTD, SCL); // output, hi
 	sbi(DDRH, 1); cbi(PORTH, 1); // output , A0 
 	sbi(DDRH, 3); cbi(PORTH, 3); // output , A1 
 	sbi(DDRH, 5); cbi(PORTH, 5); // output , A2 
}
