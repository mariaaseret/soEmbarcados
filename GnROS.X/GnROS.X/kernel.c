#include <p24FJ128GA010.h>

#include "kernel.h"

// Variáveis globais
t_ready_Queue ready_queue;

// Tarefa idle
void task_idle()
{
  while (1) {
    asm("nop");
  }
}

// Chamadas de sistema
void init()
{
  // Inicializar as estruturas de dados
  ready_queue.task_running    = 0;
  ready_queue.tasks_installed = 0;
  
  // Define o tamanho da pilha
  //SPLIM = STACK_SIZE;
  
  // Cria a tarefa idle
  create_task(0, MIN_PRIORITY, task_idle);
  setup_timer();  
}

void start_GnROS()
{
  T1CONBITS.TON = ON;
}

void dispatcher(t_state state)
{
  // Desabilitar as interrupções globais
  DGI();
  
  t_tcb *next_task = NULL;
  u_int task_in_execution = ready_queue.task_running;
  
  // Salva o contexto da tarefa que deixará a execução
  
  #if RR
  next_task = RR_scheduler();
  #else
  next_task = PRIOR_scheduler();
  #endif

  // Atualiza o estado da tarefa que deixará de ser executada
  ready_queue.tasks_tcb[task_in_execution].tcb_state = state;
  // Salvar o contexto da tarefa que deixará de ser executada
  stack_copy(&ready_queue.tasks_tcb[task_in_execution], state);
  
  // Atualiza o estado da tarefa que entrará em execução
  next_task->tcb_state = RUNNING;
  // Restaurar o contexto da tarefa que entrará em execução
  stack_copy(next_task, RUNNING);
  
  EGI();
}

t_tcb* RR_scheduler()
{
  t_tcb *next_task;
  u_int pos_next_task   = 0;
  
  do {
    next_task = NULL;
    pos_next_task = (pos_next_task + 1) % ready_queue.tasks_installed;
    if (ready_queue.tasks_tcb[pos_next_task].tcb_state == READY)
      next_task = &ready_queue.tasks_tcb[pos_next_task];
    
  } while (!next_task);
  
  // Atualiza a informação a respeito da posição da tarefa que entrará em execução
  ready_queue.task_running = pos_next_task;
  
  return next_task;
}

t_tcb* PRIOR_scheduler()
{
    
  
}

void delay(u_int ms)
{
  
}

void create_task(u_int id, u_int prior, void(*f)(void))
{
  ready_queue.tasks_tcb[ready_queue.tasks_installed].tcb_id = id;
  ready_queue.tasks_tcb[ready_queue.tasks_installed].tcb_prior = prior;
  ready_queue.tasks_tcb[ready_queue.tasks_installed].f = f;
  ready_queue.tasks_tcb[ready_queue.tasks_installed].tcb_state = READY;
  ready_queue.tasks_tcb[ready_queue.tasks_installed].task_stack.stack[0] = ready_queue.tasks_tcb[ready_queue.tasks_installed].f;
  ready_queue.tasks_tcb[ready_queue.tasks_installed].task_stack.stack_size = 1;
  ready_queue.tasks_installed++;  
}

void setup_timer()
{
  INTCON1bits.NSTDIS = 1;
  INTCON2bits.INT0EP = 0;       // Borda de subida (default zero)
  IFS0bits.T1IF      = 0;       // Flag da interrupção
  IEC0bits.T1IE      = 1;       // Habilita a interrupção externa zero
  IPC0bits.T1IP      = 0b001;   // Prioridade da interrupção -> 1  
  T1CONbits.TCS      = 0;       // Fonte interna de clock (Fosc / 2)
  T1CONbits.TCKPS    = 0b01;    // Preescaler
  // Verificar
  PR1                = 15000;  
}

void stack_copy(t_tcb *task, u_int in_out)
{
  // in_out
  // 0 - in 
  // 1 - out
  
  switch (in_out) {
  
    case RUNNING: // Copia dados da pilha de contexto para a pilha de hardware
            WREG15 = 0x0;
            do {
              
              --task->task_stack.stack_size;
              WREG15 = (task->task_stack.stack[task->task_stack.stack_size]);
              asm("PUSH W15");
              
            } while (task->task_stack.stack_size);
            
            break;
    
    default: // Copia dados da pilha de hardware para a pilha de contexto
            task->task_stack.stack_size = 0;
            do {
              asm("POP W15");
              task->task_stack.stack[task->task_stack.stack_size] = *WREG15;
              task->task_stack.stack_size++;              
            } while (WREG15);

            break;
  }
}

// Controle de interrupção (Round Robin)
void __attribute__ ((interrupt(no_auto_psv))) _T1Interrupt(void)
{
  IFS0bits.T1IF   = 0;
  dispatcher(READY);
}


