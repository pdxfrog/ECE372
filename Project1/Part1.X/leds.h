/* 
* File:   leds.h
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#ifndef LEDS_H
#define	LEDS_H

#define RUN_LED 0x2000
#define STOP_LED 0x0800
void initLEDs();
void swapLEDs();
void setLED(int led);

#endif	/* LEDS_H */

