#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

struct timer *Thead = NULL;

void insert_timer(struct task *tskp, int ms){
	int total;
	struct timer *tp, *cp, *pp;
	//get a new node
	tp = get_timer();
	tp->task = *tskp;
	tp->time = ms;

	//insert into empty timer list
  if (Thead == NULL) {
		Thead = tp;
		tp->link = NULL;
		return;
	}

	pp = NULL;
	total = 0;
	//loop while cp is not null
	for (cp = Thead; cp; cp = cp->link) {
			total += cp->time;
			//if total is bigger than ms then pp point to right before cp
			if (total >= ms)
			//break at cp
				break;
      pp = cp;
  }
	//insert into head. second node time is subtracted by insertion node time
  if (pp == NULL) {
		cp->time -= tp->time;
		tp->link = cp;
	 	Thead = tp;
	}
	//insert into tail. last one is subtracted by total
	else if (cp == NULL) {
		tp->time -= total; // pp->time
		pp->link = tp;
		tp->link = NULL;
	}
	//insert into some where in the middle of list
	else {
		//re evaluate total time before cp
		total -= cp->time;
		//re calculate time of insertion and followed nodes
		tp->time -= total;
		cp->time -= tp->time;
		//insert into middle
		pp->link = tp;
		tp->link = cp;
	}
}
void tour_timer(){
 	struct timer *cp;
	int    total = 0;
  printf("\n");
	for (cp = Thead; cp != NULL; cp = cp->link) {
		total += cp->time;
		printf("-->%d(%d) ", cp->time, total);
	}
	printf("\n");
}
void free_timer(){
 	struct timer *cp;
 	for ( ;Thead != NULL; ){
		cp = Thead;
		Thead = cp->link;
		free(cp);
	}
}
struct timer *get_timer()
{
	struct timer *tp;
  tp = (struct timer *)malloc(sizeof(*tp));
	return(tp);
}
