


#include <xc.h>
#include "global_defines.h"
#include "lock.h"
#include "LCD.h"
#include <string.h>



unsigned char code[4][5] = {0};
unsigned char query[5] = {0};
// Wipe all lock variables
void initLock(){
    int i;
    int j;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            code[i][j]='f';
        }
        code[i][j]='\0'; // Null terminated for printing ease
        query[i]='f';
    }
    query[i] = '\0'; // Null terminate for printing
}
// Add character to query buffer
int readCode(unsigned char keyScan){
    int i;
    if(keyScan=='f'){// key released
        return NOT_FILLED;
    }
    for(i=0;i<4;i++){// find empty index
        if(query[i]=='f'){
            query[i]=keyScan;
            if(i==3){
                /*for(i=0;i<4;i++){// clear buffer
                    query[i]='f';
                }*/
                 return FILLED;
            }
            break;
        }
    }
    moveCursorLCD(0,1);
    printStringLCD(query);// Print code so far to second line;
   /* if(i==4){
        for(i=0;i<4;i++){// clear buffer
            query[i]='f';
        }
        return FILLED;
    } */   
    if(query[0]=='*'&&query[1]=='*'){
        for(i=0;i<4;i++){// clear buffer
            query[i]='f';
        }
        delay(500);//Trying to make it not redo this so fast
        return SET_MODE;
    }

    
    return NOT_FILLED;
}
// Store New Code if Valid
int setCode(void){
    char tmp[5] = {0};
    int i;
    if(checkCode()==INVALID_CODE){
        return INVALID_CODE;
    }
    // barrel shift code storage before adding
    strcpy(tmp , code[3]);
    strcpy(code[3] , code[2]);
    strcpy(code[2] , code[1]);
    strcpy(code[1] , code[0]);
    strcpy(code[0] , tmp);
    strcpy(code[0],query);// Store new code
    for(i=0;i<4;i++){// clear buffer
            query[i]='f';
    }
    return VALID_CODE;
}
// Check If code is already stored
int compareCode(void){
    int i,j;
    if(checkCode()==INVALID_CODE){
        return INVALID_CODE;
    }
    for(i=0;i<4;i++){
        if(strcmp(query, code[i])==0){ // two strings are equal
            for(j=0;j<4;j++){// clear buffer
                query[j]='f';
            }
            return VALID_CODE;
        }
    }
    for(j=0;j<4;j++){// clear buffer
                query[j]='f';
    }
    return INVALID_CODE;

}

// Check for forbidden characters
int checkCode(){
    int i;
    for(i=0;i<4;i++){
        switch(query[i]){
            case '*':
            case '#':
            case 'f':
                for(i=0;i<4;i++){// clear buffer
                    query[i]='f';
                }
                return INVALID_CODE;
                break;
            default:
                break;
        }
    }
    return VALID_CODE;
}
