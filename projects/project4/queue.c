/* Implementation of a simple circular queue using a static array */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* create the queue data structure and initialize it */
queue *queue_init(int n) {
	queue *q = (queue *)malloc(sizeof(queue));
	q->size = n;
	q->start = 0;
	q->end = 0;
	q->count = 0;

	return q;
}

/* insert an item into the queue, update the pointers and count, and
   return the no. of items in the queue (-1 if queue is null or full) */
int queue_insert(queue *q, char *item, int jobs, char *stats) {
	if ((q == NULL) || (q->count == q->size))
	   return -1;

	q->buffer[q->end % q->size] = item;
	q->status[q->end % q->size] = stats;
	q->jobID [q->end % q->size] = jobs;

	q->end = (q->end + 1) % q->size;
	q->count++;

	return q->count;
}

/* delete an item from the queue, update the pointers and count, and 
   return the item deleted (-1 if queue is null or empty) */
int queue_delete(queue *q, int jobs) {
	if ((q == NULL) || (q->count == 0))
	   return -1;
	
	q->start = (q->start + 1) % q->size;
	q->count--;

	jobs--;
	return jobs;
}

/* display the contents of the queue data structure */
void queue_display(queue *q) {
	int i;
	printf("job ID\tprogram name\tstatus\n");
	if (q != NULL && q->count != 0) {
		for (i = 0; i < q->count; i++){
			printf("%d\t", q->jobID[(q->start + i) % q->size]);
	    		printf("%s\t", q->buffer[(q->start + i) % q->size]);
			printf("%s\n", q->status[(q->start + i) % q->size]);
		}
	}
}

/* delete the queue data structure */
void queue_destroy(queue *q) {
	free(q->buffer);
	free(q);
}

