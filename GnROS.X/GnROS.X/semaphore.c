
#include "semaphore.h"
#include "kernel.h"

extern t_ready_Queue ready_queue;

void sem_init(sem_t *s, int value)
{
  s->sem_count = value;
  s->sem_queue.size = 0;
  s->sem_queue.pos_next_free = 0;
}

void sem_wait(sem_t *s)  // Operação P()
{
  DGI();
  
  if (--s->sem_count < 0) {    
    s->sem_queue.tasks_blocked[s->sem_queue.size] = ready_queue.task_running;
    s->sem_queue.size = (s->sem_queue.size + 1) % MAX_TASKS;
    //ready_queue.tasks_tcb[ready_queue.task_running].tcb_state = WAITING;
    dispatcher(WAITING); 
  }
  
  EGI();
}

void sem_post(sem_t *s)  // Operação V()
{
  DGI();
  
  if (++s->sem_count <= 0) {
    ready_queue.tasks_tcb[s->sem_queue.tasks_blocked[s->sem_queue.pos_next_free]].tcb_state = READY;
    s->sem_queue.pos_next_free = (s->sem_queue.pos_next_free + 1) % MAX_TASKS;
    dispatcher(READY);
  }
  
  EGI();
}

