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
