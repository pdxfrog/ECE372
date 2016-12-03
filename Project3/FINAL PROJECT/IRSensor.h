


#ifndef _IR_H    /* Guard against multiple inclusion */
#define _IR_H


void initIR();

void checkIR(unsigned char* IRL, unsigned char* IRM, unsigned char* IRR);

#define ADC_FLAG IFS0bits.AD1IF

#define IR_L ADC1BUF0
#define IR_M ADC1BUF2
#define IR_R ADC1BUF1

#define IR_THRESHOLD 50





#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
