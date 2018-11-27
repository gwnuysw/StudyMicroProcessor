#include <stdio.h>
struct task {
	void   (*fun)(void *);
	char    arg[8];
};
struct timer {  // node for timer
	int    time;
	struct task task;
	struct timer   *link;
};

extern struct timer *Thead;
void insert_timer(struct task *tskp, int ms);
struct timer *get_timer();
void tour_timer(), free_timer();

void  app_timer(char *ap);
