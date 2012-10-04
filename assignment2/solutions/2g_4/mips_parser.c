#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "mips_parser.h"
#include "mips_instr.h"

// code mem is just a dummy variable that hold all the code in memory
char* code_mem[CODE_SIZE];
Label* labels;

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
        parse_instruction(code_mem[pc]);
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

// add all lines to the code_mem, when we encounter things not instructions,
// we simply don't care when executing. When we encounter labels with code
// after, we simply only save the part after the label in the code_mem

void parse_line (const char *line)
{
    /*
    code_mem[0] = line;
    parse_labels(line);
    code_mem ++;
    */
    // Add labels to label list
    // Add code to code list
    // Run meta-instructions
}

void run_meta (const char *instr)
{
    // .space
    if (strcmp(instr, ".space") == 0)
    {

    }

    // .asciiz
    if (strcmp(instr, ".asciiz") == 0)
    {

    }
}

void parse_labels (const char *line)
{
    /*
    char outLabel[30];
    char colonpresent[2];
    char *rest = (char *) malloc(30 * sizeof(char));

    outLabel[0] = '\0';
    colonpresent[0] = '\0';
    rest[0] = '\0';

    int numArgs = sscanf(line, " %[a-zA-Z]%[:]%[^\n]", outLabel, colonpresent, rest);

    //printf("Label=%s Rest=%s #argsFound=%d #colons=%s\n", outLabel, rest, numArgs, colonpresent);
    if ( numArgs > 1 )
    {
        // we've got a label

        Label newLabel = {outLabel, code_mem};
        //TODO: Add label to array
    }

    if ( numArgs == 3 )
    {
        // there was code after the label
        code_mem[0] = rest;
        //TODO: remember to free after using
    }
    else
    {
        free(rest);
    }
    */
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

    if ( strcmp(cmd, "add") == 0 )
    {
        add_instr( toReg(arg1), regValFrmExp(arg2), regValFrmExp(arg3) );
    }
    else if ( strcmp(cmd, "sub") == 0)
    {
        sub_instr( toReg(arg1), regValFrmExp(arg2), regValFrmExp(arg3) );
    }
    else if ( strcmp(cmd, "or") == 0)
    {
        or_instr( toReg(arg1), regValFrmExp(arg2), regValFrmExp(arg3) );
    }
    else if ( strcmp(cmd, "and") == 0)
    {
        and_instr( toReg(arg1), regValFrmExp(arg2), regValFrmExp(arg3) );
    }
    else if ( strcmp(cmd, "slt") == 0)
    {
        slt_instr( toReg(arg1), regValFrmExp(arg2), regValFrmExp(arg3) );
    }
    else if ( strcmp(cmd, "lw") == 0)
    {
        lw_instr( toReg(arg1), swlwAddr(arg2) );
    }
    else if ( strcmp(cmd, "sw") == 0)
    {
        sw_instr( toReg(arg1), swlwAddr(arg2) );
    }
    else if ( strcmp(cmd, "beq") == 0)
    {
        //TODO: fetch the matcing label
        Label label;
        beq_instr( regValFrmExp(arg1), regValFrmExp(arg2), label );
    }
    else if ( strcmp(cmd, "j") == 0)
    {
        //TODO: fetch the matcing label
        Label label;
        j_instr( label );
    }
    else if ( strcmp(cmd, "syscall") == 0)
    {
        syscall_instr();
    }

    //TODO: Meta instructions
}
