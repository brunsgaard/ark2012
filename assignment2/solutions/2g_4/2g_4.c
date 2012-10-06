#include <stdio.h>
#include <string.h>

#include "config.h"
#include "mips_parser.h"

//just for my testing function
#include "mips_base.h"

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
    Label test = {hej, 123};
    printf("%s\n", test.name);

    Label* test2 = &test;
    printf("%d\n", test2->location);
    //*/

    /*
    writeReg(toReg("$t0"), 16); // $t0 = 16
    parse_instruction("     add $1, $t0, 4");
    printf("%d\n", regValFrmExp("$1"));
    //*/

    /*
    char* hejmartin = "hej";
    char* martinhej ="martin";
    char* lala ="lala";

    printf("%s\n", hejmartin);

    char* testarr[2048];

    printf("%s\n", "pis");

    testarr[0] = hejmartin;
    testarr[1] = martinhej;
    testarr[3] = lala;
    printf("%s\n", "nå");
    printf("%s\n", (char*) testarr[1] );
    //*/

    /*
    printf("%s\n", "HVAD?");
    Label testLabel = {"end", 123};
    labels[0] = testLabel;

    printf("%s\n", labels[0].name);

    printf("%d\n", label_address("end") );
    //*/

    ///*
    int intarr[100];

    strcpy( (char*) &intarr[7], "string");

    char* hej = (char*) &intarr[7];
    printf("%s\n", hej );

    char* hej2 = (char*) &intarr[8];
    printf("%s\n", hej2 );
    //*/

    // TODO: test meta instructions

    if (argc != 2)
    {
        printf("Usage: %s <filename>", argv[0]);
        return -1;
    }

    run_file(argv[1]);
    return 0;
}
