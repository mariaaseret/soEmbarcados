#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <p18f4520.h>

#pragma config WDT = OFF                                                        // Desabilita Watch Dog Timer 
#pragma config OSC = HS                                                         // Oscilador de 4 MHz

#define ON      1
#define OFF     0

// Configurações do NojentOS
#define MAX_TASKS   3                                                           // Número máximo de tarefas
#define RR_SCH      OFF                                                         // Ativa escalonador Round Robin
#define PRIOR_SCH   ON                                                          // Ativa escalonador Prioridade
#define MAX_STACK_LEVEL 31                                                      // Níveis da pilha de hardware

#endif	/* CONFIG_H */

