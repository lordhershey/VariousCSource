testconst.c - declare an array, set array element to value, use mprotect on
array to disallow writing, write to array element - core dump.

$ ./testconst
      2 [main] testconst 10700 _cygtls::handle_exceptions: Exception: STATUS_ACCESS_VIOLATION
   7372 [main] testconst 10700 open_stackdumpfile: Dumping stack trace to testconst.exe.stackdump

test1.c - Pointer Fun! try to figure out what it will print. :D

simplListTotal.c take a list of names and values (like a struct) and will
list the elements, size and starting postions.

$ ./simpleListTotal  CHUNK
A                       10      0
B                       20      10
C                       30      30

the first 2 columns are in CHUNK the third is generated.

endlessloop.c is an eample of the use of goto - go ahead goto is not evil. :D

mathquestion.c is a simple example to look at the order of precidence of math
operators.

printme.c a simple test of printf format.

testVariableTimecard.c

tries to expand a file called testcard.txt it was atest to see how easy it 
would be to do some sort of expansion in place.

$ ./testVariableTimecard.exe
Location : 35, Max Size : 25, Last Record Size : 12, Records in File : 3
Read in 12 Bytes..
Record (Del Char not seen) [12345678901]

testloop.c has 2 variable in its increment step.

$ ./testloop.exe
0 0
1 1
2 2
3 3
4 4
5 5
6 6
7 7
8 8
9 9
10 10

one is used as a total and the other is the local loop variable.

