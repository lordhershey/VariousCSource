
  A simple Read Balck Tree implementation. A Red Black tree is a fairly
balanced tree scheme where (if I remember correctly) one side is either not
double the length of the other.

you call the program with a list of numbers on the command line.

Here is a sample run:

$ ./redblack 2 3 1 6 56 45 2 8 54
Level 0, Key (6), Color Black, Parent Nil
Left:
        Level 1, Key (2), Color Red, Parent Key [6]
        Left:
                Level 2, Key (1), Color Black, Parent Key [2]
                Left:
                        Nil
                Right:
                        Nil
        Right:
                Level 2, Key (3), Color Black, Parent Key [2]
                Left:
                        Level 3, Key (2), Color Red, Parent Key [3]
                        Left:
                                Nil
                        Right:
                                Nil
                Right:
                        Nil
Right:
        Level 1, Key (45), Color Red, Parent Key [6]
        Left:
                Level 2, Key (8), Color Black, Parent Key [45]
                Left:
                        Nil
                Right:
                        Nil
        Right:
                Level 2, Key (56), Color Black, Parent Key [45]
                Left:
                        Level 3, Key (54), Color Red, Parent Key [56]
                        Left:
                                Nil
                        Right:
                                Nil
                Right:
                        Nil


