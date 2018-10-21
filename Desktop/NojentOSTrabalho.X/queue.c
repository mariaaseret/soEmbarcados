#include "queue.h"
#include "types.h"

void queue_create(queue_t *queue_handler){
    queue_handler->queue_first = 0;
    queue_handler->queue_size = 0;
}

void queue_insert(queue_t *queue_handler, u_int task_pos){
    u_int pos = (queue_handler->queue_size + queue_handler->queue_first) % MAX_TASKS; 
    queue_handler->TASKS[pos] = task_pos;
    queue_handler->queue_size++;
    
}

u_int queue_remove(queue_t *queue_handler){
    u_int value = queue_handler->TASKS[queue_handler->queue_first];
    
    queue_handler->queue_first = (queue_handler->queue_first + 1) % MAX_TASKS;
    queue_handler->queue_size--;
    
    return value;
}