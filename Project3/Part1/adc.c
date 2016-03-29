/* Analog Digital Converter */

#include <xc.h>
#include "global_defines.h"
#include "adc.h"

/* Initialize ADC */
void initADC(){
    ANSELBbits.ANSB5 = 1; // Use RB5 as Analog Input
    AD1CON1bits.FORM = 0; // 16 unsigned integer
    AD1CON1bits.SSRC = 7; // Auto-convert mode
    AD1CON1bits.ASAM = 1; // Auto-sampling
    AD1CON2bits.VCFG = 0; // Use board reference voltages
    AD1CON2bits.CSCNA = 0; // Disable scanning
    AD1CON2bits.SMPI = 0; // 1 interrupt per sample completed (:= 1 burrito, apparently)
    AD1CON2bits.ALTS = 0; // Only Mux A
    AD1CON3bits.ADRC = 0; // Use PBCLK
    AD1CON3bits.SAMC = 2; // 2 Tad per sample (AutoSample Time Bits)
    AD1CON3bits.ADCS = 1; // 4 times the PBCLK (ADC Clock Select)
    AD1CHSbits.CH0NA = 0; // Use Vref- as negative reference
    AD1CHSbits.CH0SA = 5; // Scan AN5
    AD1CON2bits.BUFM = 0; // 16 word buffer
    IFS0bits.AD1IF = 0; // Put down ADC flag
    IPC5bits.AD1IP = 7; // Default Priority for Interrupt
    IEC0bits.AD1IE = 0; // Enable Interrupt for ADC
    AD1CON1bits.ADON = 1; // turn on the ADC
    
    
}