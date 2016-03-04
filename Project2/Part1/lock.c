


#include <xc.h>
#include "global_defines.h"
#include "lock.h"




unsigned char code[4][5] = {0};
unsigned char query[5] = {0};

void initLock(){
    int i;
    int j;
    for(i=0;i<4;i++){
        for(j=0;j<5;++){
            code[i][j]='f';
        }
    }
}

int readCode(unsigned char keyScan){
    if(keyScan=='f'){
        return NOT_FILLED;
    }
    
    
    return 0;
}

int setCode(unsigned char keyScan){
    
    return 0;
}

int compareCode(void){
    
    
    return 0;
}

