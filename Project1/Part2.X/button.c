/*
 * Author: kairu
 * Adapted from work by gvanhoy
 *
 * Created January 2016
 */
#include <xc.h>
#include "button.h"
#define INPUT 1
#define OUTPUT 0
#define ENABLED 1
#define DISABLED 0
void initSW1(){
    TRISDbits.TRISD6 = INPUT;
    CNCONDbits.ON = 1;
    CNENDbits.CNIED6 = ENABLED;//CN pin
    CNPUDbits.CNPUD6 = ENABLED;//CN pullup
    IFS1bits.CNDIF = 0;//Flag down
    IPC8bits.CNIP = 7;//priority
    IEC1bits.CNDIE = ENABLED;
}