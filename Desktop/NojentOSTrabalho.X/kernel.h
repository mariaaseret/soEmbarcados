#ifndef KERNEL_H
#define	KERNEL_H

#include "types.h"
#include "sralloc.h"
#include "delay.h"

extern fila_t F_APTOS;
extern queue_delay_t Q_DELAY;

byte tWORK, tBSR, tSTATUS;

#define SAVE_CONTEXT() \
do{\
    asm("MOVWF _tWORK");\
    asm("MOVFF BSR, _tBSR");\
    asm("MOVFF STATUS, _tSTATUS");\
    F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_WORK = tWORK;\
    F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_BSR = tBSR;\
    F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_STATUS = tSTATUS;\
    while(STKPTR) { \
        F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_STACK.task_stack[F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_STACK.stack_size].TOSU = TOSU;\
        F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_STACK.task_stack[F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_STACK.stack_size].TOSL = TOSL;\
        F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_STACK.task_stack[F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_STACK.stack_size].TOSH = TOSH;\
        F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_STACK.stack_size++;\
        asm("POP");\
    }\
 }while(0)
    
#define RESTORE_CONTEXT()\
do{\
    STKPTR = 0;\
    tWORK = F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_WORK;\
    tBSR = F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_BSR;\
    tSTATUS = F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_STATUS;\
    while (F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_STACK.stack_size > 0) { \
        asm("PUSH");\
        F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_STACK.stack_size--;\
        TOSU = F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_STACK.task_stack[F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_STACK.stack_size].TOSU;\
        TOSH = F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_STACK.task_stack[F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_STACK.stack_size].TOSH;\
        TOSL = F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_STACK.task_stack[F_APTOS.FILA_APTOS[F_APTOS.task_running].task_CTX.ctx_STACK.stack_size].TOSL;\
    }; \
    asm("MOVFF _tBSR, BSR");\
    asm("MOVFF _tSTATUS, STATUS");\
    asm("MOVF _tWORK");\
}while(0)

#define DISABLE_GLOBAL_INTERRUPTS()     INTCONbits.GIE = 0
#define ENABLE_GLOBAL_INTERRUPTS()      INTCONbits.GIE = 1

void nojoStart();
void nojoTaskCreate(u_int id, u_int prior, FuncPtr task_PTR);
void nojoDelay(u_int ms);
void nojoDispatcher(state_t state);
TASK nojoTaskIdle();
void nojoYield();

#endif	/* KERNEL_H */

