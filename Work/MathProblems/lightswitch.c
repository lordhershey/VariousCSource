#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
  int arr[100];
  int i,k;
  int step = 0;

  memset((char *)arr,'\0',sizeof(arr));

  for(step = 0;step < 100;step++)
    {
      int modulus = step + 1;

      for(i = 0; i < 100 ; i++)
	{
	  if(((i + 1) % modulus) == 0)
	    {
	      arr[i] = (arr[i] + 1) % 2;
	    }
	}

      for(k = 0 ; k < 100 ; k++)
	{
	  printf("%c",arr[k] ? '*' : ' ');
	}

      printf("\n");

    }
  return 0;

}
