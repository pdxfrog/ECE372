/* 
 * File:   main.c
 * Author: kairu
 * Description: lab 0.
 * Created on February, 2016
 */

#include <xc.h>
#include <sys/attribs.h>
#include "timer.h"
#include "led.h"
#include "button.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1

typedef enum stateTypeEnum {
    led1, button1, led2, button2, led3, button3
} stateType;

volatile unsigned char state;
volatile unsigned char nextState;

int main() {
    SYSTEMConfigPerformance(10000000); //Does something with assembly to set clock speed
    enableInterrupts(); //Make interrupt work

    initLEDs();
    initTimer1();
    initTimer2();
    initSW1();
    state = led1;

    while (1) {
        switch (state) {
            case led1:
                LED1_ON;
                //timer1Off();
                break;
            case button1:
                //timer1On();
                break;
            case led2:
                LED2_ON;
                //timer1Off();
                break;
            case button2:
                //timer1On();
                break;
         //   case led3:
           //     LED3_ON;
             //   timer1Off();
               // break;
         //   case button3:
           //     timer1On();
             //   break;
        }
    }
    return 0;
}

// After 1 Second set next-state to the previous LED
void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt() {
    IFS0bits.T1IF = 0;
    TMR1 = 0;
    
    T1CONbits.ON = 0;
    PORTD;
    if (BUTTON1 == PRESSED) {

        switch (state) {
            case button1:
                nextState = led2;
                break;
            case button2:
                nextState = led1;
                break;
         //   case button3:
           //     nextState = led1;
             //   break;
            default:
                break;
        }
    }
}

// After 1 millisecond, set the next state to the next LED
void __ISR(_TIMER_2_VECTOR, IPL7SRS) _T2Interrupt() {
    IFS0bits.T2IF = 0;
    TMR2 = 0;
    T2CONbits.ON = 0;
    PORTD;
    if (BUTTON1 == PRESSED) {

        switch (state) {
            case button1:
                nextState = led2;
                break;
            case button2:
                nextState = led1;
                break;
         //   case button3:
           //     nextState = led1;
             //   break;
            default:
                break;
        }
    }
}
// If button is pressed, sets nextstate to a button state
// Updates state to nextState on button change
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt() {
    IFS1bits.CNDIF = 0; //Flag down
    PORTD;
    if (BUTTON1 == PRESSED) {
        T1CONbits.ON = 1;
        switch (state) {
            case led1:
                nextState = button1;
                break;
            case led2:
                nextState = button2;
                break;
        //    case led3:
          //      nextState = button3;
            //    break;
            default:
                break;
        }
    }
    state = nextState;
    IFS1bits.CNDIF = 0;
}