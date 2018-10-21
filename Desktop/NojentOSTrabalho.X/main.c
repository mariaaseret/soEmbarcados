#include <xc.h>
#include "kernel.h"
#include "tasks.h"
#include "timer.h"
#include "lcd.h"

void ADCInit();
void PORTInit();

int main(void) 
{
    nojoStart();
    setupTimer();   
    SRAMInitHeap(); // gerenciador de memória
    LCDInit(LS_BLINK);
    LCDWriteStringXY(0,0,"Piscina");
    //Inicia as portas - entrada/saida
    PORTInit();
    //Inicia o modulo de conversao ADC
    ADCInit();
    // Declaracao e criacao dos semaforos
    extern sem_t s_1, s_2;
    //O semaforo s_1 e inicializado em 1 para assegurar funcionamento
    sem_create(&s_1, 0);
    //O semaforo s_1 e inicializado em 0 para assegurar funcionamento
    sem_create(&s_2, 1);
    
    //Criacao das tarefas
    nojoTaskCreate(1, 10, limpeza);
    nojoTaskCreate(2, 9, cloro);
    nojoTaskCreate(3, 8, ph);
    nojoTaskCreate(4, 7, controle);
    
    
    nojoScheduler();//Chama o escalonador

    while(1)
    {
        NOP();
    }
    return (EXIT_SUCCESS);
}

void ADCInit() {
	ADCON2=0b10001010;
}

void PORTInit() {
    
    TRISCbits.RC0 = 0;
    TRISCbits.RC1 = 0;
    TRISCbits.RC2 = 0;
    TRISCbits.RC3 = 0;
    TRISCbits.RC4 = 0;
    TRISCbits.RC5 = 0;
    TRISCbits.RC7 = 1;
    PORTCbits.RC0 = 0;
    PORTCbits.RC1 = 0;
}