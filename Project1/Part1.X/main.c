// ******************************************************************************************* //
//
// File:         lab1p1.c
// Date:         
// Authors:      
//
// Description: Part 1 for lab 1
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
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
    
    
int main(void)
{
    SYSTEMConfigPerformance(10000000);
    initTimer1();
    initLEDs();
    initExtSW();
    enum{
        run, stop, wait1, wait2
    };
     state = run;
     nextState = run;
     timerFinished = 0;
     runState = 0;

    
    while(1)
    {
        switch(state){
            case run:
                setLED(RUN_LED);               
                timerOn();
                nextState = wait1;
                break;
            case wait1:
                timerOn();
                nextState = stop;
                break;
            case stop:         
                setLED(STOP_LED);
                timerOn();
                nextState = wait2;
                break;
            case wait2:              
                timerOn();
                nextState = run;
                break;
            default:
                break;
        }
    }
    
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
    CNAIF = LOW;

    if(timerFinished){
        state = nextState;
        timerFinished = 0;
    }
    

}

void __ISR(_TIMER_1_VECTOR, IPL7SRS) _Timer1Interrupt(void){
    T1IF = LOW;
    T1CONbits.ON = 0;
    timerFinished = 1;

}