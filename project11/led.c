#include <avr/io.h>
#include "task.h"
#include "timer.h"

static uint8_t Leds;

void led_init() {
	DDRL = PORTL = 0xff;
}
void led_on_all(void) {
	Leds = PORTL = 0x00;
}
void led_off_all(void) {
	 Leds = PORTL = 0xff;
}
void led_on(uint8_t led_no) {
	Leds &= ~(1 << led_no);
	PORTL = Leds;
}
void led_off(uint8_t led_no) {
	Leds |= (1 << led_no);
	PORTL = Leds;
}
void led_set(uint8_t led_mask) {
	Leds = ~led_mask;
	PORTL = Leds;
} 

/*void task_led(){
	struct task task;
	task.fun = onoff5;
	task.arg = "";
	struct timer ledturn;

}
void onoff5(){
	static int flag = 0;
	if(flag = 0){
		led_on_all();
		flag = 1;
	}
	else{
		led_off_all();
		flag = 0;
	}
}*/
void task_led(char *ap){
	struct task task;
	static int tag;
	int ms = 1024*5;
	if(ap&&*ap)
		ms = atoi(ap);
	
	if(tag){
		led_on_all();
		tag = 0;
	}
	else{
		led_off_all();
		tag = 1;
	}
	task.fun=task_led;
	sprintf(task.arg,"%d",ms);
	insert_timer(&task, ms/256);
}
