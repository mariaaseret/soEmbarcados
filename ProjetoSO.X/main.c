#include "xc.h"
#include "kernel.h"
#include "tasks.h"


int main(void)
{
  // Configura o SO
  init();
  
  // Cria as tarefas
  create_task(2, 5, task_1);
  create_task(3, 4, task_2);
  create_task(4, 6, task_3);
  
  // Inicia o SO
  start_GnROS();  
  
  while (1) {
    
  }
  
  return 0;
}
