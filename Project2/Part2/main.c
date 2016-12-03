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
#include "lock.h"

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
volatile int count;


int position = 0;


int main() {
    int keepGoing = YES;
    count=0;
    SYSTEMConfigPerformance(10000000); //Does something with assembly to set clock speed
    enableInterrupts(); //Make interrupt work
    
    initTimer1(); // For 2s delay
    initTimer2(); // Used for delay()
    initKeypad();
    initLCD();
    
    delay(500);
    //printCharLCD(0);
  //  testLCD();
    initLock();
    
 //   state = InitState;
    TRISDbits.TRISD2 = OUTPUT;
    LATDbits.LATD2 = 0;
    
    moveCursorLCD(0,0);
  
    while (1) {
        moveCursorLCD(0,0);
        printStringLCD("ENTER");
        while(!poll); // Wait for keypress
        if(poll==1){
            //printCharLCD(keyScan());
            switch(readCode(keyScan())){
                case SET_MODE:
                    clearLCD();
                    printStringLCD("SET MODE");
                    keepGoing = YES;
                    while(!poll);// Wait for key release
                    poll = 0;
                    CNCONDbits.ON = 1;
                    while(keepGoing){// DO this until told to stop
                        while(!poll);
                        
                            switch(readCode(keyScan())){
                                case SET_MODE: // double asterisk
                                    clearLCD();
                                    printStringLCD("INVALID");
                                    delaySeconds(2);
                                    clearLCD();
                                    keepGoing = NO; // Don't keep going
                                    break;
                                case FILLED: // Buffer is full
                                    if(setCode()){ // Code was valid
                                        clearLCD();
                                        printStringLCD("VALID");
                                        delaySeconds(2); 
                                        clearLCD();
                                    }
                                    else{
                                        clearLCD();
                                        printStringLCD("INVALID");
                                        delaySeconds(2);
                                        clearLCD();
                                    }
                                    keepGoing = NO;
                                    break;
                                case NOT_FILLED:
                                    // DO Nothing
                                    break;
                            }
                            poll = 0;
                            CNCONDbits.ON = 1;
                    }
                    break;
                case FILLED:
                    if(compareCode()){ // If code is valid
                        clearLCD();
                        printStringLCD("GOOD");
                        // Hang two Seconds
                        delaySeconds(2);
                        clearLCD();
                    }
                    else{// code is not valid
                        clearLCD();
                        printStringLCD("BAD");
                        // Hang two Seconds
                        delaySeconds(2);
                        clearLCD();
                    }
                    break;
                case NOT_FILLED:
                    // DO Nothing
                    break;  
            }
            /*position++;
            if(position == 32){
                moveCursorLCD(0,1);
            }
            if(position == 64){
                moveCursorLCD(0,0);
                position = 0;
            }*/
            delay(500);
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
    count++;
}



// After 1 millisecond, set the next state to the next LED

// If button is pressed, sets nextstate to a button state
// Updates state to nextState on button change
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt() {
    IFS1bits.CNDIF=0;//put down interrupt flag
    LATDbits.LATD2 ^= 1;//toggle led for visual debugging aid
   // T1CONbits.ON = 1;
    CNCONDbits.ON = 0;   // Turn of Change notifications. 
    poll = 1;// Flag for key press
}