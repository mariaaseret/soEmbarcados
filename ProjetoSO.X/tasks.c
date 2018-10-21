
#include <p24FJ128GA010.h>
#include "pipe.h"

pipe_t msgs;

// Implementação das tarefas
void task_1()
{
    create_pipe(&msgs);
    
    TRISCbits.TRISC1 = 0;
    char dados[5] = {'a', 'b', 'c', 'd','e'};
    int x = 0;
 
    while (1) {
      PORTCbits.RC1 = ~PORTCbits.RC1;
      //Escreve no pipe
      write(&msgs, dados[x]);
      if(++x > 4) x=0;
    }  
}

void task_2()
{
    TRISEbits.TRISE0=0;
    byte mensagem;
  while (1) {
      PORTEbits.RE0 = ~PORTEbits.RE0;
      read(&msgs, &mensagem);
  }    
}

void task_3()
{
  while (1) {
    
  }    
}

