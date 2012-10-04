#include <stdio.h>

#include "config.h"
#include "mips_parser.h"

int main(int argc, const char *argv[])
{
    // KEEP MY FREAKING TESTING FUNCTIONS!!!!
    
    /*
    writeReg(toReg("$t0"), 16); // $t0 = 16
    printf("read $8: %d\n", regValFrmExp("$8") ); // $8 is 16, as $t0 == $8
    printf("read 1337 %d\n", regValFrmExp("1337") );

    printf("%d\n", swlwAddr("0($8)") );
    printf("%d\n", swlwAddr("4($8)"));
    
    char* hej = "hej";
    char* martin = "martin";
    Label test = {hej, martin};
    printf("%s\n", test.name);

    Label* test2 = &test;
    printf("%s\n", test2->location);
    //*/

    /*
    writeReg(toReg("$t0"), 16); // $t0 = 16
    parse_instruction("     add $1, $t0, 4");
    printf("%d\n", regValFrmExp("$1"));
    //*/

    if (argc != 2)
    {
        printf("Usage: %s <filename>", argv[0]);
        return -1;
    }

    run_file(argv[1]);
    return 0;
}
