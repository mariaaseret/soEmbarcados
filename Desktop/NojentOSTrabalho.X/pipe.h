#ifndef PIPE_H
#define	PIPE_H

#include "types.h"

typedef struct pipe {
    u_int p_id;
    char* p_msg_queue;
    u_int p_pos_write;
    u_int p_pos_read;
    u_int p_size;
    u_int p_count;
} pipe_t;

/*
 * Chamadas de sistema para manipulação do PIPE
 */
void pipe_create(pipe_t *pipe_handler, u_int id, u_int size);
void pipe_read(pipe_t *pipe_handler, char* msg);
void pipe_write(pipe_t *pipe_handler, char msg);
void pipe_destroy(pipe_t *pipe_handler);
void libera_processos();


#endif	/* PIPE_H */

