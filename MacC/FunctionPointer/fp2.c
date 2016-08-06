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

int boo(int (*foo1)(int) , int (*foo2)(int))
{

  int a = 0;

  if(NULL != foo1)
    {
      printf("Function foo1(5) = %d\n",foo1(5));
      a++;
    }
  else
    {
      printf("Function foo1 NULL\n");
    }

  if(NULL != foo2)
    {
      printf("Function foo2(5) = %d\n",foo2(5));
      a++;
    }
  else
    {
      printf("Function foo2 NULL\n");
    }

  return (a);
}

int main (int argc,char *argv[])
{
  int (*foo)(int);
  unsigned char *v;
  int i;

  boo(NULL,NULL);
  boo(NULL,addPlus2);
  boo(addPlus5,NULL);
  boo(addPlus5,addPlus2);
  boo(addPlus2,addPlus5);

  return (0);
}
