#ifndef KERNEL_H
#define	KERNEL_H

#include "types.h"

// Tarefa idle
void task_idle();

// Chamadas de sistema
void init();
void dispatcher(t_state state);
t_tcb* RR_scheduler();
t_tcb* PRIOR_scheduler();
void delay(u_int ms);
void create_task(u_int id, u_int prior, void(*f)(void));
void setup_timer();
void start_GnROS();
void stack_copy(t_tcb *task, u_int in_out);

// Controle de interrupção (Round Robin)
void __attribute__ ((interrupt(no_auto_psv))) _T1Interrupt(void);


#endif	/* KERNEL_H */

