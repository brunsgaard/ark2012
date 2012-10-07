#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "mips_parser.h"
#include "mips_instr.h"

// code mem is just a dummy variable that hold all the code in memory
char* code_mem[CODE_SIZE];
int code_mem_index;
Label labels[LABEL_SIZE];
int data_index;
int labels_added_index;

void run_file (const char *filename)
{
    // Initialize machine
    pc = 0;
    memset(mem, 0, MEM_SIZE);
    memset(reg, 0, 32);
    reg[REG_SP] = STACK_START;
    reg[REG_FP] = STACK_START;
    code_mem_index = 0;
    labels_added_index = 0;
    data_index = 0;

    // First pass
    parse_file(filename);

    // Run code
    while (1)
    {
        // Run the current instruction
        parse_instruction(code_mem[pc]);
        pc++;
    }
}

/*****************************
 * FIRST PASS
 *****************************/

void parse_file (const char *filename)
{
    char linebuf[LINE_LENGTH];
    FILE *fp = fopen(filename, "r");

    if (!fp)
    {
        printf("Unable to open the specified file for reading");
        exit(1);
    }

    while (fgets(linebuf, LINE_LENGTH, fp) != NULL)
    {
        parse_line(linebuf);
    }

    fclose(fp);
}

void parse_line (const char *line)
{
    int len = strlen(line);
    char* copy = (char*) malloc(len * sizeof(char) );
    strcpy(copy, line);
    code_mem[code_mem_index] = copy;
    parse_labels(line);
    code_mem_index++;
}

// add all lines to the code_mem, when we encounter things not instructions,
// we simply don't care when executing. When we encounter labels with code
// after, we simply only save the part after the label in the code_mem

void parse_labels (const char *line)
{

    char outLabel[48];
    char colonpresent[2];
    int howfarin = 0;
    char rest[256];

    memset(outLabel, 0, 48);
    memset(colonpresent, 0, 2);
    memset(rest, 0, 256);

    int numArgs = sscanf(line, " %47[a-zA-Z]%1[:] %n%255[^\n]", outLabel, colonpresent, &howfarin, rest);

    if ( numArgs > 1 )
    {
        // we've got a label

        int label_len = strlen(outLabel);
        char* label_copy = (char*) malloc(label_len * sizeof(char) );
        strcpy(label_copy, outLabel);

        Label* newLabel = malloc( sizeof(Label) );
        newLabel->name = label_copy;

        if ( numArgs == 3 && rest[0] == '.')
        {
            // code after the label wich is meta instruction
            newLabel->location = run_meta(rest);
        }
        else
        {
            newLabel->location = code_mem_index-1; //-1 because pc will be incremented by 1 when executing is done
        }

        labels[labels_added_index] = *newLabel;
        labels_added_index++;
    }

    if ( numArgs == 3 && rest[0] != '.' )
    {
        // there was code after the label
        int len = strlen(line);
        char* copy = (char*) malloc(len * sizeof(char) );
        strcpy(copy, line);

        code_mem_index++;
        code_mem[code_mem_index] = (copy + howfarin);
    }
}

int run_meta (const char* line)
{
    char cmd[20];
    char arg1[64];

    memset(cmd, 0, 20);
    memset(arg1, 0, 20);

    sscanf(line, " %19[.a-zA-Z] %63s", cmd, arg1 );

    int old_data_index = data_index;
    if (strcmp(cmd, ".space") == 0)
    {
        int space = atoi(arg1);
        data_index += space;
        return old_data_index;
    }
    else if (strcmp(cmd, ".asciiz") == 0)
    {
        char string[256];
        int read = sscanf(line, "%*s \"%[^\"]", string);

        if (read == 1)
        {
            strncpy((char *) &mem[data_index], string, strlen(string));
            data_index += strlen(string);

            return old_data_index;
        }
    }

    printf("Error reading meta instruction: %s\n", cmd);
    exit(1);
}

/*****************************
 * SECOND PASS
 *****************************/

void parse_instruction(char* line)
{
    char cmd[20];
    char arg1[10];
    char arg2[10];
    char arg3[10];

    memset(cmd, 0, 20);
    memset(arg1, 0, 10);
    memset(arg2, 0, 10);
    memset(arg3, 0, 10);

    sscanf(line, " %19[.a-zA-Z] %9s %9s %9s", cmd, arg1, arg2, arg3 );

    if ( strcmp(cmd, "add") == 0 )
    {
        add_instr( toReg(arg1), regValFrmExp(arg2), regValFrmExp(arg3) );
    }
    else if ( strcmp(cmd, "move") == 0 )
    {
        add_instr( toReg(arg1), 0, regValFrmExp(arg2) );
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
    else if ( strcmp(cmd, "la") == 0)
    {
        la_instr( toReg(arg1), label_address(arg2) );
    }
    else if ( strcmp(cmd, "sw") == 0)
    {
        sw_instr( regValFrmExp(arg1), swlwAddr(arg2) );
    }
    else if ( strcmp(cmd, "beq") == 0)
    {
        beq_instr( regValFrmExp(arg1), regValFrmExp(arg2), label_address(arg3) );
    }
    else if ( strcmp(cmd, "jal") == 0)
    {
        jal_instr( label_address(arg1) );
    }
    else if ( strcmp(cmd, "jr") == 0 )
    {
        jr_instr ( regValFrmExp(arg1) );
    }
    else if ( strcmp(cmd, "j") == 0)
    {
        j_instr( label_address(arg1) );
    }
    else if ( strcmp(cmd, "syscall") == 0)
    {
        syscall_instr();
    }
}

int label_address (const char *name)
{
    int i;
    for (i = 0; i < labels_added_index; i++)
    {
        if (strcmp(name, labels[i].name) == 0)
        {
            return labels[i].location;
        }
    }

    printf("Error: Didn't find any matching labels for: %s\n", name);
    exit(1);
}
