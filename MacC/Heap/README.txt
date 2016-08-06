
  This program takes a list and makes a sorted heap from
it and another list to check to see if the key exists in
the sorted. the first 10 characters on a line are treated 
as the key so a run like this would be:

$ ./fileheap.exe keys keys2
[eat fruit ] - Yes
[video is g] - No
[pizza is n] - No
[I like che] - Yes
[rachel not] - No
[auggly mc ] - No
[I want to ] - No
[life is sq] - No
[woodchuck ] - No
[joe zimmer] - Yes
[I like che] - Yes

$ ./fileheap.exe keys2 keys
[joe zimmer] - Yes
[wanker bob] - No
[zuggly mc ] - No
[eat fruit ] - Yes
[I like che] - Yes
[beef stew ] - No
[eat fruit ] - Yes
[zuggly mc ] - No
[rachel ran] - No
[joe doh   ] - No


