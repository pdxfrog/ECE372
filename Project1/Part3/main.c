/* 
 * File:   main.c
 * Author: kairu
 * Description: lab 0.
 * Created on February, 2016
 */
// This debugging thing is so useful we left it in the final version. Remove if you don't like it.
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
                  LATGbits.LATG14=LedOFF; //TRD1
                  LATGbits.LATG12=LedON; //TRD2
                  moveCursorLCD(0,0);
                  printStringLCD("Running...");
                  if(counterCN==1){   // If the counter changed...
                      printTimeLCD(counter);
                      counterCN = 0;
                  }
                  if(AllowChange == 0){
                      delay(5000);
                      delay(5000);
                      delay(5000);
                      delay(5000);
                      AllowChange = 1;
                  }
                  if((ReqChange==1) && (AllowChange==1)){
                      state=WAIT1;
                      ReqChange=0;
                      AllowChange=0;  
                    //  CNCONAbits.ON = 1;
                  }
                  break;
                  
              case STOP:
#ifdef _DEBUG_
                  LATDbits.LATD0=1;
                  LATDbits.LATD1=0;
                  LATDbits.LATD2=0;
#endif
                  LATGbits.LATG14=LedON;
                  LATGbits.LATG12=LedOFF;
                  moveCursorLCD(0,0);
                  printStringLCD("Stopped");
                  if(AllowChange == 0){
                      delay(5000);
                      delay(5000);
                      delay(5000);
                      delay(5000);
                      AllowChange = 1;
                  }
                  if(AllowReset == 0){
                      delay(5000);
                      delay(5000);
                      delay(5000);
                      delay(5000);
                      AllowReset = 1;
                  }
                  if((ReqReset==1) && (AllowReset==1)){
                      AllowReset = 0;
                      ReqReset = 0;
                      counter = 0;
                      printTimeLCD(counter);
                  }
                  if((ReqChange==1) && (AllowChange==1)){
                      state=WAIT2;
                      ReqChange=0;
                      AllowChange=0;
                     // CNCONAbits.ON = 1;
                  }
                  break;
                  
              case WAIT1:
#ifdef _DEBUG_
                  LATDbits.LATD0=0;
                  LATDbits.LATD1=1;
                  LATDbits.LATD2=1;
#endif
                  T1CONbits.ON = 0; // Turn off counter
                  if(AllowChange == 0){
                      delay(5000);
                      delay(5000);
                      delay(5000);
                      delay(5000);
                      AllowChange = 1;
                  }
                  if((ReqChange==1) && (AllowChange==1)){
                      state=STOP;
                      ReqChange=0;
                      AllowChange=0;
                      ReqReset = 0; // So we don't reset as soon as we stop...
                      AllowReset = 0;   // See previous line
                     // CNCONAbits.ON = 1;
                  }
                  
                  break;
              case WAIT2:
#ifdef _DEBUG_
                  LATDbits.LATD0=1;
                  LATDbits.LATD1=1;
                  LATDbits.LATD2=0;
#endif
                  T1CONbits.ON = 1; // Turn on counter
                  if(AllowChange == 0){
                      delay(5000);// The sad part is this didn't even work.
                      delay(5000);
                      delay(5000);
                      delay(5000);
                      AllowChange = 1;
                  }
                  if((ReqChange==1) && (AllowChange==1)){   // Button Changed and De-bouncing period is done
                      state=RUN;
                      ReqChange=0;
                      AllowChange=0;
                      //CNCONAbits.ON = 1;
                  }
                  break;
              
              case InitState:// Only happens once
                   state=STOP;
                   clearLCD();
                   counter = 0;
                   printTimeLCD(counter);
                   T1CONbits.ON = 0;
                   TMR1 = 0;

                  break;
              default:// Should never happen. How did you get here?
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
    counterCN = 1;// counter changed, redraw in FSM
    TMR1 = 0;// Clear timer (shouldn't be necessary, but it works)
}

// Debounce External
void __ISR(_TIMER_3_VECTOR, IPL7SRS) _T3Interrupt() {
    IFS0bits.T3IF=0; //put down interrupt flag
    T3CONbits.ON=0;// Turn off timer
    TMR3=0;// Clear Timer
    AllowChange=1;//Debouncing complete
    CNCONAbits.ON=1;// Turn on CN
}


// Debounce Internal
void __ISR(_TIMER_4_VECTOR, IPL7SRS) _T4Interrupt() {
    IFS0bits.T4IF=0; //put down interrupt flag
    T4CONbits.ON=0;// Turn off timer
    TMR4=0;// Reset timer
    AllowReset=1;// Safe to reset clock
    CNCONDbits.ON=1;// Turn CN back on.
}
// After 1 millisecond, set the next state to the next LED

// If button is pressed, sets nextstate to a button state
// Updates state to nextState on button change
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt() {
    PORTA;
    PORTD;
    
    if(IFS1bits.CNAIF){// External Button was pressed or released
        T3CONbits.ON=1;
        ReqChange=1;
        CNCONAbits.ON = 0;  // Without this, no amount of debouncing works with this switch.
    }
    if(IFS1bits.CNDIF){// internal Button was pressed or released
        T4CONbits.ON=1;
        ReqReset=1;
        CNCONDbits.ON=0;    // Not actually necessary, but might be in the future. Doesn't seem to be hurting.
    }
    IFS1bits.CNAIF=0;//put down interrupt flag
    IFS1bits.CNDIF=0;
            
}