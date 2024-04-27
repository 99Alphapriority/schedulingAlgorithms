#define MIN_PRIORITY 1
#define MAX_PRIORITY 10

extern struct node *head;
extern struct node *curr;

// add a task to the list 
void add(char *name, int priority, int burst);

// invoke the scheduler
void schedule();
