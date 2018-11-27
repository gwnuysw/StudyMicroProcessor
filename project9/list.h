struct node {
	int data;
	struct node *link;
};
void insert_node_head(struct node *np),
insert_node_tail(struct node *np),
insert_node_ascn(struct node *np),
free_node(struct node *np), tour_list(), free_list();
struct node *get_node();
extern struct node *Head;
