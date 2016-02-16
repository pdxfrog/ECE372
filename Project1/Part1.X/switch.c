/*
 * File:   switch.c
 * Author: Garrett
 *
 * Created on September 19, 2015, 10:46 AM
 */
#include <xc.h>
#include "switch.h"
#define INPUT 1
#define HIGH 1
#define LOW 0
#define ENABLED 1
#define DISABLED 0
#define DEFAULT 7
void initExtSW(){
    TRISAbits.TRISA7 = INPUT;   // Enable Input
    CNPUAbits.CNPUA7 = HIGH;    // Enable Pullup
    CNENAbits.CNIEA7 = ENABLED; // Enable CN for RA7
    CNCONAbits.ON = ENABLED;    // Enable Change notifications for A register
    CNAIF = LOW;       // Lower interrupt flag
    IPC8bits.CNIP = DEFAULT;    // Set default priority
    IEC1bits.CNAIE = ENABLED;   // Enable CN Interrupt
}
