#ifndef PIPE_H
#define	PIPE_H

#include "types.h"

#define PIPE_SIZE 10

typedef struct pipe {
  byte pipe_msgs[PIPE_SIZE];
  u_int pos_write;
  u_int pos_read;
} pipe_t;

void create_pipe(pipe_t *p);
void write(pipe_t *p, byte msg);
void read(pipe_t *p, byte *msg);

#endif	/* PIPE_H */

