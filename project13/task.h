#ifndef TASK_H
#define TASK_H
struct task{
	void (*fun)(void*);
	char arg[8];
};
volatile int Task_f, Task_r;
void task_prime(char *ap);
void task_init();
int task_insert(struct task *tskp);
int task_delete(struct task *tskp);
void task_cmd(void *arg);
void  task_tc1047a(void *arg);
void task_tc77(void *arg);
#endif
