#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if(argc < 3)
    {
      printf("USAGE:%s num comma_seperated_list_of_numbers\n",argv[0]);
      exit(-1);
    }

  int first = atoi(argv[1]);
  int i;
  int num;
  num = 0;
  unsigned char result;
  char *p = argv[2];
  for(i = 0; i < (strlen(p) + 1) ; i++)
    {
      if(isdigit(p[i]))
	{
	  num = num*10 + (int)( p[i] - '0');
	}
      else
	{
	  result = (unsigned char)(num - first);
	  if (isprint(result) || isspace(result))
	    {
	      printf("%c",result);
	    }
	  else
	    {
	      printf("|_%3d_|",result);
	    }
	num = 0;
	}
    }
  printf("\n");
  exit(0);
}
