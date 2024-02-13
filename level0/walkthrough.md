# Level 0

We can find a "./level0" executable at the root of the user root owned by level1. He's statically linked.

```sh
$ ls -l
total 732
-rwsr-x---+ 1 level1 users 747441 Mar  6  2016 level0

$ ldd ./level0 
	not a dynamic executable
```

We can decompile it with Ghidra.
```c
TODO: Ghidra
```

We can see that ./level0 give access to a shell as level1 if the first argument is equal to 423.

```sh
$ whoami 
level0

$ ./level0 423

$ whoami
level1

$ cd ../level1	

$ cat .pass
```