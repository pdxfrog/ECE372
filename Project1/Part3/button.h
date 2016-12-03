
#ifndef _BUTTON_H    /* Guard against multiple inclusion */
#define _BUTTON_H




/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    #define R_SWITCH PORTDbits.RD6
    #define S_SWITCH PORTAbits.RA7
    #define PRESSED 0
    #define RELEASED 1

    void initSwitch();
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif 
