/* 
 * File:   led.h
 * Author: kairu
 * Adapted from work by gvanhoy
 *
 * Created January 2016
 */

#ifndef LED_H
#define	LED_H

#include <xc.h>

#define OUTPUT 0
#define INPUT 1

#define ENABLE 1
#define DISABLE 0

#define HIGHZ 0
#define LOWZ 1

#define LED1 LATDbits.LATD0
#define LED2 LATDbits.LATD1
#define LED3 LATDbits.LATD2

#define LED1_ON LATD = 0b001
#define LED2_ON LATD = 0b010
#define LED3_ON LATD = 0b100


void initLEDs();
void turnOnLED(int led);





#define RUN_LED TRISGbits.TRISG12
#define STOP_LED TRISGbits.TRISG14


#endif	/* LED_H */

