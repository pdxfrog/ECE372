/* 
 * File:   led.c
 * Author: kairu
 * Created January 2016
 */

#include <xc.h>
#include "global_defines.h"
#include "led.h"


void initLEDs(){
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