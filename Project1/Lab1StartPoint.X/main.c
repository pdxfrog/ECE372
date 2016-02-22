/* 
 * File:   main.c
 * Author: gvanhoy
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1
#define DOWN 0
#define UP 1

#define LedON 0
#define LedOFF 1

#define InitState 0
#define RUN 1
#define WAIT1 2
#define STOP 3
#define WAIT2 4



//TODO: Define states of the state machine
//typedef enum stateTypeEnum{
//} stateType;

//TODO: Use volatile variables that change within interrupts
volatile int ReqChange=0;
volatile int AllowChange=0;



int main() {
    SYSTEMConfigPerformance(10000000);    //Configures low-level system parameters for 10 MHz clock
    enableInterrupts();                   //This function is necessary to use interrupts.

    
    initLEDs(); //initialize external LEDs with ODC pins
    initTimer1(); //initialize internal timer to 5ms delay
    initSwitch(); //init external switch with external PUR
    
    int state=InitState;
    int NextState=0;    
   
    

    
    while(1){
        
        /*if (AllowChange==1){
            state=NextState;
            AllowChange=0;
            
        }*/
        
        
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
                   state=RUN;
                  break;
              default:
                   state=InitState;
                  break;
        
        }
        
    }
    
    return 0;
}

//TODO: Add interrupt service routines that manage the change of states
//for particular events as needed
void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt(){
    IFS0bits.T1IF=0; //put down interrupt flag
    T1CONbits.ON=0;
    TMR1=0;//turn off timer
    AllowChange=1;
    CNCONAbits.ON=1;
    
    
    
              
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(){
    //IFS1bits.CNDIF=0;
    IFS1bits.CNAIF=0;//put down interrupt flag
    T1CONbits.ON=1;
    ReqChange=1;
    CNCONAbits.ON=0;
    
    
   
    
    
    
}