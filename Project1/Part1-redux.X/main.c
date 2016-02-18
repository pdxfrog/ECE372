// ******************************************************************************************* //
//
// File:         lab1p1.c
// Date:         
// Authors:      
//
// Description: Part 1 for lab 1
// ******************************************************************************************* //
#define _TESTING_MODE
#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "leds.h"
#include "interrupt.h"
#include "switch.h"
#include "timer.h"

#define LOW 0
#define HIGH 1
/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */

    volatile char state;
    volatile char nextState;
    volatile char timerFinished;
    volatile char runState;
    enum{
        run, stop, wait1, wait2
    };
    
int main(void)
{
    SYSTEMConfigPerformance(10000000);
    initTimer1();
    initLEDs();
    initExtSW();
    initIntSW();
    // TEST:
#ifdef _TESTING_MODE
    TRISDbits.TRISD0 = 0;
    LATDbits.LATD0 = 0;
    TRISDbits.TRISD2 = 0;
    LATDbits.LATD2 = 0;
#endif
    
     state = run;
     nextState = run;
     timerFinished = 0;
     runState = 0;

    
    while(1)
    {
        switch(state){
            case run:
                setLED(RUN_LED);               
                LATDbits.LATD0 = 1;
                break;
            case wait1:
                LATDbits.LATD2 = 1;
                break;
            case stop:         
                setLED(STOP_LED);
                LATDbits.LATD0 = 0;
                break;
            case wait2:              
            LATDbits.LATD2 = 0;
                break;
            default:
                break;
        }
    }
    
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
    CNAIF = LOW;
    IFS1bits.CNDIF = LOW;
    PORTA;
    PORTD;
   
    if(!T1CONbits.ON){
        T1CONbits.ON = 1;
        switch(state){
            case run:
                state = wait1;
                break;
            case stop:
                state = wait2;
                break;
            case wait1:
                state = stop;
                break;
            case wait2:
                state = run;
                break;
        }
    }
}


void __ISR(_TIMER_1_VECTOR, IPL7SRS) _Timer1Interrupt(void){
    T1IF = LOW;
    T1CONbits.ON = 0;
    
}