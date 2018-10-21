#ifndef SEMAPHORE_H
#define	SEMAPHORE_H

#include "types.h"

typedef struct sem_queue {
  u_int size;
  u_int pos_next_free;
  u_int tasks_blocked[MAX_TASKS];
} queue_t;

typedef struct semaphore {
  int sem_count;
  queue_t sem_queue;
} sem_t;

void sem_init(sem_t *s, int value);
void sem_wait(sem_t *s);  // Operação P()
void sem_post(sem_t *s);  // Operação V()


#endif	/* SEMAPHORE_H */

