/* 
 * File:   led.c
 * Author: kairu
 * Created January 2016
 */

#include <xc.h>
#include "led.h"



void initLEDs(){
    TRISDbits.TRISD0 = 0;    
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
}
