#include <stdio.h>
#include <stdlib.h>

void mergeSort(int *a, int p, int r)
{

  int mid,p2;
  int *tmp;
  int i,x,y,top;

  if (p >= r)
    {
      /*Node of 1*/
      return;
    }

  mid = p + ((r - p))/2;
  p2 = mid+1;

  mergeSort(a,p,mid);
  
  mergeSort(a,p2,r);

  tmp = (int *)malloc(sizeof(int) * (r-p + 1));
  top = 0;
  
  x = p;
  y = p2;
  
  /*Make tmp odering array*/
  for(i = p; i <= r ;i++)
    {
      
      /*we still have a stack chunk left*/
      if(x <= mid && y <= r)
	{
	  /*we are moving something to a[i]*/
	  if(a[x] > a[y])
	    {
	      printf("%d  %d %d ",p,mid,r);
	      printf("TOP %d\n",a[x]);
	      tmp[top++] = a[x];
	      x++;
	    }
	  else
	    {
	      printf("%d  %d %d ",p,mid,r);
	      printf("TOP %d\n",a[y]);
	      tmp[top++] = a[y];
	      y++;
	    }
	  continue;
	}
      
      if(x <= mid)
	{
	  printf("%d  %d %d ",p,mid,r);
	  printf("TOP %d\n",a[x]);
	  tmp[top++] = a[x];
	  x++;
	  continue;
	}
      printf("%d  %d %d ",p,mid,r);
      printf("TOP %d\n",a[y]);
      tmp[top++] = a[y];
      y++;
    }
  
  for(i = p; i <= r ;i++)
    {
      a[i] = tmp[i-p];
    }
  
  free(tmp);
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

  mergeSort(a,0,9);

  for(i = 0 ; i < 10; i++)
    {
      printf ("%d ",a[i]);
    }

  printf("\n");
}
