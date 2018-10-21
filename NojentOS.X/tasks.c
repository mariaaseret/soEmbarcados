#include "tasks.h"

TASK pisca_led_red()
{
    TRISDbits.RD0 = 0;                                                          // D0 configurado como saída de dados
    PORTDbits.RD0 = 0;                                                          // Porta está em estado 0
    
    while(1)
    {
        PORTDbits.RD0 = ~LATDbits.LD0;
        asm("nop");
        asm("nop");
        asm("nop");
    }
    
    return NULL;
}

TASK pisca_led_yellow()
{
    TRISDbits.RD1 = 0;                                                          // D0 configurado como saída de dados
    PORTDbits.RD1 = 0;                                                          // Porta está em estado 0
    
    while(1)
    {
        PORTDbits.RD1 = ~LATDbits.LD1;
        asm("nop");
        asm("nop");
        asm("nop");
    }
    
    return NULL;
}

TASK pisca_led_green()
{
    TRISDbits.RD2 = 0;                                                          // D0 configurado como saída de dados
    PORTDbits.RD2 = 0;                                                          // Porta está em estado 0
    
    while(1)
    {
        PORTDbits.RD2 = ~LATDbits.LD2;
        asm("nop");
        asm("nop");
        asm("nop");
    }
    
    return NULL;
}
