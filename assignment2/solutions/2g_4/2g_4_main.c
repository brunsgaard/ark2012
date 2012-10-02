#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mips_base.h"


// CODE

int main()
{
	writeReg(toReg("$t0"), 16); // $t0 = 16
    printf("read $8: %d\n", regValFrmExp("$8") ); // $8 is 16, as $t0 == $8
    printf("read 1337 %d\n", regValFrmExp("1337") );

    printf("%d\n", swlwAddr("0($8)") );
    printf("%d\n", swlwAddr("4($8)"));
	
	char* hej = "hej";
	char* martin = "martin";
	Label test = {hej, martin};

	Label* test2 = &test;

	printf("%s\n", test2->location);

    return 0;
}