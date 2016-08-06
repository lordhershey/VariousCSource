#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int globalops = 0;
int globalcomps = 0;

int inplacemerge(int *arr,int x1,int x2, int y2)
{
    int i,j;
    int start,finish;
    int tmp;
    int y1 = x2-1;

    /*TODO - check the x1 and x2 to make sure they are in order*/

    start = x1;
    finish = y2;

    for(i = start; i < finish ; i ++)
      {

	if(x1 > y1)
	  {
	    /*first list empty*/
	    break;
	  }

	if(x2 > y2)
	  {
	    /*second list empty*/
	    break;
	  }

	globalcomps++;

	if(arr[x2] < arr[x1])
	  {
	    /*the top of the second stack is smaller, we must shift the stack
	      on top down*/
	    tmp = arr[x2];
	    x2++;

	    /*move index down*/
	    for(j = y1+1; j >= x1 ;j--)
	      {
		arr[j] = arr[j-1];
	      }

	    arr[x1] = tmp;

	    x1++;
	    y1++;
	    continue;
	  }

	x1++;

      }

    return 0;
}

void mergsortreccurse(int *a,int start, int end,int ListSize)
{

  int elems = 0;
  int i;

  globalops++;

  if(start >= end)
    {
      return;
    }

  elems = (end - start);

  if(0 == start && (end + 1) ==  ListSize)
    {
      for(i = 0; i < ListSize ; i++)
	{
	  printf("%d ",a[i]);
	}
      printf("\n");
    }

  mergsortreccurse(a,start,start+elems/2,ListSize);
  mergsortreccurse(a,start+elems/2+1,end,ListSize);
 
  inplacemerge(a,start,start+elems/2+1,end);

  for(i = 0; i < ListSize ; i++)
  {
    printf("%d ",a[i]);
  }
  printf("\n");

  return;
}

void insertsortreccurse(int *a,int start,int end, int ListSize)
{
  int i;

  globalops++;

  if(start >= end)
    return;

  if(0 == start && (end + 1) ==  ListSize)
    {
      for(i = 0; i < ListSize ; i++)
	{
	  printf("%d ",a[i]);
	}
      printf("\n");
    }

  /*Sort the rest of the list */
  insertsortreccurse(a,start+1,end,ListSize);

  /*then merge with are already sorted list*/
  inplacemerge(a,start,start+1,end);

  for(i = 0; i < ListSize ; i++)
  {
    printf("%d ",a[i]);
  }
  printf("\n");

}

int mergesort(int *a,int ListSize)
{
  int step = 1;
  int tmp;
  int midval = 0;
  int i;

  for(i = 0; i < ListSize ; i++)
    {
      printf("%d ",a[i]);
    }
  printf("\n");

  while (step < ListSize)
    {
      step = step*2;
      for (i = 0 ; i < ListSize ; i+=step)
	{
	  globalops++;
	  tmp = i+step-1;
	  if (tmp >= ListSize)
	    {
	      tmp = ListSize -1 ;
	    }
	  midval=i + (step)/2 ;
	  if(midval > tmp)
	    {
	      midval = tmp;
	    }
	  inplacemerge(a,i,midval,tmp);
	}

      for(i = 0; i < ListSize ; i++)
	{
	  printf("%d ",a[i]);
	}
      printf("\n");
    }

}

int main(int argc, char *argv[])
{
  int *a = NULL;
  int *b = NULL;
  int *c = NULL;
  int i;

  clock_t start, end;
  double cpu_time_used;

  if(argc < 2)
    {
      printf("Your Mom...\n");
      exit(-1);
    }

  a = (int *)malloc(sizeof(int) * (argc-1));
  b = (int *)malloc(sizeof(int) * (argc-1));
  c = (int *)malloc(sizeof(int) * (argc-1));

  for(i= 1 ; i < argc; i++)
    {
      a[i-1] = atoi(argv[i]);
      b[i-1] = a[i-1];
      c[i-1] = a[i-1];
    }

  globalops=0;
  globalcomps=0;
  printf("Merge Sort (recursive) Theta(N lg N)\n");
  start = clock();
  mergsortreccurse(a,0,argc-2,argc-1);

  printf("Items : %d, Operations : %d , Compares : % d\n",argc-1,globalops,globalcomps);

  globalops=0;
  globalcomps=0;
  printf("Insertion Sort (recursive) Omega(N*N)\n");
  insertsortreccurse(b,0,argc-2,argc-1);

  printf("Items : %d, Operations : %d , Compares : % d\n",argc-1,globalops,globalcomps);

  globalops=0;
  globalcomps=0;
  printf("Merge Sort Theta(N Lg N)\n");
  mergesort(c,argc-1);

  printf("Items : %d, Operations : %d , Compares : % d\n",argc-1,globalops,globalcomps);



  return (0);
}
