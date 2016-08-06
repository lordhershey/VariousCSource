#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
  char buf[500];
  int i,j;
  int a;

  if(argc < 2)
    {
      fprintf(stderr,"usage:%s strings with numbers",argv[0]);
      exit(-1);
    }

  for(j = 1 ; j < argc ; j++)
    {
      snprintf(buf,500,"%s",argv[j]);

      /* step through front white space */
      for(i = 0 ; i < strlen(buf) && !isdigit(buf[i]) ; i++);
      
      for(a = 0; i < strlen(buf) ; i++)
	{
	  
	  if(isdigit(buf[i]))
	    {
	      a = 10 * a + (int)buf[i] - (int)'0';
	    }
	  
	  /*Non Digit or End Condition*/
	  if(!isdigit(buf[i]) || i >= (strlen(buf)-1))
	    {
	      printf("a = %d\n",a);
	      a = 0;

	      /* step through */
	      for(; i < strlen(buf) && !isdigit(buf[i]);i++)
		{
		  if( (i < (strlen(buf) - 1)) && isdigit(buf[(i+1)]))
		    break; 
		}

	    }
	  
	}
    }
  exit(0);
  return (0);
}

