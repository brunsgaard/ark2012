#ifndef MIPS_BASE_H
#define MIPS_BASE_H

extern int reg[];
extern int ip;
extern int fp;
extern int sp;

typedef struct {
    char *name;
    char *location;
} Label;

Label *labels;

#else
#endif
