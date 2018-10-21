#define FCY 10000000UL


#include "xc.h"
#include "kernel.h"
#include "tasks.h"
#include "pipe.h"

#define ON        1
#define OFF       0
#define MAX_TASKS 5
#define QUANTUM   1250
#define RR_SCH    ON

#define DGI() asm("DISI #0x3FFF")
#define EGI() asm("DISI #0")


struct tcb_t READY_Queue[MAX_TASKS];
struct queue_t WAITING_Queue[MAX_TASKS];

u_int tasks         = 0;
u_int task_running  = MAX_TASKS-1;
u_int tasks_waiting = 0;


/**
 * Tarefas  
 */
void task_1();
void task_2();
void task_3();
void task_4();
void task_5();

/**
 * Chamadas de sistema
 */
void create_tasks(u_int id, u_int prior, void(*f)(void));
u_int RR_scheduler();
void dispatcher(u_int task_pos);
void setup();
void setup_int();
void setup_timer_0();
u_int get_pos(u_int id);
void delay(u_int valor);

/**
 * Interrupção de timer
 */
void __attribute__ ((interrupt(no_auto_psv))) _T1Interrupt(void);



/**
 * Função principal
 */
int main()
{
  setup();
  setup_timer_0();
  SPLIM = 0x1FFE;
  // Cria tarefas
  create_tasks(1, 5, task_1);
  create_tasks(2, 4, task_2);
  create_tasks(3, 3, task_3);
  create_tasks(4, 2, task_4);
  create_tasks(5, 1, task_5);
  
  while (1) {

  }
  return 0;
}

/**
 * Chamadas de sistema
 */
void create_tasks(u_int id, u_int prior, void(*f)(void))
{
  READY_Queue[tasks].task_id      = id;
  READY_Queue[tasks].task_prior   = prior;
  READY_Queue[tasks].f            = f;
  READY_Queue[tasks].task_state   = NEW;
  
  tasks++;
}

u_int priority_scheduler()
{
  u_int pos;
  
  return pos;
}

u_int RR_scheduler()
{  
  return ((task_running+1) % MAX_TASKS);
}

void dispatcher(u_int task_pos)
{
  // Atualiza tarefa que está em execução
  task_running = task_pos;
  // Executa a tarefa
  READY_Queue[task_pos].f();
}

void setup()
{
  //TRISA = 0b1111111111100000;
  
  TRISAbits.TRISA0 = 0;
  TRISAbits.TRISA1 = 0;
  TRISAbits.TRISA2 = 0;
  TRISAbits.TRISA3 = 0;
  TRISAbits.TRISA4 = 0;
}

void setup_int()
{
  // Configura as fontes de interrupção
  // Configuração da Interrupção 0
  INTCON1bits.NSTDIS = 1;
  INTCON2bits.INT0EP = 0;       // Borda de subida (default zero)
  IFS0bits.INT0IF    = 0;       // Flag da interrupção
  IEC0bits.INT0IE    = 1;       // Habilita a interrupção externa zero
  IPC0bits.INT0IP    = 0b001;   // Prioridade da interrupção -> 1  
}

void setup_timer_0()
{  
 // INTCON1bits.NSTDIS = 1;
 // INTCON2bits.DISI = 1;
  INTCON2bits.INT0EP = 0;       // Borda de subida (default zero)
  IFS0bits.T1IF      = 0;       // Flag da interrupção
  IEC0bits.T1IE      = 1;       // Habilita a interrupção externa zero
  IPC0bits.T1IP      = 0b001;   // Prioridade da interrupção -> 1  
  T1CONbits.TCS      = 0;      // Fonte interna de clock (Fosc / 2)
  T1CONbits.TCKPS    = 0b00;   // Preescaler
  PR1                = 15000;
  TMR1               = 0;
  T1CONbits.TON      = ON;    // Timer inicia desativado
}

void __attribute__ ((interrupt(no_auto_psv))) _T1Interrupt(void)
{
  // Desabilita as interrupões globais
  DGI();
  
  // Desabilitar o flag da interrupção zero
  IFS0bits.T1IF   = 0;
  
  if (/*task_running == 4 && */READY_Queue[task_running].task_state == NEW) {
    // Escolhe a próxima tarefa a entrar em execução
    //task_running    = ((task_running+1) % MAX_TASKS);
    // Restaura contexto da tarefa que entrará em execução
    //asm("mov.w w14, %0" :: "r" (READY_Queue[task_running].frame_ptr));
    asm("mov.w w14, %0" : "=r" (READY_Queue[task_running].stack_ptr));
   // SPLIM = READY_Queue[task_running].statck_limit;
    READY_Queue[task_running].task_state = RUNNING;
    SET_CPU_IPL(0);
    asm("goto %0" :: "r" (READY_Queue[task_running].f));    
  }
  else if (READY_Queue[task_running].task_state == RUNNING) {
    // Salva contexto da tarefa que sairá de execução
    //asm("mov.w w14, %0" : "=r" (READY_Queue[task_running].frame_ptr));
    asm("mov.w w14, %0" : "=r" (READY_Queue[task_running].stack_ptr));
    //READY_Queue[task_running].statck_limit = SPLIM;
    READY_Queue[task_running].task_state = READY;

    // Escolhe a próxima tarefa a entrar em execução
    task_running    = ((task_running+1) % MAX_TASKS);
    if (*(READY_Queue[task_running].stack_ptr) >= 0x0800 && *(READY_Queue[task_running].stack_ptr) < SPLIM){ 
    // Restaura contexto da tarefa que entrará em execução
        //asm("mov.w %0, w14" :: "r" (READY_Queue[task_running].frame_ptr));
        asm("mov.w %0, w14" :: "r" (READY_Queue[task_running].stack_ptr));
    READY_Queue[task_running].task_state = RUNNING;
   // SPLIM = READY_Queue[task_running].statck_limit;    
    }
  } 

  // Habilita as interrupões globais
  EGI();
}

u_int get_pos(u_int id)
{
  int i;
  for (i = 0; i < tasks; i++)
    if (READY_Queue[i].task_id == id)
      return i;
  
  return MAX_TASKS;    
}

void delay(u_int valor)
{
  u_int i, j;
  for (i = 0; i < valor/6; i++){
    for (j = 0;j < valor/2; j++){
    }
  }
}


/**
 * Tarefas  
 */
void task_1()
{
    while(1){
        PORTAbits.RA0 = !PORTAbits.RA0;
        delay(QUANTUM);
    }
}

void task_2()
{
    while(1){
        PORTAbits.RA1 = !PORTAbits.RA1;
        delay(QUANTUM);
    }
}

void task_3()
{
    while(1){
        PORTAbits.RA2 = !PORTAbits.RA2;
        delay(QUANTUM);
    }
}

void task_4()
{
    while(1){
        PORTAbits.RA3 = !PORTAbits.RA3;
        delay(QUANTUM);
    }
}

void task_5()
{
    while(1){
        PORTAbits.RA4 = !PORTAbits.RA4;
        delay(QUANTUM);
    }
}

