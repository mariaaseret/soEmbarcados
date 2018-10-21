#include "pipe.h"
#include "sralloc.h"
#include "kernel.h"

/*
 * Chamadas de sistema para manipulação do PIPE
 */
void pipe_create(pipe_t *pipe_handler, u_int id, u_int size)
{
  pipe_handler->p_id        = id;
  pipe_handler->p_pos_read  = 0;
  pipe_handler->p_pos_write = 0;
  pipe_handler->p_size      = size;
  pipe_handler->p_msg_queue = SRAMalloc(size);  
  pipe_handler->p_count     = 0;
}

void pipe_read(pipe_t *pipe_handler, char* msg)
{
  DISABLE_GLOBAL_INTERRUPTS();
  
  if (pipe_handler->p_count == 0) { // PIPE está vazio
    // Bloqueia processo que tentou ler
    // Chama o despachante
    nojoDispatcher(WAITING_PIPE);
  }
  else {
    *msg = pipe_handler->p_msg_queue[pipe_handler->p_pos_read];
    pipe_handler->p_pos_read = (pipe_handler->p_pos_read + 1) % pipe_handler->p_size;
    pipe_handler->p_count--;
    // Desbloqueia processos que estão aguardando espaço no pipe
    libera_processos();
  }
  
  ENABLE_GLOBAL_INTERRUPTS();
}

void pipe_write(pipe_t *pipe_handler, char msg)
{
  DISABLE_GLOBAL_INTERRUPTS();
  
  if (pipe_handler->p_count == pipe_handler->p_size) { // PIPE está cheio
    // Bloqueia processo que tentou ler
    // Chama o despachante
    nojoDispatcher(WAITING_PIPE);
  }
  else {
    pipe_handler->p_msg_queue[pipe_handler->p_pos_write] = msg;
    pipe_handler->p_pos_write = (pipe_handler->p_pos_write + 1) % pipe_handler->p_size;
    pipe_handler->p_count++;
    // Desbloqueia processo que querem ler do pipe
    libera_processos();
  }

  ENABLE_GLOBAL_INTERRUPTS();  
}

void pipe_destroy(pipe_t *pipe_handler)
{
  SRAMfree(pipe_handler->p_msg_queue);
}

void libera_processos()
{
  int i;
  for (i = 0; i < F_APTOS.tasks_installed; i++)
    if (F_APTOS.FILA_APTOS[i].task_STATE == WAITING_PIPE)
      F_APTOS.FILA_APTOS[i].task_STATE = READY;
}
