/*
 * Projeto: Troca de Contexto
 * Data: 25 de setembro de 2017 
 * Arquivo: types.h
 */

#ifndef TYPES_H
#define	TYPES_H

typedef unsigned int u_int;
typedef enum {NEW, READY, RUNNING} t_state;

struct tcb_t {
  u_int task_id;
  u_int task_prior;
  t_state task_state;
  u_int *frame_ptr;
  u_int *stack_ptr;
  u_int statck_limit;
  void(*f)(void);
};

struct queue_t {
  u_int pos_ready_queue;
  u_int delay_time;
};

#endif	/* TYPES_H */

