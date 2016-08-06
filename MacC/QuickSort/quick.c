#include <stdio.h>
#include <stdlib.h>


int partition(int *a,int p, int r)
{
  int x = a[p];
  int i = p - 1;
  int j = r + 1;
  int tmp;

  while(1)
    {
      for(; !(a[--j] <= x););
      for(; !(a[++i] >= x););
      if (i < j)
	{
	  tmp = a[i];
	  a[i] = a[j];
	  a[j] = tmp;
	}
      else
	{
	  return (j);
	}
    }
}

void quickSort(int *a,int p, int r)
{
  int q;
  if(p < r)
    {
      q = partition(a,p,r);
      quickSort(a,p,q);
      quickSort(a,(q + 1),r);
    }
}

int main(int argc, char *argv[])
{
  int a[10];
  int i;

  a[0] = 4;
  a[1] = 3;
  a[2] = 8;
  a[3] = 2;
  a[4] = 9;
  a[5] = 1;
  a[6] = 0;
  a[7] = 7;
  a[8] = 5;
  a[9] = 6;

  for(i = 0 ; i < 10; i++)
    {
      printf ("%d ",a[i]);
    }

  printf("\n");

  quickSort(a,0,9);

  for(i = 0 ; i < 10; i++)
    {
      printf ("%d ",a[i]);
    }

  printf("\n");
}
