/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"
//Uses timer 2
void delayUs(unsigned int delay){
    //TODO: Create a delay using timer 2 for "delay" microseconds.
}


void initTimer1(){
    TMR1 = 0;               // clear TMR1
    PR1 = 194;           // Initialize PR1 for 5ms delay
    T1CONbits.TCKPS = 3;    // Set Prescaler to 256
    T1CONbits.TCS = 0;      // Choose Oscillator Zero (PLL)
    IEC0bits.T1IE = 1;      // Interrupt enabled
    T1IF = 0;      // Lower the flag
    IPC1bits.T1IP = 7;      // Default Priority
    T1CONbits.ON = 0;
}

void timerOn(){
    T1CONbits.ON = 1;       // Start Timer
}
void timerOff(){
    TMR1 = 0;
    T1CONbits.ON = 0;
}

