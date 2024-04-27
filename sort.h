#include "list.h"

typedef enum{
	SJF,
	PRIORITY
}sort_type_et;

struct node* merge(struct node *l1, struct node* l2, sort_type_et type);
void split(struct node* head, struct node **l1, struct node **l2);
void mergeSort(struct node **headRef, sort_type_et type);
