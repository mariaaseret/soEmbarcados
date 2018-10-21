#ifndef QUEUE_H
#define	QUEUE_H

#include "types.h"

typedef struct queue {
    u_int TASKS[MAX_TASKS];
    u_int queue_size;
    u_int queue_first;
} queue_t;

void queue_create(queue_t *queue_handler);
void queue_insert(queue_t *queue_handler, u_int task_pos);
u_int queue_remove(queue_t *queue_handler);

#endif	/* QUEUE_H */

