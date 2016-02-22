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


void initSwitch(){
    TRISAbits.TRISA7=INPUT; //enable pin RA7 as an input signal
    CNENAbits.CNIEA7=ENABLED; //Enable change notification for PORTA RA7
    CNPUAbits.CNPUA7=ENABLED;  //This will enable pull up resistor
    
    CNCONAbits.ON=ENABLED; //turn on (1) change notifications for PORTA
    IFS1bits.CNAIF=0;  //put down PORTA interrupt flag
    IPC8bits.CNIP=7;  //configure interrupt priority
    IEC1bits.CNAIE=ENABLED;  //enable interrupt for A pin change notifications*/
    
    
    TRISDbits.TRISD6=INPUT; //enable pin RD6 as an input signal
    CNENDbits.CNIED6=ENABLED; //Enable change notification for PORTA RD6
    CNPUDbits.CNPUD6=ENABLED;  //This will enable pull up resistor
    
    CNCONDbits.ON=ENABLED; //turn on (1) change notifications for PORTD
    IFS1bits.CNDIF=0;  //put down PORTD interrupt flag
    IPC8bits.CNIP=7;  //configure interrupt priority
    IEC1bits.CNDIE=ENABLED;  //enable interrupt for D pin change notifications
}