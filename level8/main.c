#include <stdio.h>

char *auth;
int service;

int main(int argc, const char **argv, const char **envp)
{
    char s[5];
    char v5[2];
    char v6[129];

    while (1)
    {
        printf("%p, %p \n", auth, (const void *)service);

        if (!fgets(s, 128, stdin))
            break;

        if (!memcmp(s, "auth ", 5))
        {
            auth = (char *)malloc(4);
            auth[0] = 0;
            if (strlen(v5) <= 30)
                strcpy(auth, v5);
        }

        if (!memcmp(s, "reset", 5))
            free(auth);

        if (!memcmp(s, "service", 6))
            service = (int)strdup(v6);

        if (!memcmp(s, "login", 5u))
        {
            if (*&auth[8]) //??????
                system("/bin/sh");
            else
                fwrite("Password:\n", 1u, 0xAu, stdout);
        }
    }
    return 0;
}