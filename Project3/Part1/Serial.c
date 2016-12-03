

#include <xc.h>
#include "global_defines.h"
#include "Serial.h"
#include "timer.h"

#define RPF4 0b0010
#define U2TX 0b0001
#define P8N1 0
void initSerial(){
    U2RXRbits.U2RXR = RPF4;    // RPF4
    RPF5Rbits.RPF5R = U2RX;    // U2TX
    U2BRG = ((10000000/9600)/16) - 1;                  // Baud rate generator prescaler
    U2MODEbits.PDSEL = P8N1;        // Parity select (depends on device) (8-N-1)
    U2MODEbits.STSEL = P8N1;        // One stop bit
    U2MODEbits.UEN = NO;          // Only control RX and TX pins
    U2MODEbits.BRGH = NO;         // Not high speed
    
    U2STAbits.URXISEL = 0b00;
//    IEC1bits.U1RXIE = 0;
    U2STAbits.URXEN = 1;         // Enable the receive pin (TRIS not needed)
    U2STAbits.UTXEN = 1;         // Enable the transmit pin (TRIS not needed)
    U2MODEbits.ON = 1;           // Enable UART
}


void SerialWriteChar(unsigned char c){
    U2TXREG = c;
    delay(2);
}



unsigned char SerialReadChar(void){
    return U2RXREG;
}