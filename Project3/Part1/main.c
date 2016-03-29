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
#include <stdlib.h>
#include "global_defines.h"
#include "timer.h"
//#include "led.h"
#include "keypad.h"
#include "interrupt.h"
#include "config.h"
#include "LCD.h"
#include "lock.h"
#include "adc.h"
#include "pwm.h"
#include "drive.h"

#define DOWN 0
#define UP 1

#define LedON 1
#define LedOFF 0

#define InitState 0
#define RUN 1
#define WAIT1 2
#define STOP 3
#define WAIT2 4

#define MAX_VOLTAGE 500


volatile unsigned char state;
volatile unsigned char poll;
volatile unsigned int adcValue;
volatile int count;
volatile int keyCount;

int position = 0;


int main() {
    count=0;
    SYSTEMConfigPerformance(10000000); //Does something with assembly to set clock speed
    enableInterrupts(); //Make interrupt work
    
    initTimer1(); // For 2s delay
    initTimer2(); // Used for delay()
    initTimer3();
    initKeypad();
    initLCD();
    TRISDbits.TRISD3 = OUTPUT;
    delay(500);
    initADC();

    TRISDbits.TRISD2 = OUTPUT;
    LATDbits.LATD2 = 0;

    moveCursorLCD(0,0);
    printStringLCD("Voltage:");
    adcValue = 0;
    
    initPWM();
    
    initDrive();
    int direction = 1;
    unsigned int speedLeft = 0;
    unsigned int speedRight = 0;
    
    keyCount = 0;
    state = 0;
    while (1) {
       
        moveCursorLCD(0,1);
        if(ADC_FLAG){
            ADC_FLAG = 0;
            if(adcValue!=ADC_BUFF){
               adcValue = ADC_BUFF; 
               printVoltageLCD((adcValue*MAX_VOLTAGE)/1023);
               calcSpeedLeftRight(adcValue, 1023, &speedLeft, &speedRight);
               drive(speedLeft, speedRight, direction);
            }
            
        }
        
        if(poll){
            poll = 0;
            keyCount++;
            delay(50);
            CNCONDbits.ON = 1;
        }
        
        if(keyCount >= 2){
            keyCount = 0;
            state++;
            if(state>3){
                state = 0;
            }
        }
        
        // States
        switch(state){
            case 0: 
                direction = 0;
                break;
            case 1:
                direction = 1;
                break;
            case 2:
                direction = 0;
                break;
            case 3:
                direction = -1;
                break;
            default:    // Return to default
                direction = 0;
                state = 0;
                break;            
        }
        
        
        
        
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

// ISR Causes Problems
void __ISR(_ADC_VECTOR, IPL7AUTO) _ADCInterrupt(){
    ADC_FLAG = 0;
    adcValue = (ADC_BUFF*460)/1023; // maths
    LATDbits.LATD3 ^= 1;
}