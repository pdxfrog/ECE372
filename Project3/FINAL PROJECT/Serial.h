
#ifndef _SERIAL_H    /* Guard against multiple inclusion */
#define _SERIAL_H


void initSerial();

void SerialWriteChar(unsigned char c);
unsigned char SerialReadChar(void);

#define SERIAL_FLAG IFS1bits.U2RXIF
#define SERIAL_AVAILABLE U2STAbits.URXDA

//#define SERIAL_FLAG U1STAbits.URXDA


#endif