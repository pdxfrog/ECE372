
#ifndef _KEYPAD_H    /* Guard against multiple inclusion */
#define _KEYPAD_H




/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
  


void initKeypad();
unsigned char keyScan();
    
// Row Tristate    
#define R1_PINMODE TRISDbits.TRISD9
#define R2_PINMODE TRISDbits.TRISD3
#define R3_PINMODE TRISDbits.TRISD6
#define R4_PINMODE TRISDbits.TRISD12

// Row PullUP
#define R1_USECNPU CNPUDbits.CNPUD9
#define R2_USECNPU CNPUDbits.CNPUD3
#define R3_USECNPU CNPUDbits.CNPUD6
#define R4_USECNPU CNPUDbits.CNPUD12
    
#define R1ISANALOG ANSELDbits.ANSD1
#define R2ISANALOG ANSELDbits.ANSD3

// Row Port Register
#define RA_PINREAD PORTD  // Read All Pins
#define R1_PINREAD PORTDbits.RD9
#define R2_PINREAD PORTDbits.RD3
#define R3_PINREAD PORTDbits.RD6
#define R4_PINREAD PORTDbits.RD12   

#define R1_CNIEBIT CNENDbits.CNIED9
#define R2_CNIEBIT CNENDbits.CNIED3
#define R3_CNIEBIT CNENDbits.CNIED6
#define R4_CNIEBIT CNENDbits.CNIED12
    
    
// Column Tristate
#define G1_PINMODE TRISGbits.TRISG12
#define G2_PINMODE TRISGbits.TRISG13    
#define G3_PINMODE TRISGbits.TRISG14

// Column Drain Control
#define G1_ODCMODE ODCGbits.ODCG12
#define G2_ODCMODE ODCGbits.ODCG13
#define G3_ODCMODE ODCGbits.ODCG14
    
// Column Drain Valve
#define GA_ODCSETZ LATG
#define G1_ODCSETZ LATGbits.LATG12
#define G2_ODCSETZ LATGbits.LATG13
#define G3_ODCSETZ LATGbits.LATG14

#define SETALLHIGH 0x7000
#define SETALLLOWZ 0x8FFF
 
    
    
    

    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif 
