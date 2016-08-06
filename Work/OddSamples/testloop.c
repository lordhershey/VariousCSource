#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int i,j;
  j = 0;

  for(i = 0 ; i < 10 ; i++,j++)
    {
      printf("%d %d\n",i,j);
    }
  printf("%d %d\n",i,j);
  return(0);
}
