/*
* File:   leds.c
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#include <xc.h>
#define OUTPUT 0

void initLEDs(){
    ODCGbits.ODCG12 = 1;
    ODCGbits.ODCG14 = 1;
    TRISGbits.TRISG12 = OUTPUT;
    TRISGbits.TRISG14 = OUTPUT;
    
    LATG = 0x2000; // Turn on Run LED
    
}

void swapLEDs(){
    LATG ^= 0x2800; // Swap LEDs
}

void setLED(int led){
    LATG = led;
}