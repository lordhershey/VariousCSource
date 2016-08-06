
handtest.c - takes 6 arguments, the first five represents cards the sixth
checks the card at the position and see's if there is anything valuable.
It guages this on - at least a 3 of a kind, possible straight or flush. This
does not sense a full house (as it was not part of the concept being developed)
there is some java game prototype that came out of this. Maybe I'll put it up.

example usage:
$ ./handtest 1a 2a 3a 4a 5a  0
This hand is a Straight [1 .. 5]
This hand has a flush element

$ ./handtest 1a 1b 1c 4a 5a  0
Have a touple 1 [0 .. 2]

$ ./handtest 2a 4a 1a 3a 5a  3
This hand is a Straight [1 .. 5]
This hand has a flush element


Handtest2 - seems to look for partial straights of 4 cards - I do not think
I finished this one since I decided to scrap partial straights with flush
elements.



