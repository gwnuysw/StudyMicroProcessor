#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "timer.h"
extern volatile int exe_time;

int is_prime(int n)
{
 int i;
 for (i = 2; i <= n/2; i++)
	 if ((n % i) == 0)
	 	return(0);
 return(1);
}
void app_prime(char *ap)
{
 int n = 2000, count = 0, t;
 if (ap) t = atoi(ap);
 for (n = 2; n <= t; n++) {
 	if (is_prime(n)) {
	 	count++;
	 	printf("%d is a prime number !!!\n", n);
	 }
 }
 printf("count=%d\n", count);
}
void  app_timer(char *ap)  {
  char buf[8];
  int ms;
  struct task  tsk;
  //>>5000
  //typing end with ctl + z
  while(1) {
   printf(">> ");
   if (fgets(buf, 8, stdin) == NULL || (ms = atoi(buf)) == 0)
     break;
   insert_timer(&tsk, ms);
  }
  tour_timer();
  free_timer();
}
void app_time(){
	printf("MIN : SEC\n");
	printf("%.2d : %.2d\n", exe_time/60, exe_time%60);
}
