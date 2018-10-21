#ifndef TYPES_H
#define	TYPES_H

#include "config.h"

#define MAX_PRIORITY    10
#define MIN_PRIORITY    0

#define NULL            '\0'

#define DGI() asm("DISI #0x3FFF")
#define EGI() asm("DISI #0")

typedef char byte;
typedef unsigned int u_int;
typedef enum {READY = 0, RUNNING, WAITING,W_PIPE, W_SEM, SLEPPING, STOPPED} t_state;

typedef struct {
  int stack[STACK_SIZE]; 
  u_int stack_size;  
} t_stack;

typedef struct {
  u_int tcb_id;
  u_int tcb_prior;
  t_state tcb_state;
  t_stack task_stack;
  void (*f)(void);
} t_tcb;

typedef struct {
  t_tcb tasks_tcb[MAX_TASKS];
  u_int tasks_installed;  // Tarefas instaladas (quantidade)
  u_int task_running;     // Tarefa atualmente em execução (posição)  
} t_ready_Queue;

#endif	/* TYPES_H */

