/* 
 * File:   main.c
 * Author: kairu
 * Description: lab 0.
 * Created on February, 2016
 */

/*
 * Notes: Register E is reserved for the LCD
 *        Register A is for input
 *        Register D is on-board components
 */

#include <xc.h>
#include <sys/attribs.h>
#include "timer.h"
#include "led.h"
#include "button.h"
#include "interrupt.h"
#include "config.h"
#include "LCD.h"

#define DOWN 0
#define UP 1

#define LedON 1
#define LedOFF 0

#define InitState 0
#define RUN 1
#define WAIT1 2
#define STOP 3
#define WAIT2 4


#define OUTPUT 0
#define INPUT 1


volatile unsigned char state;
volatile unsigned char nextState;

volatile int ReqChange=0;
volatile int AllowChange=0;

int main() {
    SYSTEMConfigPerformance(10000000); //Does something with assembly to set clock speed
    enableInterrupts(); //Make interrupt work

    initLEDs();
    initTimer1();
    initTimer2();
    initSwitch();
    initLCD();
    delay(500);
    //printCharLCD(0);
    testLCD();
    
    state = InitState;
    nextState = InitState;

    while (1) {
        switch (state) {
            case RUN:
                  LATDbits.LATD0=0;
                  LATDbits.LATD1=0;
                  LATDbits.LATD2=1;
                  LATGbits.LATG12=LedOFF; //TRD1
                  LATGbits.LATG14=LedON; //TRD2
                  if((ReqChange==1) && (AllowChange==1)){
                      state=WAIT1;
                      ReqChange=0;
                      AllowChange=0;  
                  }
                  break;
                  
              case STOP:
                  LATDbits.LATD0=1;
                  LATDbits.LATD1=0;
                  LATDbits.LATD2=0;
                  LATGbits.LATG12=LedON;
                  LATGbits.LATG14=LedOFF;
                  if((ReqChange==1) && (AllowChange==1)){
                      state=WAIT2;
                      ReqChange=0;
                      AllowChange=0;
                  }
                  break;
                  
              case WAIT1:
                  LATDbits.LATD0=0;
                  LATDbits.LATD1=1;
                  LATDbits.LATD2=1;
                  if((ReqChange==1) && (AllowChange==1)){
                      state=STOP;
                      ReqChange=0;
                      AllowChange=0;
                  }
                  
                  break;
              case WAIT2:
                  LATDbits.LATD0=1;
                  LATDbits.LATD1=1;
                  LATDbits.LATD2=0;
                  if((ReqChange==1) && (AllowChange==1)){
                      state=RUN;
                      ReqChange=0;
                      AllowChange=0;
                  }
                  break;
              
              case InitState:
                   state=STOP;
                  break;
              default:
                   state=InitState;
                   ReqChange = 0;
                   AllowChange=0;
                  break;
        }
    }
    return 0;
}

// After 1 Second set next-state to the previous LED
void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt() {
    IFS0bits.T1IF=0; //put down interrupt flag
    T1CONbits.ON=0;
    TMR1=0;//turn off timer
    AllowChange=1;
    CNCONAbits.ON=1;
}

// After 1 millisecond, set the next state to the next LED

// If button is pressed, sets nextstate to a button state
// Updates state to nextState on button change
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt() {
    //IFS1bits.CNDIF=0;
    IFS1bits.CNAIF=0;//put down interrupt flag
    T1CONbits.ON=1;
    ReqChange=1;
    CNCONAbits.ON=0;
            
}