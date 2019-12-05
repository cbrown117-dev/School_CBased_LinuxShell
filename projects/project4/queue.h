/* Header file for the simple circular queue example */
#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct _queue {
	int size;    /* maximum size of the queue */
	char buffer[100][10]; /* queue buffer */
	int start;   /* index to the start of the queue */
	int end;     /* index to the end of the queue */
	int count;   /* no. of elements in the queue */
} queue;

queue *queue_init(int n);
int queue_insert(queue *q, char *item);
char* queue_delete(queue *q);
void queue_display(queue *q);
void queue_destroy(queue *q);

#endif
