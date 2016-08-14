Base 64 Encode and Decode programs:

compile
gcc -o Base64Encode -g Base64Encode.c

gcc -o Base64Decode -g Base64Decode.c


USAGE Encodeing:
$ ./Base64Encode.exe "This is a Sring to Encode\!"
VGhpcyBpcyBhIFNyaW5nIHRvIEVuY29kZVwh


USAGE Decoding:
$ ./Base64Decode.exe VGhpcyBpcyBhIFNyaW5nIHRvIEVuY29kZVwh
[[[This is a Sring to Encode\!]]]




