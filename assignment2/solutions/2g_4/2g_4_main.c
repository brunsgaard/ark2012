#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mips_base.h"


// CODE

int main()
{
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
	*/

	char* testLabel = "swap:asdf";

	char outLabel[30];
	sscanf(testLabel, "%[a-z,A-Z]:", outLabel);
	printf("Label=%s\n", outLabel);

	char cmd[20];
	char arg1[10];
	char arg2[10];
	char arg3[10];

	char* testCommand = "	add $v0, $zero, 1";
	sscanf(testCommand, "%*[ \t]%s%*[ \t]%[^,],%*[ \t]%[^,],%*[ \t]%s", cmd, arg1, arg2, arg3 );
	printf("Command=%s a1=%s a2=%s a3=%s\n", cmd, arg1, arg2, arg3);

    return 0;
}