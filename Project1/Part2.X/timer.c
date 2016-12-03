/* 
 * File:   timer.c
 * Author: kairu
 * Adapted from work by gvanhoy
 *
 * Created January 2016
 */

#include <xc.h>
// Not used in this part, but kept to make integration with part 3 easier
void initTimer1(){
    TMR1 = 0;               // clear TMR1
    PR1 = 194;           // Initialize PR1
    T1CONbits.TCKPS = 3;    // Set Prescaler to 256
    T1CONbits.TCS = 0;      // Choose Oscillator Zero (PLL)
    IEC0bits.T1IE = 1;      // Interrupt enabled
    IFS0bits.T1IF = 0;      // Lower the flag
    IPC1bits.T1IP = 7;      // Default Priority
}
// Unused, but kept for sentimental reasons:
void timer1On(){
    T1CONbits.ON = 1;       // Start Timer
}
void timer1Off(){
    TMR1 = 0;
    T1CONbits.ON = 0;
}
// Used for microsecond delay
void initTimer2(){
    TMR2 = 0;               // Clear TMR2
    T2CONbits.TCKPS = 1;// Set Prescaler to 2
    T2CONbits.TCS = 0;      // Choose Oscillator Zero (PLL)
    IEC0bits.T2IE = 0;      // Disable the interrupt
    IFS0bits.T2IF = 0;      // Lower the flag
    IPC2bits.T2IP = 7;      // Default Priority
    T2CONbits.ON = 0;
}
// Delays some number of microseconds
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