#ifndef DELAY_H
#define	DELAY_H

#include "config.h"
#include "types.h"

typedef struct delay_data {
    u_int task_pos_ready_queue;
    u_int task_delay_remaning;
} delay_data_t;


typedef struct queue_delay {
    delay_data_t delay_QUEUE[MAX_TASKS];
    u_int delay_queue_size;
} queue_delay_t;

void delay_queue_create(queue_delay_t *delay_queue_handler);
void delay_queue_insert(queue_delay_t *delay_queue_handler, u_int task_pos, u_int ms);
void delay_queue_remove(queue_delay_t *delay_queue_handler,  u_int task_pos);

#endif	/* DELAY_H */

