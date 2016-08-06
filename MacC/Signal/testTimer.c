#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <setjmp.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <time.h>
#include <dirent.h>
#include <ctype.h>

#include <netdb.h>
#include <sys/time.h> 
#include <errno.h>


struct itimerval nval,oval;

void testSignal()
{
  printf("Chicken!\n");
}

int main()
{
  int ret = 0;

  ret = getitimer(ITIMER_REAL,&oval);

  if(ret != 0)
    {
      printf("Arrrgh! I cannot get the old Interval");
      return (-1);
    }

  nval.it_interval.tv_sec = 0;
  nval.it_interval.tv_usec = 50000;

  nval.it_value.tv_sec = 0;
  nval.it_value.tv_usec = 50000;

  ret = setitimer(ITIMER_REAL,&nval,&oval);

  if(ret != 0)
    {
      printf("Arrrgh! Cannot set Timer\n");
      switch (errno)
	{
	case EFAULT:
	  printf("EFAULT\n");
	  break;
	case EINVAL:
	  printf("EINVAL\n");
	  break;
	}
      return (-1);
    }

  signal(SIGALRM, testSignal );

  sleep(10);
  printf("I'm Done\n");
  return (0);
}

