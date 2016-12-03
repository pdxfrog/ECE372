/* 
 * File:   timer.c
 * Author: kairu
 * Adapted from work by gvanhoy
 *
 * Created January 2016
 */

#include <xc.h>
#include "timer.h"
#include "global_defines.h"

void initTimer1(){
    TMR1 = 0;               // clear TMR1
    PR1 = 195;              // Initialize PR1 To 5ms
    T1CONbits.TCKPS = 3;    // Set Prescaler to 256
    T1CONbits.TCS = 0;      // Choose Oscillator Zero (PLL)
    IEC0bits.T1IE = 1;      // Interrupt enabled
    IFS0bits.T1IF = 0;      // Lower the flag
    IPC1bits.T1IP = 7;      // Default Priority
}


void initTimer2(){
    TMR2 = 0;               // Clear TMR2
    T2CONbits.TCKPS = 1;// Set Prescaler to 2
    T2CONbits.TCS = 0;      // Choose Oscillator Zero (PLL)
    IEC0bits.T2IE = 0;      // Disable the interrupt
    IFS0bits.T2IF = 0;      // Lower the flag
    IPC2bits.T2IP = 7;      // Default Priority
    T2CONbits.ON = 0;
}

void delay(short int microSeconds){
    if(microSeconds){
    PR2 = 5 * microSeconds;
    TMR2 = 0;
    IFS0bits.T2IF = 0;  // Lower flag
    T2CONbits.ON = 1;   // Start Timer
    while(!IFS0bits.T2IF);  // Wait for flag to come up
    T2CONbits.ON = 0;   // Stop Timer
    }
}


/*
void initTimer3(){
    TMR3 = 0;               // clear TMR1
    PR3 = 194;           // Initialize PR1 To 5ms
    T3CONbits.TCKPS = 7;    // Set Prescaler to 256
    T3CONbits.TCS = 0;      // Choose Oscillator Zero (PLL)
    IEC0bits.T3IE = 1;      // Interrupt enabled
    IFS0bits.T3IF = 0;      // Lower the flag
    IPC3bits.T3IP = 7;      // Default Priority
}

void initTimer4(){
    TMR4 = 0;               // clear TMR1
    PR4 = 194;           // Initialize PR1 To 5ms
    T4CONbits.TCKPS = 7;    // Set Prescaler to 256
    T4CONbits.TCS = 0;      // Choose Oscillator Zero (PLL)
    IEC0bits.T4IE = 1;      // Interrupt enabled
    IFS0bits.T4IF = 0;      // Lower the flag
    IPC4bits.T4IP = 7;      // Default Priority
}
 */