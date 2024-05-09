#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include "schedulers.h"
#include "sort.h"
#include "cpu.h"

struct node *head = NULL;
struct node *curr = NULL;
int numOfTasks = 0;

//struct node *priority_q[MAX_PRIORITY + 1] = {NULL};

void add(char *name, int priority, int burst)
{
    Task *task = (Task*) malloc (sizeof(Task));
    assert(task != NULL);

    task->name = (char*) malloc (sizeof(name));
    assert(task->name != NULL);

    numOfTasks++;

    if(NULL == head)
    {
        head = (struct node *) malloc (sizeof(struct node));
        assert(head != NULL);

        //copy name 
        strcpy(task->name, name);

        task->priority = priority;
        task->burst = burst;
        task->remaining_burst = burst;

        head->task = task;
        head->next = NULL;

        curr = head;
    }
    else
    {
        curr->next = (struct node *) malloc (sizeof(struct node));
        assert(curr->next != NULL);

        curr = curr->next;

        //copy name
        strcpy(task->name, name);

        task->priority = priority;
        task->burst = burst;
        task->remaining_burst = burst;

        curr->task = task;
        curr->next = NULL;
    }

}

void schedule()
{
	struct node *temp = head;
	int waitTime = 0;
	int currTime = 0;

	struct node **priority_q = (struct node**) calloc ((MAX_PRIORITY + 1), sizeof(struct node*));

	while(temp != NULL)
	{
		struct node **curr = &priority_q[temp->task->priority];
		
		if(*curr == NULL)
		{
			*curr = temp;
			temp = temp->next;
			(*curr)->next = NULL;
		}
		else
		{
			struct node *iterator = *curr;

			while(iterator->next != NULL)
			{	
				iterator = iterator->next;
			}

			iterator->next = temp;
			temp = temp->next;
			iterator->next->next = NULL;
		}

	}

	for(int i = MAX_PRIORITY; i >= MIN_PRIORITY; i--)
	{
		struct node* curr = priority_q[i];
		struct node* schd = curr;

		if(curr == NULL)
			continue;
	
		if(curr->next == NULL)
		{
			run(curr->task, curr->task->burst, curr->task->burst + waitTime, waitTime);
			curr = NULL;
		}
		else
		{	while(curr != NULL)
			{
				if(schd->task->remaining_burst < TIME_QUANTUM)
				{
					currTime = schd->task->remaining_burst;
					schd->task->remaining_burst = 0;
				}
				else
				{
					currTime = TIME_QUANTUM;
					schd->task->remaining_burst -= TIME_QUANTUM;
				}
		
				if(schd->task->remaining_burst == 0)
				{
					run(schd->task, currTime, schd->task->burst + waitTime, waitTime);
					delete(&curr, schd->task);
				}
				else
					run_rr(schd->task, currTime, waitTime);

				waitTime += currTime;

				schd = schd->next;
				
				if(schd == NULL)
					schd = curr;
			}
		}
	}
}
