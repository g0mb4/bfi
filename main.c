#include <stdio.h>

#include "bfi.h"

const char *hw = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
const char *echo = ",+[-.,+]";
const char *ASCII = ".+[.+]";
const char *back = "+[>,----- -----]<-[+ +++++ +++++.<-]";

int main(int argc, char** argv)
{
    printf("brainfuck interpreter v0.5\n");
    printf("2013, gmb\n\n");

    init_mem();
    run(hw);

    printf("\nProgram exited, press any key to quit...");
    _getch();

    return 0;
}
