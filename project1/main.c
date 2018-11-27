#include <avr/io.h>
#include <util/delay.h>

#include "led.h"

int main()
{
	led_init();
	int i;
	while(1) {
		led_on_all();
		_delay_ms(300);
		for(i = 0; i < 8; i++){
			led_off(i);
			_delay_ms(300);
		}
		for(i = 7; i >= 0; i--){
			led_on(i);
			_delay_ms(300);
		}

 	}
 	return 0;
}
