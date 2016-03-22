

#ifndef _LCD_H    /* Guard against multiple inclusion */
#define _LCD_H

#define EN LATEbits.LATE6   /* LCD Read Enable */
#define RS LATEbits.LATE5   /*       */
#define RW LATEbits.LATE4   /*       */
#define D7 LATEbits.LATE3   /* Most Significant Bit */
#define D6 LATEbits.LATE2
#define D5 LATEbits.LATE1
#define D4 LATEbits.LATE0   /* Least Significant Bit */

#define COMMAND 0
#define DATA 1

#define LCD_CLEAR 0x01
#define LCD_HOME 0x02

#define LOWER 1
#define UPPER 0

void writeLCD(unsigned char word, unsigned int commandType, unsigned short int delay);
void writeFourBits(unsigned char word, unsigned int commandType, unsigned short int delayAfter, short int lower);
void initLCD(void);
void clearLCD(void);
void moveCursorLCD(unsigned char x, unsigned char y);
void printCharLCD(unsigned char c);
void printStringLCD(const char* s);
void printTimeLCD(int time);

void testLCD();



#endif /* _LCD_H */

