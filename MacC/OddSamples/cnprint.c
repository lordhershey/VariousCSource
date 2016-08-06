#include <stdio.h>
#include <stdlib.h>

#include <stdarg.h>

int cnprintf(char *p_buff,int p_len,char *fmt, ...)
{
  int ret = 0;
  int i;
  int lgt = 0;
  int hasgt = 0;

  va_list args;
  
  memset(p_buff,'\0',p_len);

  va_start(args, fmt);
  ret = vsnprintf(p_buff, p_len, fmt, args);
  va_end(args);

  /*wash out < and >*/
  for(i = 0; i < p_len; i++)
    {
      if('<' == p_buff[i])
	{
	  if(hasgt)
	    {
	      p_buff[lgt] = ' ';
	      lgt = i;
	    }
	  else
	    {
	      hasgt = 1;
	      lgt = i;
	    }
	}
      if('>' == p_buff[i])
	{
	  if(hasgt)
	    {
	      hasgt = 0;
	    }
	  else
	    {
	      p_buff[i] = ' ';
	    }
	}
    }

  if(hasgt)
    {
      p_buff[lgt] = ' ';
      hasgt = 0;
    }

  return (ret);
}

int main(int argc, char *argv[])
{
  char s[1000];
  char entry[1000];
  for(;;)
    {
      memset(s,'\0',1000);
      printf("Enter a string ");
      if(NULL == fgets(entry,1000,stdin))
	{
	  exit(0);
	}
      printf("\nyour washed string is\n");
      cnprintf(s,1000,"%s",entry);
      printf("[%s]\n",s);
    }
}
