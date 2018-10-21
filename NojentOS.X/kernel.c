#include "kernel.h"
#include "scheduler.h"
#include "delay.h"

fila_t F_APTOS;
queue_delay_t Q_DELAY;

void nojoStart() {
    asm("GLOBAL _pisca_led_red, _pisca_led_yellow, _pisca_led_green, _nojoTaskIdle");
    // Inicializa as estruturas de dados
    // Instala a tarefa Idle na posição 0 da fila de aptos
    // As prioridades são diretamente proporcional
    F_APTOS.FILA_APTOS[0].task_ID     = 0;
    F_APTOS.FILA_APTOS[0].task_PRIOR  = 0;
    F_APTOS.FILA_APTOS[0].task_STATE  = READY;
    F_APTOS.FILA_APTOS[0].task_PTR    = nojoTaskIdle;
    F_APTOS.tasks_installed = 1;
    F_APTOS.task_running = 0;
    delay_queue_create(&Q_DELAY);
    
    // Ativa controle de interrupção global
    ENABLE_GLOBAL_INTERRUPTS();
}

void nojoTaskCreate(u_int id, u_int prior, FuncPtr task_PTR)
{    
    F_APTOS.FILA_APTOS[F_APTOS.tasks_installed].task_ID     = id;
    F_APTOS.FILA_APTOS[F_APTOS.tasks_installed].task_PRIOR  = prior;
    F_APTOS.FILA_APTOS[F_APTOS.tasks_installed].task_STATE  = READY;
    F_APTOS.FILA_APTOS[F_APTOS.tasks_installed].task_PTR    = task_PTR;
    F_APTOS.FILA_APTOS[F_APTOS.tasks_installed].task_CTX.ctx_STACK.task_stack[0].TOSL = (uint32_t) task_PTR;
    F_APTOS.FILA_APTOS[F_APTOS.tasks_installed].task_CTX.ctx_STACK.task_stack[0].TOSH = (uint32_t) task_PTR >> 8;
    F_APTOS.FILA_APTOS[F_APTOS.tasks_installed].task_CTX.ctx_STACK.task_stack[0].TOSU = (uint32_t) task_PTR >> 16;
    F_APTOS.FILA_APTOS[F_APTOS.tasks_installed].task_CTX.ctx_STACK.stack_size = 1;
    F_APTOS.tasks_installed++;
}

void nojoDispatcher(state_t state)
{
    DISABLE_GLOBAL_INTERRUPTS();
    POS_READY_QUEUE task_pos;

    // Salva contexto da tarefa atual
    SAVE_CONTEXT();
    
    F_APTOS.FILA_APTOS[F_APTOS.task_running].task_STATE = state;

    // Seleciona nova tarefa
    #if RR_SCH
        task_pos = RR_scheduler();
    #else
        task_pos = priority_scheduler();
    #endif

    // Restaura contexto da nova tarefa
    F_APTOS.task_running = task_pos;
    F_APTOS.FILA_APTOS[task_pos].task_STATE = RUNNING;
    
    RESTORE_CONTEXT();        
    ENABLE_GLOBAL_INTERRUPTS();    
}

TASK nojoTaskIdle() {
    Nop();
    Nop();
    Nop();
    
    return NULL;
}

void nojoYield(){
    
}

void nojoDelay(u_int ms){
    DISABLE_GLOBAL_INTERRUPTS();
    
    delay_queue_insert(&Q_DELAY, F_APTOS.task_running, ms);
    nojoDispatcher(WAITING);    
    
    ENABLE_GLOBAL_INTERRUPTS();
}