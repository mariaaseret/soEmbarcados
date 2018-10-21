#ifndef TIMER_H
#define	TIMER_H

#include "types.h"

void setupTimer();
void nojoScheduler();
void resetTimer();
void interrupt timer_ISR();

#endif	/* TIMER_H */

