cnprint - washes some chars out of a string - I do not know why this exists.

crunchDate - Doesn't have anything to do with dates, looks like it pulls integers out of a string like so:

$ ./crunchDate this45ismy67andthinggs792_r
a = 45
a = 67
a = 792

sampleLayout shows you the address of locally defined variables in a block, I
guess I was using this in gdb looking for byte boundaries and the like.

$ ./sampleLayout
0x5faa9c
0x5faa98
0x5faa40
0x5fa9f0
0x5fa9a0
0x5fa950
0x5fa94c
0x5fa948
0x5fa944
0x5fa940
0x5fa93c
0x5fa938
0x5fa890
0x5fa7f0
0x5fa7e8
0x5fa7e0

seems to hit the 4's boundary.

testRand - makes weighted random numbers in a range.

$ ./testRand
Enter Low Number 1
Enter High Number 5
Enter Weight 0.0 to 1.0 0.7
5.00000
5.00000
5.00000
5.00000
5.00000
4.43643
3.76510
5.00000
5.00000
5.00000
1.91704
5.00000
5.00000
5.00000
5.00000
2.13340
5.00000
2.36679
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
1.42658
5.00000
2.31979
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
1.88631
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
3.47635
2.15020
5.00000
4.11771
5.00000
1.09893
5.00000
5.00000
5.00000
3.80161
5.00000
4.48337
5.00000
5.00000
5.00000
4.81300
5.00000
5.00000
5.00000
5.00000
5.00000
1.74527
5.00000
5.00000
2.36109
4.99405
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
5.00000
2.81562
5.00000
4.66096
3.49080
5.00000
5.00000
5.00000
5.00000
1.81731
5.00000
5.00000

readCodedArray.c was a thing I found attached to one of those spam
email messages, it was written in JavaScriptr, I just wanted to see
where they thing was trying to take me.

$ ./readCodedArray.exe 3 69,70,71
BCD

3 values 3 numbers (could pass on first parameter and just count commas in
list) it was trying to set the window location to the URL that was represented
by a number array.


