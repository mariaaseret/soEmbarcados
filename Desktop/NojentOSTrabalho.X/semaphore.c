#include "semaphore.h"
#include "kernel.h"

void sem_create(sem_t *handler, u_int initial_value) {
    handler->sem_value = initial_value;
    queue_create(&handler->sem_queue);
}

void sem_wait(sem_t *handler) {
    DISABLE_GLOBAL_INTERRUPTS();
    
    handler->sem_value--;
    if(handler->sem_value < 0){
        // Bloqueia o Processo
        queue_insert(&handler->sem_queue, F_APTOS.task_running);
        F_APTOS.FILA_APTOS[F_APTOS.task_running].task_STATE = WAITING;

        // Chama o despachante
        nojoDispatcher(WAITING);
    }
    
    ENABLE_GLOBAL_INTERRUPTS();
}

void sem_post(sem_t *handler){
    DISABLE_GLOBAL_INTERRUPTS();
    
    handler->sem_value++;
    if(handler->sem_value <= 0) {
        F_APTOS.FILA_APTOS[queue_remove(&handler->sem_queue)].task_STATE = READY;
        nojoDispatcher(READY);
    }
    
    ENABLE_GLOBAL_INTERRUPTS();
}
