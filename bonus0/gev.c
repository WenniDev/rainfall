#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *ptr;

    if (argc < 2)
    {
        printf("Usage: %s <environment variable> \n", argv[0]);
        exit(0);
    }

    ptr = getenv(argv[1]);
    printf("%s will be near %p\n", argv[1], ptr);
}