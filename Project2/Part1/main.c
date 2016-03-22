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
#include "global_defines.h"
#include "timer.h"
//#include "led.h"
#include "keypad.h"
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




volatile unsigned char state;
volatile unsigned char poll;

int position = 0;

int main() {
    SYSTEMConfigPerformance(10000000); //Does something with assembly to set clock speed
    enableInterrupts(); //Make interrupt work
    
   // initTimer1(); // For debouncing Keypad
    initTimer2(); // Used for delay()
    initKeypad();
    initLCD();
    
    delay(500);
    //printCharLCD(0);
    testLCD();
    
 //   state = InitState;
    TRISDbits.TRISD2 = OUTPUT;
    LATDbits.LATD2 = 0;
    
    moveCursorLCD(0,0);
    while (1) {
        if(poll==1){
            printCharLCD(keyScan());
            position++;
            if(position == 31){
                moveCursorLCD(0,1);
            }
            if(position == 63){
                moveCursorLCD(0,0);
                position = 0;
            }
            delay(5000);
            CNCONDbits.ON = 1;
            poll = 0;
        }
        //printCharLCD('C');
    }
    return 0;
}

// Stop-Watch
void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt() {
    IFS0bits.T1IF=0; //put down interrupt flag
}



// After 1 millisecond, set the next state to the next LED

// If button is pressed, sets nextstate to a button state
// Updates state to nextState on button change
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt() {
    IFS1bits.CNDIF=0;//put down interrupt flag
    LATDbits.LATD2 = 1;
   // T1CONbits.ON = 1;
    CNCONDbits.ON = 0;   // Turn of Change notifications. 
    poll = 1;
}