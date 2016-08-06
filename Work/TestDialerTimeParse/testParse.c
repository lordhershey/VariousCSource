#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>

int parseStringTime(const char *str, char hms[3])
{
    char *pos = NULL, *badPtr = NULL;
    long hour = 0, min = 0, sec = 0;

    hms[0] = hms[1] = hms[2] = 0;

    pos = strchr(str, ':');

    if (NULL == pos)
        return 0;

    if (pos != str)
        --pos;

    for (; pos != str && isdigit(*pos); --pos)
    {
    }

    if (!isdigit(*pos))
        return 0;

    hour = strtol(pos, &badPtr, 10);
    if (hour < 0 || 23 < hour)
        return 0;

    if (':' != *badPtr)
        return 0;

    ++badPtr;
    if (!isdigit(*badPtr))
        return 0;

    min = strtol(badPtr, &badPtr, 10);

    if (min < 0 || 59 < min)
        return 0;

    if (':' == *badPtr)
    {
        sec = strtol(badPtr + 1, &badPtr, 10);

        if (sec < 0 || 59 < sec)
            return 0;
    }

    hms[0] = hour;
    hms[1] = min;
    hms[2] = sec;

    return 1;
}


int main(int argc, char *argv[])
{
char hms[3];
char buffer[10];
int ret = 0;

while(NULL != fgets(buffer,sizeof(buffer),stdin))
  {
 if(strlen(buffer) < 2)
   {
break;
}
   
   ret = parseStringTime(buffer,hms);
printf(" ret: %d, hms:  %d %d %d\n",ret,hms[0],hms[1],hms[2]);
}

}
