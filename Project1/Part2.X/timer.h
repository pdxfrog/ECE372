/* 
 * File:   timer.h
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#ifndef INITTIMER_H
#define	INITTIMER_H

void delayUs(unsigned int delay);



void initTimer1();

#define START_TIMER_1  T1CONbits.ON = 1;
#define STOP_TIMER_1 TMR1 = 0; T1CONbits.ON = 0;
#define T1IF IFS0bits.T1IF
void initTimer2();

void timer2On();
void timer2Off();
#define T2IF IFS0bits.T2IF
#endif	/* INITTIMER_H */

