/*
 * File:   lcd.h
 * Authors:
 *
 * Created on December 31, 2014, 1:39 PM
 */


    #define DB4 LATEbits.LATE0
    #define DB5 LATEbits.LATE1
    #define DB6 LATEbits.LATE2
    #define DB7 LATEbits.LATE3
    #define RW  LATEbits.LATE4
    #define RS  LATEbits.LATE5
    #define ENABLE  LATEbits.LATE6


void writeLCD(unsigned char word, unsigned int commandType, unsigned int delay);
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower);
void initLCD(void);
void clearLCD(void);
void moveCursorLCD(unsigned char x, unsigned char y);
void printCharLCD(char c);
void printStringLCD(const char* s);
void testLCD();