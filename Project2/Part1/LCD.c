/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
#include <xc.h>
#include "LCD.h"
#include "timer.h"

void writeLCD(unsigned char word, unsigned int commandType, unsigned short int delay){
    writeFourBits(word, commandType, delay, UPPER);
    writeFourBits(word, commandType, delay, LOWER);
}
void writeFourBits(unsigned char word, unsigned int commandType, unsigned short int delayAfter,  short int lower){
    LATE = 0x0000;
    EN = 0;
    if(lower){  
        LATE |= (word & 0xF);
    }
    else{
        LATE |= (word>>4); 
    }
    RS = commandType & 0x01;
    delay(1);
    EN = 1;
    delay(1);
    EN = 0; 
    delay(delayAfter);
}
void initLCD(void){
    TRISE = 0x00; // Set first six bits in TRISE to 0
    
    // Wait to make absolutely certain power is on.
    delay(7500);
    delay(7500);
    // Gave delays 10% margin
    writeFourBits(0x03, COMMAND, 4510, LOWER);
    
    writeFourBits(0x03, COMMAND, 110, LOWER);
    
    writeFourBits(0x03, COMMAND, 40, LOWER);
    
    writeFourBits(0x02, COMMAND, 40, LOWER);
    
    writeFourBits(0x28, COMMAND, 10, UPPER);
    writeFourBits(0x28, COMMAND, 50, LOWER);
    
    writeFourBits(0x08, COMMAND, 10, UPPER);
    writeFourBits(0x08, COMMAND, 50, LOWER);
    
    writeFourBits(0x01, COMMAND, 10, UPPER);
    writeFourBits(0x01, COMMAND, 1804, LOWER);
    
    writeFourBits(0x06, COMMAND, 10, UPPER);
    writeFourBits(0x06, COMMAND, 50, LOWER);
    
    writeFourBits(0x0F, COMMAND, 50, UPPER);
    writeFourBits(0x0F, COMMAND, 50, LOWER);
}
void clearLCD(void){
    // Clear Screen
    writeLCD(LCD_CLEAR, COMMAND, 1640);
}
void moveCursorLCD(unsigned char x, unsigned char y){
    unsigned char word = 0x80;
    word |= (x & 0x0F);
    if(y){
        word |= 0x40;
    }
    writeLCD(word, COMMAND, 50);
}
void printCharLCD(unsigned char c){
    writeLCD(c, DATA, 55);
   // writeFourBits(c, DATA, 0, UPPER);
   // writeFourBits(c, DATA, 51, LOWER);
}
void printStringLCD(const char* s){
    while(*s != '\0'){
        printCharLCD(*s);
        s++;
    }
}

void printTimeLCD(int time){
    char timeString[9] = {"\0"};
    int mm = time/6000; // integer division for the win
    int ss = (time%6000)/100;         
    int nn = time%100;
    moveCursorLCD(0,1);
    sprintf(timeString, "%02d:%02d:%02d", mm,ss,nn);
    printStringLCD(timeString); 
}



void testLCD(){
    clearLCD();
    moveCursorLCD(0,0);
    printStringLCD(" DUNCAN  JULIAN ");
    moveCursorLCD(0,1);
    printStringLCD(" KYLE    SULTAN ");
}






