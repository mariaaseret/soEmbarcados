
#ifndef SEMAPHORE_H
#define	SEMAPHORE_H

#include "types.h"
#include "queue.h"

typedef struct sem {
    int sem_value;
    queue_t sem_queue;
} sem_t;

void sem_create(sem_t *handler, u_int initial_value);
void sem_wait(sem_t *handler);
void sem_post(sem_t *handler);

#endif	/* SEMAPHORE_H */

