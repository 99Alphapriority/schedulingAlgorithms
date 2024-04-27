/**
 * "Virtual" CPU that also maintains track of system time.
 */

#include <stdio.h>
#include <unistd.h>

#include "task.h"

// run this task for the specified time slice
void run(Task *task, int slice, int tat, int waitTime) {
    printf("Running task = [%s] [%d] [%d] for %d ms.\t TAT: %d ms waiting time: %d ms.\n",task->name, task->priority, task->burst, slice, tat, waitTime);
	sleep(slice/1000);
}
