#include <stdlib.h>
# include <stdio.h>
# include "list.h"

//special global pointer for list head
struct node *Head = NULL;

struct node *get_node()
{
	struct node *cp;
	cp = (struct node *)malloc(sizeof(struct node));
	return(cp);
}
void free_node(struct node *np)
{
	free(np);
}
void insert_node_head(struct node *np)
{
	if (!Head) {
		Head = np;
		np->link = NULL;
	}
 	else {
 		np->link = Head;
 		Head = np;
	}
}
void insert_node_tail(struct node *np)
{
	struct node *cp;
	if (!Head){
		Head = np;
	}
	else {
		//cp point to tail of list
		for (cp = Head; cp->link != NULL; cp = cp->link)
			;
		cp->link = np;
	}
	np->link = NULL;
}
void insert_node_ascn(struct node *np)
{
	struct node *cp, *pp;
	if (!Head) {
		Head = np;
		np->link = NULL;
	}
	else {
		//pp always point to right before of cp
		//loop while data of new node is smaller than data of cp
		for (cp = Head, pp = NULL; (cp != NULL) && (cp->data < np->data);pp = cp, cp = cp->link)
			;
		//insert new node to HEAD. in this case data of new node is smallest one
 		if (pp == NULL) {
			np->link = Head;
			Head = np;
		}
		//insert between pp and cp
		else {
			np->link = pp->link;
			pp->link = np;
		}
	}
}
void tour_list()
{
	struct node *cp;
	printf("\n");
	for (cp = Head; cp != NULL; cp = cp->link)
		printf("-->%c ", cp->data);
	printf("\n");
}
void free_list()
{
	struct node *cp;
	//Head point to second node of list. cp point to first node of list and delete cp
	for ( ; Head != NULL; ) {
		cp = Head;
		Head = cp->link;
		free_node(cp);
	}
}
