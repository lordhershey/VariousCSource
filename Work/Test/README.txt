
  Not sure if this was an Amazon test or a Google Test. It had worked I am just
trying to remember what the hell it did, something to do with graph cycles, I
had to code it in front of them on my machine. I'll figure it out later.

Here is a sample run:

$ ./test1
2
a | a b c d e f a b c
a
Input size : 2
a | a b c d e f a b c
a
Current Search : a
Current Search : bcdef
All Results: a|bcdef|
b,c,d,e,f

give it at least 2 inputs. This first (n-1) are like a list that says
root_name | destination_1 destination_2 destination_3
search_root_cycle

it will print a path if there is a loop.

all results - a|bcdef|

the first case a is trivial, you are on a, you are already there.

the last line of input is a sinlge char stating were you are search from
and wanting to return to.

$ ./test1
2
b | h g f e d c d a h g f e d c b a
b
Input size : 2
b | h g f e d c d a h g f e d c b a
b
Current Search : b
Current Search : hgfedca
All Results: b|hgfedca|
h,g,f,e,d,c,a

