#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
  FILE *f = NULL;
  char buffer[100];
  int total = 0;
  int i;
  int size = 0;

  if(argc < 2)
    {
      exit(-1);
    }


  f = fopen(argv[1],"r");

  while(fgets(buffer,sizeof(buffer),f) != NULL)
    {

      size = 0;

      for(i = 0 ; i < strlen(buffer) ; i++)
	{
	  if(buffer[i] == ' ' || buffer[i] == '\t')
	    {
	      buffer[i] = '\0';
	      size = atoi(buffer + i + 1);
	      break;
	    }
	}

      if(size < 1)
	continue;

      printf("%-20s\t%d\t%d\r\n",buffer,size,total);

      total += size;

    }

  exit(0);
}
