#ifndef TIMER_H
#define TIMER_H
struct timer {  // node for timer
	int    time;
	struct task task;
	struct timer   *link;
}; 

extern struct timer *Thead;
void insert_timer(struct task *tskp, int ms);
struct timer *get_timer();
void tour_timer(), free_timer();
void timer_init();
void timer_expire(void);
#endif
