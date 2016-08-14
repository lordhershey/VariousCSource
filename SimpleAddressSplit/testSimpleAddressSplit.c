#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EPIC_TS 301
#define LEN_ADDRESS 30

static void parseAddressField(char *token, char *a1, char *a2)
{
  int i;
  int j;
  int k;

  /**/
  memset(a1,' ',LEN_ADDRESS+1);
  a1[LEN_ADDRESS]= '\0';
  memset(a2,' ',LEN_ADDRESS+1);
  a2[LEN_ADDRESS]= '\0';

  for(i = 0,j = 0,k = 0; i < EPIC_TS && token[i];i++)
    {
      if('^' == token[i])
	{
	  if(!k)
	    {
	      k++;
	      j = 0;
	      continue;
	    }

	  /*no K additional overflow into second address*/
	  if(j < LEN_ADDRESS)
	    {
	      a2[j++] = ' ';
	    }
	  continue;
	}

      /*Buffer cannot grow over LEN_ADDRESS*/
      if(j >= LEN_ADDRESS)
	{
	  continue;
	}

      switch(k)
	{
	case 0:
	  a1[j++] = token[i];
	  break;
	default:
	  a2[j++] = token[i];
	  break;
	}

    }

  return;
}

int main(int argc, char * argv[])
{
  char a1[LEN_ADDRESS + 1];
  char a2[LEN_ADDRESS + 1];

  char token[EPIC_TS];

  memset(token,'\0',EPIC_TS);

  snprintf(token,EPIC_TS,"1234 First Avenue^Building 2^Suite C");

  parseAddressField(token,a1,a2);

  printf("%s\n%s\n%s\n",token,a1,a2);

  return (0);
}
