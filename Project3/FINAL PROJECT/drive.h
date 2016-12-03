
#ifndef _DRIVE_H    /* Guard against multiple inclusion */
#define _DRIVE_H

#define DIRECTION_LEFT LATAbits.LATA5
#define DIRECTION_RIGHT LATAbits.LATA7

#define L_SPEED OC1RS
#define R_SPEED OC2RS

#define L_ENABLE LATAbits.LATA4
#define R_ENABLE LATAbits.LATA6

#define FORWARD 0
#define BACKWARD 1


// MOTOR Direction Tristate
#define LD_PINMODE TRISAbits.TRISA5
#define RD_PINMODE TRISAbits.TRISA7    


// MOTOR Drain Control
#define LD_ODCMODE ODCAbits.ODCA5
#define RD_ODCMODE ODCAbits.ODCA7

    
// MOTOR Drain Valve
#define LD_ODCSETZ LATAbits.LATA5
#define RD_ODCSETZ LATAbits.LATA7


extern unsigned int DEFAULT_SPEED;
extern unsigned int TURN_RADIUS;

void initDrive();


void calcSpeedLeftRight(unsigned int turnRatio, unsigned int maxSpeed, unsigned int* speedLeft, unsigned int* speedRight);


void drive(unsigned int speedLeft, unsigned int speedRight, int direction);

void turnLeft();
void turnRight();
void turnAround();
void forward();
void backward();

void pivotRight();
void pivotLeft();

void stop();





#endif /* _DRIVE_H */

/* *****************************************************************************
 End of File
 */
