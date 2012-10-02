#ifndef MIPS_BASE_H
#define MIPS_BASE_H

extern int ip;
extern int fp;
extern int sp;
extern char* nextInstr;
extern int mem[2048];

typedef struct {
    char *name;
    char *location;
} Label;

int readReg(int regNum);
void writeReg(int regNum, int data);

#else
#endif
