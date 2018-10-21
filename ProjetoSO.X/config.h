#ifndef CONFIG_H
#define	CONFIG_H

// Frequência
#define FCY 10000000UL

// DEFINE ON/OFF
#define ON        1
#define OFF       0

// Quantidade máxima de tarefas permitidas no sistema
#define MAX_TASKS 5

// Quantum do escalonador Round Robin (ms)
#define QUANTUM   2

// Escolha do escalonador
#define RR        ON
#define PRIOR     !RR

#define STACK_SIZE 64


#endif	/* CONFIG_H */

