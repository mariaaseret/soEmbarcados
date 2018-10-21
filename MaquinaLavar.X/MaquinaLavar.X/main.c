/*
 * File:   main.c
 * Author: eletro30
 *
 * Created on 7 de Agosto de 2017, 14:30
 */

#define FCY 40000000UL

#include <xc.h>
#include "libpic30.h"

void roupaColorida();
void roupaBranca();
void roupaPreta();

int main(void)
{
  TRISAbits.TRISA0 = TRISAbits.TRISA1 = TRISAbits.TRISA2 = 0;
  TRISBbits.TRISB0 = TRISBbits.TRISB1 = TRISBbits.TRISB2 = 1;
  
  while(1)
  {
    if(PORTBbits.RB0 == 0)
      roupaColorida();
    else if(PORTBbits.RB1 == 0)
      roupaBranca();
    else if(PORTBbits.RB2 == 0)
      roupaPreta();
  }
  
  return 0;
}

void roupaColorida()
{
  PORTAbits.RA0 = 1;
  __delay_ms(100);
  PORTAbits.RA0 = 0;
}

void roupaBranca()
{
  PORTAbits.RA1 = 1;
  __delay_ms(200);
  PORTAbits.RA1 = 0;
}

void roupaPreta()
{
  PORTAbits.RA2 = 1;
  __delay_ms(50);
  PORTAbits.RA2 = 0;
}