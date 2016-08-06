#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*!
  \brief get the token index from a line like PAYAMNT_1=

  This routine will minus 1 from the index 

  \param[in] token char pointer 
  \retval < 0 no/bad number 
  \retval >= 0 found a number
 */
static int GetIndex(char *token)
{
  char buffer[20];
  int i = 0;
  int j = 0;
  int go = 0;
  int stop = 0;

  memset(buffer,'\0',sizeof(buffer));

  for(i = 0 ; i < strlen(token) ; i++)
    {
      if('_' == token [i])
	{
	  go = 1;
	  continue;
	}

      if('=' == token [i])
	{
	  stop = 1;
	  break;
	}

      if(!go)
	{
	  continue;
	}

      if(j < (sizeof(buffer) - 1))
	{
	  buffer[j] = token[i];
	  j++;
	}
    }

  if(!go || !stop)
    {
      return(-1);
    }

  return(atoi(buffer) - 1);
}

static int GetTokenOffset(char *token)
{

  int i;
  int stop = 0;

  for(i = 0; i < strlen(token); i++)
    {
      if(token[i] == '=')
	{
	  stop = 1;
	  i++;
	  break;
	}
    }

  if(!stop)
    {
      return(-1);
    }

  return (i);
}


int main(int argc, char *argv[])
{

  int a,b;

  if(argc < 2)
    {
      exit(-1);
    }

  a = GetIndex(argv[1]);
  b = GetTokenOffset(argv[1]);

  printf("Index : %d, Offset : %d\n",a,b);
  if(b > -1)
    {
      printf("Token Value = %s\n",argv[1] + b);
    }
}
