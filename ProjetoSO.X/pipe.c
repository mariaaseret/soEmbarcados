
#include "pipe.h"

void create_pipe(pipe_t *p){

    p->pos_read = -1;
    p->pos_write = 0;
    
}


void write(pipe_t *p, byte msg){

    DGI();
    
    p->pipe_msgs[p->pos_write] = msg;
    p->pos_write=(p->pos_write+1)%PIPE_SIZE;
    
    //Se posicao de escrita for igual a pos. de leitura
    //bloqueia processo. nao há espaco para escrita.
    if(p->pos_write==p->pos_read)
        dispatcher(W_PIPE);
    
    EGI();

}


byte read(pipe_t *p){

    DGI();
     byte msg;
    //se posicao de leitura for igual a pos. de escrita 
    //bloqueia processo. nao existe dado novo a ser lido
    if(p->pos_write==p->pos_read)
        dispatcher(WAITING);
    *msg = p->pipe_msgs[p->pos_read];
    p->pos_read=(p->pos_read+1)%PIPE_SIZE;
    
    //Chama o despachante para liberar eventuais
    //tarefas bloqueadas 
    dispatcher(READY);
  
    EGI();

}
