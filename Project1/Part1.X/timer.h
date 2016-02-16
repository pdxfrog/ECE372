/* 
 * File:   timer.h
 * Author: 
 *
 * Created on December 30, 2014, 8:07 PM
 */

#ifndef INITTIMER_H
#define	INITTIMER_H

#define T1IF IFS0bits.T1IF

void delayUs(unsigned int delay);
void initTimer1();
void timerOn();
void timerOff();


#endif	/* INITTIMER_H */

