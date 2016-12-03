

#include "pwm.h"
#include <xc.h>


void initPWM(){

// See timer 3 init for PR values
    
    RPD1Rbits.RPD1R = 0b1011; // Map OC2 to RD1
    OC2CON = 0x0000; // Turn off OC2 for setup
    OC2R = 0x0000; // Initialize compare register
    OC2RS = 0x0000; // Initialize secondary compare register
    OC2CONbits.OCTSEL = 1;  // Use Timer 3 // 0 for timer 2
    OC2CONbits.OCM = 0b110; // PWM Mode // Fault pin disabled
    OC2CONbits.ON = 1;

    
    RPD0Rbits.RPD0R = 0b1100; // Map OC1 to RD0
    OC1CON = 0x0000; // Turn off OC1 for setup
    OC1R = 0x0000; // Initialize compare register
    OC1RS = 0x0000; // Initialize secondary compare register
    OC1CONbits.OCTSEL = 1;  // Use Timer 3 // 0 for timer 2
    OC1CONbits.OCM = 0b110; // PWM Mode // Fault pin disabled
    OC1CONbits.ON = 1;
    
    
  //  OC1CONSET = 0x8000; // Enable OC1
 
    
}