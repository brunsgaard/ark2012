#include <stdio.h>
#include "mips_base.h"

int main(int args, cont char *argv[])
{
    if (argc != 2)
    {
        printf("You must add a filename as argument");
        return -1
    }

    run_file(argv[1])
    return 0;
}
