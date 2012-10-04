#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "mips_parser.h"
#include "mips_instr.h"

void run_file (const char *filename)
{
    // First pass
    parse_file(filename);

    // Initialize machine
    memset(mem, 0, MEM_SIZE);
    memset(reg, 0, 32);
    reg[REG_SP] = STACK_START;
    reg[REG_FP] = STACK_START;

    // Run code
    while (1)
    {
        // Run the current instruction

        pc++;
    }
}

void parse_file (const char *filename)
{
    char linebuf[LINE_LENGTH];
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

char *parse_labels (char *line)
{
    char outLabel[30];
    char colonpresent[2];
    char *rest = (char *) malloc(30 * sizeof(char));

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

        //TODO: Add label to array;
    }
    else if ( numArgs == 3 )
    {
        // a label with code after

        //TODO: remember to free after using

        return rest;
    }

    free(rest);
    return NULL;
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

    if ( strncmp(cmd, "add", 3) == 0 )
    {
        add_instr( toReg(arg1), regValFrmExp(arg2), regValFrmExp(arg3) );
    }
    else if ( strncmp(cmd, "sub", 3) == 0)
    {
        sub_instr( toReg(arg1), regValFrmExp(arg2), regValFrmExp(arg3) );
    }
    else if ( strncmp(cmd, "or", 2) == 0)
    {
        or_instr( toReg(arg1), regValFrmExp(arg2), regValFrmExp(arg3) );
    }
    else if ( strncmp(cmd, "and", 3) == 0)
    {
        and_instr( toReg(arg1), regValFrmExp(arg2), regValFrmExp(arg3) );
    }
    else if ( strncmp(cmd, "slt", 3) == 0)
    {
        slt_instr( toReg(arg1), regValFrmExp(arg2), regValFrmExp(arg3) );
    }
    else if ( strncmp(cmd, "lw", 2) == 0)
    {
        lw_instr( toReg(arg1), swlwAddr(arg2) );
    }
    else if ( strncmp(cmd, "sw", 2) == 0)
    {
        sw_instr( toReg(arg1), swlwAddr(arg2) );
    }
    else if ( strncmp(cmd, "beq", 3) == 0)
    {
        //TODO: fetch the matcing label
        Label label;
        beq_instr( regValFrmExp(arg1), regValFrmExp(arg2), label );
    }
    else if ( strncmp(cmd, "j", 1) == 0)
    {
        //TODO: fetch the matcing label
        Label label;
        j_instr( label );
    }
    else if ( strncmp(cmd, "syscall", 7) == 0)
    {
        syscall_instr();
    }

    //TODO: Meta instructions
}
