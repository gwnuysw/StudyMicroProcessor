#ifndef TIMER_H
#define TIMER_H
	#include <stdio.h>
	struct task {
		void   (*fun)(void *);
		char    arg[8];
	};
  // node for timer
	struct timer {
		int    time;
		struct task task;
		struct timer   *link;
	};

	//extern struct timer *Thead;
	struct timer *get_timer();
	
	void insert_timer(struct task *tskp, int ms);
	void tour_timer();
	void free_timer();
#endif
