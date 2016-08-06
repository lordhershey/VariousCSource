#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int addPlus5(int a)
{
  return (a + 5);
}

int addPlus2(int a)
{
  return (a + 2);
}

int addPlus5Prime(int a)
{
  return (a + 5);
}

int main (int argc,char *argv[])
{
  int (*foo)(int);
  unsigned char *v;
  int i;

  foo = addPlus5;

  printf("%d\n",foo(5));

  v = (char *)foo;

  for (i = 0; i < 25 ; i++)
    {
      printf("%02x ",*(v + i));
    }
  printf("\n");

  foo = addPlus2;

  printf("%d\n",foo(5));

  v = (unsigned char *)foo;

  for (i = 0; i < 25 ; i++)
    {
      printf("%02x ",*(v + i));
    }
  printf("\n");

  return (0);
}
