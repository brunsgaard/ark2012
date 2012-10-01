#include <stdlib.h>
#include <stdio.h>

void parse_line(char *line);

enum INSTRUCTION {
    ADD,
    SUB,
    AND,
    OR,
    SLT,
    LW,
    SW,
    BEQ,
    J
};

int registers[32];

int ip;

int fp;
int sp;

/********************************
 * CODE METADATA
 ********************************/

typedef struct {
    char *name;
    char *location;
} Label;

Label *labels;

/********************************
 * FIRST PASS
 ********************************/

char **code;

void first_pass (const char* filename)
{
    char linebuf[256];
    FILE *fp = fopen(filename, "r");

    if (!fp)
    {
        printf("Unable to open the specified file for reading");
        exit(-1);
    }

    while (fgets(linebuf, 256, fp) != NULL)
    {
        parse_line(linebuf);
    }

    fclose(fp);
}

void parse_line (char *line)
{
    // Determine line type
    // If label
    //      Add new label to list with pointer to next place in code
    // If instruction
    //      Add to list of code

    // Parse R type instruction
    char *operation;
    char *rd;
    char *rs;
    char *rt;
    int immediate;

    sscanf(line, " %s $%s , $%s, $%s", operation, rd, rs, rt);

    // Parse I type instruction
    sscanf(line, " %s $%s, $%s, %i", operation, rt, rs, &immediate);
}

void parse_rtype (char *line)
{

}

/********************************
 * MAIN
 ********************************/

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <filename>", argv[0]);
        return -1;
    }

    first_pass(argv[1]);

    return 0;
}
