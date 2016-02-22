/* 
 * File:   main.c
 * Author: kairu
 * Description: lab 0.
 * Created on February, 2016
 */
#define _DEBUG_
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

volatile unsigned char ReqChange=0;
volatile unsigned char AllowChange=0;

volatile unsigned char ReqReset=0;
volatile unsigned char AllowReset=0;

volatile int counter = 0;
volatile unsigned char counterCN = 0;

volatile int porta;
volatile int portd;

int main() {
    SYSTEMConfigPerformance(10000000); //Does something with assembly to set clock speed
    enableInterrupts(); //Make interrupt work

    initLEDs();
    initTimer1();
    initTimer2();
    initTimer3();
    initTimer4();
    initSwitch();
    
    
    porta = PORTA;
    portd = PORTD;
    
    initLCD();
    delay(500);
    //printCharLCD(0);
    testLCD();
    
    state = InitState;
    nextState = InitState;

    while (1) {
        switch (state) {
            case RUN:
#ifdef _DEBUG_
                  LATDbits.LATD0=0;
                  LATDbits.LATD1=0;
                  LATDbits.LATD2=1;
#endif
                  LATGbits.LATG12=LedOFF; //TRD1
                  LATGbits.LATG14=LedON; //TRD2
                  
                  if(counter==0 || counterCN==1){   // If the counter changed...
                      printTimeLCD(counter);
                      counterCN = 0;
                  }
                  
                  if((ReqChange==1) && (AllowChange==1)){
                      state=WAIT1;
                      ReqChange=0;
                      AllowChange=0;  
                  }
                  break;
                  
              case STOP:
#ifdef _DEBUG_
                  LATDbits.LATD0=1;
                  LATDbits.LATD1=0;
                  LATDbits.LATD2=0;
#endif
                  LATGbits.LATG12=LedON;
                  LATGbits.LATG14=LedOFF;
                  
                  if((ReqReset==1) && (AllowReset)){
                      AllowReset = 0;
                      ReqReset = 0;
                      counter = 0;
                  }
                  if((ReqChange==1) && (AllowChange==1)){
                      state=WAIT2;
                      ReqChange=0;
                      AllowChange=0;
                  }
                  break;
                  
              case WAIT1:
#ifdef _DEBUG_
                  LATDbits.LATD0=0;
                  LATDbits.LATD1=1;
                  LATDbits.LATD2=1;
#endif
                  T1CONbits.ON = 0; // Turn off counter
                  if((ReqChange==1) && (AllowChange==1)){
                      state=STOP;
                      ReqChange=0;
                      AllowChange=0;
                      ReqReset = 0; // So we don't reset as soon as we stop...
                      AllowReset = 0;   // See previous line
                  }
                  
                  break;
              case WAIT2:
#ifdef _DEBUG_
                  LATDbits.LATD0=1;
                  LATDbits.LATD1=1;
                  LATDbits.LATD2=0;
#endif
                  T1CONbits.ON = 1; // Turn on counter
                  if((ReqChange==1) && (AllowChange==1)){   // Button Changed and De-bouncing period is done
                      state=RUN;
                      ReqChange=0;
                      AllowChange=0;
                  }
                  break;
              
              case InitState:
                   state=STOP;
                   counter = 0;
                   T1CONbits.ON = 0;
                   TMR1 = 0;
                   CNCONDbits.ON = 0;
                   CNCONAbits.ON = 1;
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

// Stop-Watch
void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt() {
    IFS0bits.T1IF=0; //put down interrupt flag
    counter++;  // increment counter
    counterCN = 1;
}

// Debounce External
void __ISR(_TIMER_3_VECTOR, IPL7SRS) _T3Interrupt() {
    IFS0bits.T3IF=0; //put down interrupt flag
    T3CONbits.ON=0;
    TMR3=0;
    AllowChange=1;
    CNCONAbits.ON=1;
}


// Debounce Internal
void __ISR(_TIMER_4_VECTOR, IPL7SRS) _T4Interrupt() {
    IFS0bits.T4IF=0; //put down interrupt flag
    T4CONbits.ON=0;
    TMR4=0;
    AllowReset=1;
    CNCONDbits.ON=1;
}
// After 1 millisecond, set the next state to the next LED

// If button is pressed, sets nextstate to a button state
// Updates state to nextState on button change
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt() {
    //IFS1bits.CNDIF=0;
    
    PORTA;
    PORTD;
    if(IFS1bits.CNAIF){
        T3CONbits.ON=1;
        ReqChange=1;
        porta = PORTA;
        CNCONAbits.ON=0;
    }
    if(IFS1bits.CNDIF){
        T4CONbits.ON=1;
        ReqReset=1;
        portd = PORTD;
        CNCONDbits.ON = 0;
    }
    IFS1bits.CNAIF=0;//put down interrupt flag
    IFS1bits.CNDIF=0;
    T3CONbits.ON=1;
            
}