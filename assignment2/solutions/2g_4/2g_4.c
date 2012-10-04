#include <stdio.h>

#include "config.h"
#include "mips_parser.h"

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <filename>", argv[0]);
        return -1;
    }

    run_file(argv[1]);
    return 0;
}
