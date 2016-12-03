/*
 * Author: Team 205
 * Adapted from work by gvanhoy
 *
 * Created January 2016
 */
#include <xc.h>
#include "global_defines.h"
#include "interrupt.h"
#include "keypad.h"

/*void initSwitch(){
    TRISAbits.TRISA7=INPUT; //enable pin RA7 as an input signal
    CNENAbits.CNIEA7=ENABLED; //Enable change notification for PORTA RA7
    CNPUAbits.CNPUA7=ENABLED;  //This will enable pull up resistor
    
    CNCONAbits.ON=ENABLED; //turn on (1) change notifications for PORTA
    IFS1bits.CNAIF=0;  //put down PORTA interrupt flag
    IPC8bits.CNIP=7;  //configure interrupt priority
    IEC1bits.CNAIE=ENABLED;  //enable interrupt for A pin change notifications
    
    
    TRISDbits.TRISD6=INPUT; //enable pin RD6 as an input signal
    CNENDbits.CNIED6=ENABLED; //Enable change notification for PORTA RD6
    CNPUDbits.CNPUD6=ENABLED;  //This will enable pull up resistor
    
    CNCONDbits.ON=ENABLED; //turn on (1) change notifications for PORTD
    IFS1bits.CNDIF=0;  //put down PORTD interrupt flag
    IPC8bits.CNIP=7;  //configure interrupt priority
    IEC1bits.CNDIE=ENABLED;  //enable interrupt for D pin change notifications
}*/

void initKeypad(){
    // Set Rows as Inputs
    R1_PINMODE = INPUT;
    R2_PINMODE = INPUT;
    R3_PINMODE = INPUT;
    R4_PINMODE = INPUT;
    
    // Enable Pull-Ups on pins
    R1_USECNPU = YES;
    R2_USECNPU = YES;
    R3_USECNPU = YES;
    R4_USECNPU = YES;
    
    R1ISANALOG = NO;
    R2ISANALOG = NO;
    
    // Set Columns as Outputs
    G1_PINMODE = OUTPUT;
    G2_PINMODE = OUTPUT;
    G3_PINMODE = OUTPUT;
    
    // Enable Drain Control
    G1_ODCMODE = ENABLE;
    G2_ODCMODE = ENABLE;
    G3_ODCMODE = ENABLE;
    
    // Open Drains
    G1_ODCSETZ = LOW_Z;
    G2_ODCSETZ = LOW_Z;
    G3_ODCSETZ = LOW_Z;
    
    // Enable Interrupts on pins
    R1_CNIEBIT = ENABLE;
    R2_CNIEBIT = ENABLE;
    R3_CNIEBIT = ENABLE;
    R4_CNIEBIT = ENABLE;
    
    CNCONDbits.ON = 1; // Enable Change Notifications
    IPC8bits.CNIP=7;  //configure interrupt priority
    IEC1bits.CNDIE=ENABLE;  //enable interrupt for D pin change notifications
}
// Return what key is currently pressed
unsigned char keyScan(){
    int i = 0;
    int j = 0;
    const unsigned char keys[4][3] = {
        {'*', '0', '#'},
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}};
    unsigned char presses[4][3] = {0};

  //  for(i=0;i<3;i++){ // Poll Pins
        GA_ODCSETZ |= SETALLHIGH;
        // Clear bit 12,13,14 by shifting 1 and inverting
        //GA_ODCSETZ &= !(0x1<<(i+12)); // Trust But Verify
        G1_ODCSETZ = LOW_Z;
        G2_ODCSETZ = HIGH_Z;
        G3_ODCSETZ = HIGH_Z;
        delay(500);
        presses[0][0] = !R4_PINREAD;
        presses[1][0] = !R1_PINREAD;
        presses[2][0] = !R2_PINREAD;
        presses[3][0] = !R3_PINREAD;
        
        G1_ODCSETZ = HIGH_Z;
        G2_ODCSETZ = LOW_Z;
        G3_ODCSETZ = HIGH_Z;
        delay(500);
        presses[0][1] = !R4_PINREAD;
        presses[1][1] = !R1_PINREAD;
        presses[2][1] = !R2_PINREAD;
        presses[3][1] = !R3_PINREAD;
        
        G1_ODCSETZ = HIGH_Z;
        G2_ODCSETZ = HIGH_Z;
        G3_ODCSETZ = LOW_Z;
        delay(500);
        presses[0][2] = !R4_PINREAD;
        presses[1][2] = !R1_PINREAD;
        presses[2][2] = !R2_PINREAD;
        presses[3][2] = !R3_PINREAD;
        
    //}
        GA_ODCSETZ &= SETALLLOWZ;
    for(i=0;i<4;i++){ // Decide what to return
        for(j=0;j<3;j++){
            if(presses[i][j]){
                return keys[i][j];
            }
        }
    }
        return 'f';
}