
// This code should be readable without need for (very many) additional comments
#include <xc.h>
#include "global_defines.h"
#include "drive.h"
#include "pwm.h"


#define MAX_TURN_RATIO 1023
#define MAX_SPEED 1023
unsigned int DEFAULT_SPEED = 700;
unsigned int TURN_RADIUS = 7;
#define FULL_LEFT maxSpeed
#define FULL_RIGHT maxSpeed

#define ZERO_LEFT 0
#define ZERO_RIGHT 0

void calcSpeedLeftRight(unsigned int turnRatio, unsigned int maxSpeed,unsigned int* speedLeft, unsigned int* speedRight){
    
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
    

        *speedLeft = left;
        *speedRight = right;
 

}


void drive(unsigned int speedLeft, unsigned int speedRight, int direction){
     // Control Direction
    if(direction>0){
        L_SPEED = speedLeft;
        R_SPEED = speedRight;
        
        DIRECTION_LEFT = FORWARD;
        DIRECTION_RIGHT = FORWARD;
        
        L_ENABLE = YES;
        R_ENABLE = YES;
    }
    else if(direction<0){
        L_SPEED = MAX_SPEED - speedLeft;
        R_SPEED = MAX_SPEED - speedRight;

        DIRECTION_LEFT = BACKWARD;
        DIRECTION_RIGHT = BACKWARD;
        
        L_ENABLE = YES;
        R_ENABLE = YES;
    }
    else{
        L_SPEED = 0;
        R_SPEED = 0;
        
        DIRECTION_LEFT = FORWARD;
        DIRECTION_RIGHT = FORWARD;
        
        L_ENABLE = NO;
        R_ENABLE = NO;
    }
}


void initDrive(){
    // MOTOR Direction Tristate
LD_PINMODE = OUTPUT;
RD_PINMODE = OUTPUT;


// MOTOR Drain Control
LD_ODCMODE = ENABLE;
RD_ODCMODE = ENABLE;

    
// MOTOR Drain Valve
LD_ODCSETZ = LOW_Z;
RD_ODCSETZ = LOW_Z;

L_SPEED = 0;
R_SPEED = 0;

TRISAbits.TRISA4 = OUTPUT;
TRISAbits.TRISA6 = OUTPUT;

L_ENABLE = NO;
R_ENABLE = NO;
    
    
}

void turnLeft(){
        L_SPEED = DEFAULT_SPEED/TURN_RADIUS;
        R_SPEED = DEFAULT_SPEED;
        
        DIRECTION_LEFT = FORWARD;
        DIRECTION_RIGHT = FORWARD;
        
        L_ENABLE = YES;
        R_ENABLE = YES;
}
void turnRight(){
        L_SPEED = DEFAULT_SPEED;
        R_SPEED = DEFAULT_SPEED/TURN_RADIUS;
        
        DIRECTION_LEFT = FORWARD;
        DIRECTION_RIGHT = FORWARD;
        
        L_ENABLE = YES;
        R_ENABLE = YES;
}
void turnAround(){
        L_SPEED = DEFAULT_SPEED;
        R_SPEED = MAX_SPEED - DEFAULT_SPEED;
        
        DIRECTION_LEFT = FORWARD;
        DIRECTION_RIGHT = BACKWARD;
        
        L_ENABLE = YES;
        R_ENABLE = YES;
}
void forward(){
        L_SPEED = DEFAULT_SPEED;
        R_SPEED = DEFAULT_SPEED;
        
        DIRECTION_LEFT = FORWARD;
        DIRECTION_RIGHT = FORWARD;
        
        L_ENABLE = YES;
        R_ENABLE = YES;
}

void backward(){
        L_SPEED = MAX_SPEED - DEFAULT_SPEED;
        R_SPEED = MAX_SPEED - DEFAULT_SPEED;
        
        DIRECTION_LEFT = BACKWARD;
        DIRECTION_RIGHT = BACKWARD;
        
        L_ENABLE = YES;
        R_ENABLE = YES;
}


void pivotRight(){
        L_SPEED = DEFAULT_SPEED;
        R_SPEED = DEFAULT_SPEED;
        
        DIRECTION_LEFT = FORWARD;
        DIRECTION_RIGHT = BACKWARD;
        
        L_ENABLE = YES;
        R_ENABLE = YES;
}
void pivotLeft(){
        L_SPEED = DEFAULT_SPEED;
        R_SPEED = DEFAULT_SPEED;
        
        DIRECTION_LEFT = BACKWARD;
        DIRECTION_RIGHT = FORWARD;
        
        L_ENABLE = YES;
        R_ENABLE = YES;
}

void stop(){
        L_ENABLE = NO;
        R_ENABLE = NO;  
}