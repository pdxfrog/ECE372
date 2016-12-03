
#ifndef _BUTTON_H    /* Guard against multiple inclusion */
#define _BUTTON_H




/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    #define BUTTON1 PORTDbits.RD6
    #define PRESSED 0
    #define RELEASED 1
    void initSW1();
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif 
