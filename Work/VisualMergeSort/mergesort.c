#include "stdio.h"
#include "stdlib.h"

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

void mergesort(int *a,int start, int end)
{

  int elems = 0;
  int i;

  if(start >= end)
    {
      return;
    }

  elems = (end - start);

  printf ("(V) %3d .. %3d , %3d .. %3d : ",start,start+elems/2,start+elems/2+1,end);
  for(i = start;  i <= end ; i++)
    {
      printf ("%d ",a[i]);
    }
  printf("\n");


  mergesort(a,start,start+elems/2);
  mergesort(a,start+elems/2+1,end);
 
  inplacemerge(a,start,start+elems/2+1,end);

  printf ("(^) %3d .. %3d , %3d .. %3d : ",start,start+elems/2,start+elems/2+1,end);
  for(i = start;  i <= end ; i++)
    {
      printf ("%d ",a[i]);
    }
  printf("\n");


  return;
}

int main(int argc, char *argv[])
{
  int *a = NULL;
  int i;

  /*
  int a[] = {1,3,5,7,9,0,2,4,6,8};
  int i;

  for(i = 0;  i < 10 ; i++)
    {
      printf ("%d ",a[i]);
    }
  printf("\n");

  inplacemerge(a,0,5,9);
  */

  if(argc < 2)
    {
      printf("Your Mom...\n");
      exit(-1);
    }

  a = (int *)malloc(sizeof(int) * (argc-1));

  for(i= 1 ; i < argc; i++)
    {
      a[i-1] = atoi(argv[i]);
    }

  for(i = 0;  i < argc-1 ; i++)
    {
      printf ("%d ",a[i]);
    }
  printf("\n");

  printf("^^^^ BEFORE\n");

  mergesort(a,0,argc-2);

  printf("VVVV AFTER\n");


  for(i = 0;  i < argc-1 ; i++)
    {
      printf ("%d ",a[i]);
    }
  printf("\n");




}
