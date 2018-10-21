#include "scheduler.h"

extern fila_t F_APTOS;

POS_READY_QUEUE priority_scheduler()
{
    u_int i, pos_next_task = 0;
    for(i = 1; i <= F_APTOS.tasks_installed; i++) {
        if(F_APTOS.FILA_APTOS[pos_next_task].task_PRIOR < F_APTOS.FILA_APTOS[i].task_PRIOR) {
            if(F_APTOS.FILA_APTOS[i].task_STATE == READY){
                pos_next_task = i;
            }
        }
    }
    return pos_next_task;
}

POS_READY_QUEUE RR_scheduler()
{
    u_int i = F_APTOS.task_running, pos_next_task = 0, installed = F_APTOS.tasks_installed;
    
    do{
        i++;
        pos_next_task = i % (installed);
    }while (F_APTOS.FILA_APTOS[pos_next_task].task_STATE != READY);
    
    return pos_next_task;
}

