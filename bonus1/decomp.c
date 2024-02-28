#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int arg = atoi(argv[1]);
    int test;
    printf("The first argument is %d\n", arg);
    if (arg > 9) {
        test = 1;
    } else {
        char buf[40];
        printf("arg in uint: %i\n", arg);
        printf("arg * 4: %i\n", arg * 4);
        memcpy(&buf, argv[2], arg * 4);
        if (arg == 0x574f4c46) {
            // execl("/bin/sh", "sh");
            printf("You have modified the 'modified' variable\n");
        }
        test = 0;
    }
    return test;
}