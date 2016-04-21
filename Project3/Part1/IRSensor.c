/* Analog Digital Converter */

#include <xc.h>
#include "global_defines.h"
#include "IRSensor.h"

/* Initialize ADC */
void initIR(){
    ANSELBbits.ANSB4 = 1; // Use RB5 as Analog Input    
    ANSELBbits.ANSB3 = 1; // Use RB5 as Analog Input
    ANSELBbits.ANSB2 = 1; // Use RB5 as Analog Input

    AD1CON1bits.FORM = 0; // 16 unsigned integer
    AD1CON1bits.SSRC = 7; // Auto-convert mode
    AD1CON1bits.ASAM = 1; // Auto-sampling
    AD1CON2bits.VCFG = 0; // Use board reference voltages
    AD1CON2bits.CSCNA = 1; // ENABLE scanning
    AD1CON2bits.SMPI = 2; // 1 interrupt per sample completed (:= 1 burrito, apparently)
    AD1CON2bits.ALTS = 0; // Only Mux A
    AD1CON3bits.ADRC = 0; // Use PBCLK
    AD1CON3bits.SAMC = 2; // 2 Tad per sample (AutoSample Time Bits)
    AD1CON3bits.ADCS = 1; // 4 times the PBCLK (ADC Clock Select)
    AD1CHSbits.CH0NA = 0; // Use Vref- as negative reference
    AD1CSSLbits.CSSL2 = 1;// Scan AN2
    AD1CSSLbits.CSSL3 = 1;// Scan AN3
    AD1CSSLbits.CSSL4 = 1;// Scan AN4

  //  AD1CHSbits.CH0SA = 5; // Scan AN5
    AD1CON2bits.BUFM = 0; // 16 word buffer
    IFS0bits.AD1IF = 0; // Put down ADC flag
    IPC5bits.AD1IP = 7; // Default Priority for Interrupt
    IEC0bits.AD1IE = 0; // Disable Interrupt for ADC
    AD1CON1bits.ADON = 1; // turn on the ADC
    
    
}

void checkIR(unsigned char* IRL, unsigned char* IRM, unsigned char* IRR){
    *IRL = (IR_L >= IR_THRESHOLD);
    *IRM = (IR_M >= IR_THRESHOLD);
    *IRR = (IR_R >= IR_THRESHOLD);
}