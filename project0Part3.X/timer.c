/* 
 * File:   timer.c
 * Author: kairu
 * Adapted from work by gvanhoy
 *
 * Created January 2016
 */

#include <xc.h>

void initTimer1(){
    TMR1 = 0;               // clear TMR1
    PR1 = 194;           // Initialize PR1
    T1CONbits.TCKPS = 3;    // Set Prescaler to 256
    T1CONbits.TCS = 0;      // Choose Oscillator Zero (PLL)
    IEC0bits.T1IE = 1;      // Interrupt enabled
    IFS0bits.T1IF = 0;      // Lower the flag
    IPC1bits.T1IP = 7;      // Default Priority
}

void timer1On(){
    T1CONbits.ON = 1;       // Start Timer
}
void timer1Off(){
    TMR1 = 0;
    T1CONbits.ON = 0;
}

void initTimer2(){
    TMR2 = 0;               // Clear TMR2
    PR2 = 194;               // Appx. 1ms.
    T2CONbits.TCKPS = 7;// Set Prescaler to 256
    T2CONbits.TCS = 0;      // Choose Oscillator Zero (PLL)
    IEC0bits.T2IE = 1;      // Enable the interrupt
    IFS0bits.T2IF = 0;      // Lower the flag
    IPC2bits.T2IP = 7;      // Default Priority
    
}

void timer2On(){
    T2CONbits.ON = 1;       // Start Timer
}
void timer2Off(){
    TMR2 = 0;
    T2CONbits.ON = 0;
}

