#include "xc.h"
#include "libpic30.h"

#define MAX_TASKS 5
#define QUANTUM   50

/*
 * Tipos de dados
 */
typedef unsigned int u_int;

struct tcb_t {
  u_int task_id;
  u_int task_prior;
  void(*f)(void);
};

/**
 * Variáveis globais
 */
struct tcb_t READY_Queue[MAX_TASKS];
u_int tasks         = 0;
u_int task_running  = MAX_TASKS-1;

/**
 * Tarefas  
 */
void task_1();
void task_2();
void task_3();
void task_4();
void task_5();

/**
 * Chamadas de sistema
 */
void create_tasks(u_int id, u_int prior, void(*f)(void));
u_int priority_scheduler();
u_int RR_scheduler();
void dispatcher(u_int task_pos);
void show_id(u_int task_id);

/**
 * Função principal
 */
int main(void)
{
  // Cria tarefas
  create_tasks(1, 5, task_1);
  create_tasks(2, 4, task_2);
  create_tasks(3, 3, task_3);
  create_tasks(4, 2, task_4);
  create_tasks(5, 1, task_5);
  
  while (1) {
    
  }
  
  return 0;
}

/**
 * Chamadas de sistema
 */
void create_tasks(u_int id, u_int prior, void(*f)(void))
{
  READY_Queue[tasks].task_id      = id;
  READY_Queue[tasks].task_prior   = prior;
  READY_Queue[tasks].f            = f;
  tasks++;
}

u_int priority_scheduler()
{
  u_int pos;
  
  return pos;
}

u_int RR_scheduler()
{
  
  return ((task_running+1) % MAX_TASKS);

}

void dispatcher(u_int task_pos)
{
  // Atualiza tarefa que está em execução
  task_running = task_pos;
  // Mostra id da tarefa que irá entrar em execução
  show_id(READY_Queue[task_pos].task_id);
  // Executa tarefa
  READY_Queue[task_pos].f();
}

void show_id(u_int task_id)
{
  
}


/**
 * Tarefas  
 */
void task_1()
{
  
}

void task_2()
{
  
}

void task_3()
{
  
}

void task_4()
{
  
}

void task_5()
{
  
}
