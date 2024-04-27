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

        curr->task = task;
        curr->next = NULL;
    }

}

void schedule()
{
	mergeSort(&head, PRIORITY);

	struct node *Node = head;
    struct node *temp = Node;
    int tat = 0;
    int waitTime = 0;

    while(Node != NULL)
    {
        tat = Node->task->burst;
        run(Node->task, Node->task->burst, tat, waitTime);
        waitTime += tat;
        Node = Node->next;
        free(temp);
        temp = Node;
    }
}
