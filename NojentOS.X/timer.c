#include "timer.h"
#include "kernel.h"

void setupTimer()
{
    // Configuração do Timer0
    T0CONbits.T0CS      = 0;
    T0CONbits.T08BIT    = OFF;                                                  // 16 Bits
    T0CONbits.PSA       = 0;
    T0CONbits.T0PS      = 0b010;                                                // 1:8
    INTCONbits.TMR0IE   = ON;
    INTCONbits.TMR0IF   = OFF;
    INTCONbits.PEIE     = ON;
    
}

void nojoScheduler()
{
    TMR0 = 64911; // 1 ms
    //TMR0 = 59286;   // 10 ms
    //TMR0 = 3036;    // 100 ms
    T0CONbits.TMR0ON = ON;
}

void resetTimer()
{
    INTCONbits.TMR0IF = OFF;
    TMR0 = 64911; // 1 ms
    //TMR0 = 59286;   // 10 ms
    //TMR0 = 3036;    // 100 ms
}

void interrupt timer_ISR()
{
    if(INTCONbits.T0IE && INTCONbits.T0IF){
        resetTimer();        
        nojoDispatcher(READY);
    }
    
}