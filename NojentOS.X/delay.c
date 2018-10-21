#include "types.h"
#include "delay.h"
#include "kernel.h"
#include "timer.h"

extern fila_t F_APTOS;

void delay_queue_create(queue_delay_t *delay_queue_handler){
    int i;    
    delay_queue_handler->delay_queue_size = 0;
    for(i=0;i<MAX_TASKS;i++)
        delay_queue_handler->delay_QUEUE[i].task_pos_ready_queue = 0;
}

void delay_queue_insert(queue_delay_t *delay_queue_handler, u_int task_pos, u_int ms){
    int i;
    
    if(TMR0ON == OFF) nojoScheduler();
    
    for(i=0;i<MAX_TASKS;i++){
        if(delay_queue_handler->delay_QUEUE[i].task_pos_ready_queue == 0){
            delay_queue_handler->delay_QUEUE[i].task_pos_ready_queue = task_pos;
            delay_queue_handler->delay_QUEUE[i].task_delay_remaning = ms;
            delay_queue_handler->delay_queue_size++;
            break;
        }
    }
}

void delay_queue_remove(queue_delay_t *delay_queue_handler,  u_int task_pos){    
    F_APTOS.FILA_APTOS[delay_queue_handler->delay_QUEUE[task_pos].task_pos_ready_queue].task_STATE = READY;
    delay_queue_handler->delay_QUEUE[task_pos].task_pos_ready_queue = 0;
    delay_queue_handler->delay_queue_size--;
    if(delay_queue_handler->delay_queue_size == 0) TMR0ON == OFF;
}