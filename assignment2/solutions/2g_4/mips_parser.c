#include <stdio.h>
#include <stdlib.h>

#include "mips_parser.h"
#include "mips_instr.h"

void parse_file (const char *filename)
{
    char linebuf[1024];
    FILE *fp = fopen(filename, "r");

    if (!fp)
    {
        printf("Unable to open the specified file for reading");
        exit(-1);
    }

    while (fgets(linebuf, 1024, fp) != NULL)
    {
        parse_line(linebuf);
    }

    fclose(fp);
}

void parse_line (const char *line)
{
}

char* parse_labels (char* line)
{
    char outLabel[30];
    char colonpresent[2];
    char rest[30];

    outLabel[0] = '\0';
    colonpresent[0] = '\0';
    rest[0] = '\0';

    int numArgs = sscanf(line, " %[a-zA-Z]%[:]%[^\n]", outLabel, colonpresent, rest);

    //printf("Label=%s Rest=%s #argsFound=%d #colons=%s\n", outLabel, rest, numArgs, colonpresent);
    if ( numArgs < 2 )
    {
        // no label
    }
    else if ( numArgs == 2 )
    {
        // a label with no code after
    }
    else if ( numArgs == 3 )
    {
        // a label with code after
    }
}

void parse_instruction(char* line)
{
    char cmd[20];
    char arg1[10];
    char arg2[10];
    char arg3[10];

    cmd[0] = '\0';
    arg1[0] = '\0';
    arg2[0] = '\0';
    arg3[0] = '\0';

    sscanf(line, " %[a-zA-Z] %s %s %s", cmd, arg1, arg2, arg3 );
    //printf("Command=%s a1=%s a2=%s a3=%s\n", cmd, arg1, arg2, arg3);
}