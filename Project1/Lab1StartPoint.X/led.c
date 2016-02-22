/* 
 * File:   led.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:15 PM
 */

#include <xc.h>
#include "led.h"
#define OUTPUT 0
#define INPUT 1

#define ENABLE 1
#define DISABLE 0

//#define HIGHZ 0
//#define LOWZ 1

void initLEDs(){
//internal LEDs
    TRISDbits.TRISD0=OUTPUT;
    LATDbits.LATD0=0;
    TRISDbits.TRISD1=OUTPUT;
    LATDbits.LATD1=0;
    TRISDbits.TRISD2=OUTPUT;
    LATDbits.LATD2=0;
    
    TRISGbits.TRISG12=OUTPUT;
    ODCGbits.ODCG12=ENABLE;
    LATGbits.LATG12=0;
    TRISGbits.TRISG14=OUTPUT;
    ODCGbits.ODCG14=ENABLE;
    LATGbits.LATG14=0;
    
    
}

void turnOnLED(int led){
    
    //TODO: You may choose to write this function
    // as a matter of convenience
    
}