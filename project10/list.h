#ifndef LIST_H
#define LIST_H
	//extern struct node *Head;
	struct node {
		int data;
		struct node *link;
	};
	struct node *get_node();
	void insert_node_head(struct node *np);
	void insert_node_tail(struct node *np);
	void insert_node_ascn(struct node *np);
	void free_node(struct node *np);
	void tour_list();
	void free_list();
#endif
