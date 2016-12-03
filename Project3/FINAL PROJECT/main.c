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
//#include "adc.h"
#include "pwm.h"
#include "drive.h"
#include "IRSensor.h"
#include "Serial.h"
#define DOWN 0
#define UP 1

#define LedON 1
#define LedOFF 0



#define MAX_VOLTAGE 500


volatile unsigned char state;
volatile unsigned char poll;
volatile unsigned int IRLval, IRMval, IRRval;
volatile int count;
volatile int keyCount;



int position = 0;

unsigned char overrideMode = 0;


int main() {
    count=0;
    SYSTEMConfigPerformance(10000000); //Does something with assembly to set clock speed
    enableInterrupts(); //Make interrupt work
    
    initPWM();
    initDrive();
    
    stop();
    

    
    initTimer1(); // For 2s delay
    initTimer2(); // Used for delay()
    initTimer3();

    initSerial();
    
    initLCD();
    TRISDbits.TRISD2 = OUTPUT;
    LATDbits.LATD2 = 0;
    delay(500);
    initIR();



    
    
    
    
    
    int direction = 1;
    unsigned int speedLeft = 0;
    unsigned int speedRight = 0;
    
    keyCount = 0;
    state = 0;
    
    int crossCount = 0;
    int returnTrip = 0;
    int onCross = 0;
    
    unsigned char IRL, IRM, IRR;
    unsigned char allowLeftTurn = 1;
    printCharLCD('H');
    while(overrideMode != 'I'){
       SerialWriteChar('I');
       
       if(SERIAL_AVAILABLE){
            SERIAL_FLAG = 0;
            moveCursorLCD(15, 1);
            overrideMode = U2RXREG;
            delay(50);
            printCharLCD(overrideMode);

            LATDbits.LATD2 = 1;
        }
        else{
            LATDbits.LATD2 = 0;
        }

        
    }
    while (1) {
       
        // Update IR Sensor States
        
        if(ADC_FLAG){
            ADC_FLAG = 0;     
            checkIR(&IRL, &IRM, &IRR);
            moveCursorLCD(0,0);
            printCharLCD(IRR + '0');
            
            moveCursorLCD(5,0);
            printCharLCD(IRM + '0');
            
            moveCursorLCD(10,0);
            printCharLCD(IRL + '0');
            
            moveCursorLCD(0,1);
            printVoltageLCD((IR_R*MAX_VOLTAGE)/1023);
            moveCursorLCD(5,1);
            printVoltageLCD((IR_M*MAX_VOLTAGE)/1023);
            moveCursorLCD(10,1);
            printVoltageLCD((IR_L*MAX_VOLTAGE)/1023);
        }
        
        if(SERIAL_AVAILABLE){    // Serial data available
            SERIAL_FLAG = 0;    // Lower flag
            stop();
            overrideMode = SerialReadChar();    // read char
            SerialWriteChar('A');
            moveCursorLCD(0, 0);
            printStringLCD("OVERRIDE MODE");
            moveCursorLCD(15, 1);
            printCharLCD(overrideMode);
            while(overrideMode != 'N'){
                switch(overrideMode){
                    case 'F':
                        forward();
                        break;
                    case 'T':
                        turnAround();
                        break;
                    case 'R':
                        turnRight();
                        break;
                    case 'L':
                        turnLeft();
                        break;
                    case 'B':
                        backward();
                        break;
                    case 'S':
                        overrideMode = 'N';
                        break;
                    case 'P':
                        stop();
                        break;
                    case '\n':
                        break;
                    default:
                        break;
                }
                if(SERIAL_AVAILABLE){
                    SERIAL_FLAG = 0;
                    overrideMode = SerialReadChar();
                    SerialWriteChar('A');
                    moveCursorLCD(15, 1);
                    printCharLCD(overrideMode);
                }
                else{
                  //  moveCursorLCD(15, 1);
                  //  printCharLCD('Q');
                    
                }
            }
            clearLCD();
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
        
        if(IRM){
            DEFAULT_SPEED = 700;    // 700
            stop();
            delay(500); 
        }
        else{
            DEFAULT_SPEED = 700;    // 750
        }
        
        // States
        if((!IRL && !IRR)){
            forward();
            // Count how many cross bars we have seen
            /*if(onCross){
                onCross = 0;
                crossCount++;
                moveCursorLCD(15,0);
                printCharLCD('0' + crossCount);
                if(crossCount == 3){ // Only turn around once
                    DEFAULT_SPEED = 590;  // Change turn speed
                    turnAround(); // Need to modify this to turn 18 degrees
                    delaySeconds(2); // Modify time to make it actually turn 180
                    backward();
                    delayQuarterSeconds(3);
                    allowLeftTurn = 0;
                }
            }*/

        }
        else if(IRL && IRR && IRM){
            stop();
           // onCross = 1;
            forward();

        }
        else if(IRL && IRM){
          //  if(allowLeftTurn){
               pivotLeft(); 
            //}
            //else{
                //forward();
            //}
        }
        else if(IRL){
            pivotLeft();

        }
        else if(IRR){
            pivotRight();

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

