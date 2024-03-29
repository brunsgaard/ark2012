#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "config.h"
#include "mips_base.h"
#include "mips_parser.h"

int mem[MEM_SIZE];
int reg[32];
int pc;

int readReg(int regNum)
{
	return reg[regNum];
}

void writeReg(int regNum, int data)
{
	if (regNum == 0) return;

	reg[regNum] = data;
}

int toReg(char *in)
{
	//remove the $ as we don't care about it
	in++;

	// if it's in format $0 or $24
	if ( isdigit(in[0]) )
	{
		return atoi(in);
	}

	// items that can not be uniquely identified by their first letter
	if ( strncmp(in, "at", 2) == 0) { return 1; }
	if ( strncmp(in, "sp", 2) == 0) { return 29; }

	switch( in[0] )
	{
		case 'z': return 0; //zero
		case 'v': return 2 + in[1] - '0';
		case 'a': return 4 + in[1] - '0';
		case 't':{
			int val = in[1] - '0';
				if ( val < 8 ) { return 8 + val; }
				else { return 18 + val; }
			}
		case 's': return 16 + in[1] - '0';
		case 'k': return 26 + in[1] - '0';
		case 'g': return 28; //gp
		case 'f': return 30; //fp
		case 'r': return 31; //ra
		default: return -1;
	}
}

int regValFrmExp(char* in)
{
	if ( in[0] == '$' )
	{
		return readReg( toReg(in) );
	}

	return atoi(in);
}

int swlwAddr(char* in)
{
	int offset;
	char b[10];
	int regVal;

	memset(b, 0, 10);

	int read = sscanf(in,"%d(%9s)", &offset, b);

	if (read == 2)
    {
	    regVal = readReg( toReg(b) );
	    return (regVal + offset)/4;
	}

	read = sscanf(in,"(%9s)", b);
    regVal = readReg( toReg(b) );

	if (read == 1)
    {
	    return (regVal + 0)/4;
    }

    printf("Unable to parse memory reference %s\n", in);
    exit(1);
}
