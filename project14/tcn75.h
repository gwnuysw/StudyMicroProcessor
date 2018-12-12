#ifndef TCN75_H
#define TCN75_H
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <compat/deprecated.h>
#include <stdlib.h>
#include <util/delay.h>
#define delay_2nop() asm volatile("nop"::);
#define delay_us _delay_us
#define SCL 0
#define SDA 1
#include <util/twi.h> 
void tcn75_12c_init();
 void twi_init();

inline void i2c_tcn75_trans_start()
 {
 cbi(PORTD, SCL); // SCL ? L
 sbi(PORTD, SDA); delay_2nop(); // SDA ? H
 sbi(PORTD, SCL); delay_2nop(); // SCL ? H
 cbi(PORTD, SDA); delay_us(1); // SDA ? L
 }
inline void i2c_tcn75_trans_stop()
 {
 cbi(PORTD, SCL); // SCL ? L
 cbi(PORTD, SDA); delay_2nop(); // SDA ? L
 sbi(PORTD, SCL); delay_2nop(); // SCL ? H
 sbi(PORTD, SDA); delay_us(1); // SDA ? H
 }
inline uint8_t i2c_tcn75_write_one_byte(uint8_t data)
 {
 	uint8_t mask, ack;
 	sbi(DDRD, SDA); // SDA output(write)
 	for (mask = 0x80; mask; mask = mask >> 1) {
 		cbi(PORTD, SCL); delay_2nop(); // SCL ? L
 		if (mask & data) sbi(PORTD, SDA); // SDA ? 1
 		else cbi(PORTD, SDA); // SDA ? 0
 		delay_us(1);
 		sbi(PORTD, SCL); delay_us(1); // SCL ? H
 	}
 	cbi(DDRD, SDA); // SDA input(read)

 	cbi(PORTD, SCL); delay_us(1); // SCL ? L
 	sbi(PORTD, SCL); delay_us(1); // SCL ? H
 	ack = PIND & (1 << SDA); // ack ? SDA read ack of TC75

 	return(ack);
 }
inline uint8_t i2c_tcn75_read_one_byte(uint8_t ack)
 {
	 uint8_t i, data = 0;
	 cbi(DDRD, SDA); // SDA input

	 for (i = 0; i < 8; i++) {
		 cbi(PORTD, SCL); delay_us(1); // SCL ? L
		 sbi(PORTD, SCL); delay_us(1); // SCL ? H
		 data = (data << 1);
		 if (PIND & (1 << SDA)) 
		 	data = data | 0x01; // data ? SDA
	 }
	 sbi(DDRD, SDA); // SDA output, for sending ack
	 cbi(PORTD, SCL); delay_2nop(); // SCL ? L

	 if (ack) 
	 	sbi(PORTD, SDA); 
	 else 
	 	cbi(PORTD, SDA); // SDA ? 0 or 1 (Ack or Nck)
	 delay_us(1);
	 sbi(PORTD, SCL); delay_us(1); // SCL ? H

	 return(data);
 }
 inline uint8_t twi_start()
 {
	 TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) ; // clear TWINT, set START flag
	 while (!(TWCR & (1<<TWINT))) ; // wait transmission completion
	 return(TW_STATUS); // TWSR & 0xf8 ? 0x08 or 0x10
 }
 inline uint8_t twi_write_one_byte(uint8_t data)
 {
	 TWDR = data;
	 TWCR = ((1<<TWINT) | (1<<TWEN)); // clear TWINT and TWSTA, keep TWEN
	 while (!(TWCR & (1<<TWINT))); // wait transmission completion
	 return(TW_STATUS); // TWSR & 0xf8 ? 0x18, 0x20, 0x28,0x30
 }
 inline uint8_t twi_read_one_byte(uint8_t *data, uint8_t enack)
 {
	 TWCR = (1<<TWINT) | (enack<<TWEA) | (1<<TWEN) ; // clear TWINT, keep TWEN
	 while (!(TWCR & (1<<TWINT))) ; // wait reception completion
	 *data = TWDR;
	 return(TW_STATUS); // TWSR & 0xf8 ? 0x50, 0x58
 }
 inline void twi_stop()
 {
 	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN) ; // clear TWINT, keep TWEN
 }
#endif
