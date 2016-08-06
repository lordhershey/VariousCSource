fp.c - function pointer - examine the memory from a function pointer.

$ ./fp
10
55 89 e5 8b 45 08 83 c0 05 5d c3 55 89 e5 8b 45 08 83 c0 02 5d c3 55 89 e5
7
55 89 e5 8b 45 08 83 c0 02 5d c3 55 89 e5 8b 45 08 83 c0 05 5d c3 55 89 e5


I tried to change one of these values in the program, but it will segfault,
if you want to mess with data in the non data section you will have to
screw around with mprotect.

fp2.c pass function pointers to a function (say if you want to make a custom
compare to one of my sort functions or the like)

$ ./fp2
Function foo1 NULL
Function foo2 NULL
Function foo1 NULL
Function foo2(5) = 7
Function foo1(5) = 10
Function foo2 NULL
Function foo1(5) = 10
Function foo2(5) = 7
Function foo1(5) = 7
Function foo2(5) = 10

