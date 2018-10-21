#ifndef TYPES_H
#define TYPES_H

#include "config.h"

#define TASK void*

typedef unsigned char byte;
typedef unsigned char boolean;
typedef unsigned long int u_int;
typedef unsigned short long int uint24_t;
typedef u_int POS_READY_QUEUE;
typedef enum {READY = 0, RUNNING, WAITING, FINISHED} state_t;
typedef TASK (*FuncPtr) (void);

typedef struct stack_context {
    byte TOSL;
    byte TOSH;
    byte TOSU : 5;
} stack_context_t;

typedef struct stack {
    stack_context_t task_stack[MAX_STACK_LEVEL];
    byte stack_size;
} stack_t;

typedef struct ctx {
    byte ctx_WORK;
    byte ctx_BSR;
    byte ctx_STATUS;
    byte ctx_STKPTR;
    byte ctx_PCL;
    byte ctx_PCLATU;
    byte ctx_PCLATH;
    stack_t ctx_STACK;
} ctx_t;

typedef struct tcb {
    u_int task_ID;
    u_int task_PRIOR;
    state_t task_STATE;
    FuncPtr task_PTR;
    // int (*xuxa)(int*, int*, float*);
    ctx_t task_CTX;
} tcb_t;

typedef struct fila {
    tcb_t FILA_APTOS[MAX_TASKS+1];
    u_int tasks_installed;
    u_int task_running;
} fila_t;

#endif  /* TYPES_H */

