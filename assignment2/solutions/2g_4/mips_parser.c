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
