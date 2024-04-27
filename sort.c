#include "stdio.h"

#include "sort.h"

struct node* merge(struct node *l1, struct node* l2, sort_type_et type)
{
	struct node *res = NULL;

	if(NULL == l1)
		return l2;
	else if (NULL == l2)
		return l1;

	if(SJF == type)
	{
		if(l1->task->burst < l2->task->burst)
		{
			res = l1;
			res->next = merge(l1->next, l2, type);
		}
		else
		{
			res = l2;
			res->next = merge(l1, l2->next, type);
		}
	}
	else if(PRIORITY == type)
	{
		if(l1->task->priority > l2->task->priority)
		{
			res = l1;
			res->next = merge(l1->next, l2, type);
		}
		else
		{
			res = l2;
			res->next = merge(l1, l2->next, type);
		}
	}

	return res;
}

void split(struct node* head, struct node **l1, struct node **l2)
{
	struct node *fast = head->next;
	struct node *slow = head;

	while(fast != NULL)
	{
		fast = fast->next;
		if(fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}

	*l1 = head;
	*l2 = slow->next;
	slow->next = NULL;
}

void mergeSort(struct node **headRef, sort_type_et type)
{
	struct node *head = *headRef;
	struct node *l1 = NULL;
	struct node *l2 = NULL;

	if((head == NULL) || head->next == NULL)
		return;

	split(head, &l1, &l2);

	mergeSort(&l1, type);
	mergeSort(&l2, type);

	*headRef = merge(l1, l2, type);
}
