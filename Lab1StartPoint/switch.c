#include <xc.h>
#include "led.h"
#define OUTPUT 0
#define INPUT 1

#define ENABLE 1
#define DISABLE 0




void initSwitch(){
    
    TRISAbits.TRISA7=INPUT; //enable pin RA7 as an input signal
    CNENAbits.CNIEA7=ENABLE; //Enable change notification for PORTA RA7
    CNPUAbits.CNPUA7=ENABLE;  //This will enable pull up resistor
    
    CNCONAbits.ON=ENABLE; //turn on (1) change notifications for PORTA
    IFS1bits.CNAIF=0;  //put down PORTA interrupt flag
    IPC8bits.CNIP=7;  //configure interrupt priority
    IEC1bits.CNAIE=ENABLE;  //enable interrupt for A pin change notifications*/
    
    /*TRISDbits.TRISD6=INPUT; //enable pin RD6 as an input signal
    CNENDbits.CNIED6=ENABLE; //Enable change notification for PORTA RD6
    CNPUDbits.CNPUD6=ENABLE;  //This will enable pull up resistor
    
    CNCONDbits.ON=ENABLE; //turn on (1) change notifications for PORTD
    IFS1bits.CNDIF=0;  //put down PORTD interrupt flag
    IPC8bits.CNIP=7;  //configure interrupt priority
    IEC1bits.CNDIE=ENABLE;  //enable interrupt for D pin change notifications*/
    
    
}
