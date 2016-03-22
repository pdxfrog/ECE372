
#ifndef _LOCK_H    /* Guard against multiple inclusion */
#define _LOCK_H

#define SET_MODE 2
#define FILLED 1
#define NOT_FILLED 0

#define VALID_CODE 1
#define INVALID_CODE 0


#define READ_MODE 3

extern char codes[5][4];

unsigned char isValid(char* code);

void initLock();

int compareCode(void);
int setCode(void);
int readCode(unsigned char keyScan);


#endif /* _LOCK_H */


