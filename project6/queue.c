# include "queue.h"

#define Q_SIZE 256

char q[Q_SIZE];
int f, r;
void q_init()
{
	f = r = 0;
}
int q_insert(char ch)
{
 	if ((r + 1) % Q_SIZE == f)
 		return(0); // full
	r = (r + 1) % Q_SIZE;
	q[r] = ch;
	return(1);
}
int q_delete()
{
 if (r == f)
 	return(0); // empty
 f = (f + 1) % Q_SIZE;
 	return(q[f]);
}
