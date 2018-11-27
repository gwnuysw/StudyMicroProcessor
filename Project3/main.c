#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "led.h"
#include "uart_busy.h"


int is_prime(int  n) 
{
	int  i;
	for (i = 2; i <= n/2; i++)
		if ((n % i) == 0) return(0); /* FALSE */
	return(1);                        /* TRUE  */  
}
int main()
{
	int    i; 
 	
	uart_init();

	for (i = 3; i <= 2000; i++) {
	    if  (is_prime(i))  printf("%d  is a prime number !!!\n", i);
		else		       printf("%d is not a prime number !!!\n", i);   
	}
	while(1)
		;
}
