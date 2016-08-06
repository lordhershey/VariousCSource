#include <stdio.h>
#include <stdlib.h>

int sort(int *a,int s)
{

  int i;
  int j;
  int k;
  int tmp;

  int ops = 0;
  int swaps = 0;
  int oloop = 0;

  int inorder = 0;

  for(i = 0 ; i < (s-1) ; i++)
    {
      inorder = 1;
      oloop ++;

      for(j = (s-1) ; j > i ; j--)
	{
	  ops ++;
	  if(a[i] > a[j])
	    {
	      swaps++;
	      /*Swap & continue;*/
	      /*inorder = 0;*/
	      tmp = a[i];
	      a[i] = a[j];
	      a[j] = tmp;
	    }

	  if(a[j] < a[j-1])
	    {
	      inorder = 0;
	    }
	}

      if(inorder)
	{
	  break;
	}

      for(k= 0 ; k < s ; k++)
	{
	  printf("%d ",a[k]);
	}
      printf("\n");

    }

  printf("Number Outter   : %d\n",oloop);
  printf("Number of Inner : %d\n",ops);
  printf("Number of swaps : %d\n",swaps);

  return (0);
}

int main(int argc, char *argv[])
{
  int *list=NULL;
  int numels=0;
  int i;

  if(argc < 2)
    {
      printf("USAGE:%s num1 num2 num3 ...\n",argv[0]);
      exit(-1);
    }

  numels = argc - 1;

  list = (int *)malloc(sizeof(int) * numels);

  for(i = 0 ; i < numels ; i++)
    {
      list[i] = atoi(argv[i + 1]);
    }

  sort(list,numels);

  for(i = 0 ; i < numels ; i++)
    {
      printf("%d ",list[i]);
    }

  printf("\n");
  return (0);
}

