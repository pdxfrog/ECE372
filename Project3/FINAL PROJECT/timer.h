/* 
 * File:   timer.h
 * Author: kairu
 * Adapted from work by gvanhoy
 *
 * Created January 2016
 */

#ifndef TIMER_H
#define	TIMER_H


void initTimer1();


//void delayMs(unsigned int delay);
void initTimer2();
void timer2On();
void timer2Off();


void initTimer3();
void initTimer4();

void delayQuarterSeconds(int numSeconds);
void delaySeconds(int numSeconds);
void delay(short int microSeconds);

#endif	/* TIMER_H */

