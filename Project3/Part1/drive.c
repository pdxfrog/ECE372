

#include <xc.h>
#include "global_defines.h"
#include "drive.h"


#define MAX_TURN_RATIO 1023
#define MAX_SPEED 1023
#define FULL_LEFT maxSpeed
#define FULL_RIGHT maxSpeed
#define ZERO_LEFT 0
#define ZERO_RIGHT 0

void calcSpeedLeftRight(unsigned int turnRatio, unsigned int maxSpeed, unsigned int* speedLeft, unsigned int* speedRight){
    
    unsigned int left, right;
     
    
    // Gracefully handle out-of-range values
    if (turnRatio >= MAX_TURN_RATIO){
        left    =   FULL_LEFT;
        right   =   ZERO_RIGHT;
    } 
    else if(turnRatio <= 0){    // Unsigned, the less-than is for future-proofing / portability
        left    =   ZERO_LEFT;
        left    =   FULL_RIGHT;
    }   
    else{
        left    =   turnRatio;
        right   =   (MAX_TURN_RATIO - turnRatio);
    }
    // Scale to max
    if(left >= right){
        left    =   maxSpeed   *   left  / left;
        right   =   maxSpeed   *   right / left;
    }
    else if(right > left){
        left    =   maxSpeed   *   left  / right;
        right   =   maxSpeed   *   right / right;
    }    
}
