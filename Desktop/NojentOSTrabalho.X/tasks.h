#ifndef TASKS_H
#define	TASKS_H

#include "types.h"
#include "config.h"
#include "semaphore.h"
#include "kernel.h"
#include "pipe.h"
#include "lcd.h"
#include <math.h>

//Declaracao dos semaforos
sem_t s_1, s_2;
//Declaracao do piper
pipe_t mensagens;
//Variaveis auxiliares do ADC
unsigned int val, medcloro, medph;
//Variavel utilizada na maquina de estados
unsigned char state = '0';

//Funcao auxiliar de leitura do ADC
unsigned int ADCRead(unsigned char ch);

//Prototipo das tarefas
TASK cloro();
TASK ph();
TASK limpeza();
TASK controle();

#endif	/* TASKS_H */

