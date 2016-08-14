#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char table[] = {'A','B','C','D','E','F','G','H',
		'I','J','K','L','M','N','O','P',
		'Q','R','S','T','U','V','W','X',
		'Y','Z','a','b','c','d','e','f',
		'g','h','i','j','k','l','m','n',
		'o','p','q','r','s','t','u','v',
		'w','x','y','z','0','1','2','3',
		'4','5','6','7','8','9','+','/'};

int TableIndexOf(char a)
{
  int i;

  for(i = 0 ; i < 64 ; i++)
    {
      if(a == table[i])
	{
	  return(i);
	}
    }

  return(-1);
}

unsigned char *decodeBase64Quad(unsigned char *a1, 
				unsigned char *a2, 
				unsigned char *a3,
				unsigned char *a4)
{
  static unsigned char buff[3];

  int size = 1;

  int idx;

  unsigned char mask1 = 0xFC;
  unsigned char mask2a = 0x03;
  unsigned char mask2b = 0xF0;
  unsigned char mask3a = 0x0F;
  unsigned char mask3b = 0xC0;
  unsigned char mask4 = 0x3F;

  unsigned char i;

    /* INDENT-OFF
  11111100 00000000 00000000
  00000011 11110000 00000000
  00000000 00001111 11000000
  00000000 00000000 00111111
    INDENT-ON */

  memset(buff,'\0',4);

  if('=' == *a1)
    {
      a1 = NULL;
    } 

  if('=' == *a2)
    {
      a2 = NULL;
    } 

  if('=' == *a3)
    {
      a3 = NULL;
    } 

  if('=' == *a4)
    {
      a4 = NULL;
    } 


  if(NULL == a1)
    {
      return(NULL);
    }

  i = (unsigned char )TableIndexOf(*a1);

  buff[0] = i << 2;

  if(NULL == a2)
    {
      return(buff);
    }

  i = (unsigned char )TableIndexOf(*a2);

  buff[0] = buff[0] | (i >> 4);
  buff[1] = (i << 4);

  if(NULL == a3)
    {
      return(buff);
    }

  i = (unsigned char )TableIndexOf(*a3);
  
  buff[1] = buff[1] | (i >> 2);
  buff[2] = (i << 6);

  if(NULL == a4)
    {
      return(buff);
    }

  i = (unsigned char )TableIndexOf(*a4);

  buff[2] = buff[2] | i;

  return (buff);

}

int main(int argc, char *argv[])
{

  int i;
  char *ptr = NULL;

  if(argc < 2)
    {
      /*printf("Put a String in on the command line\n\n");*/
      char buff[3];
      int readin;
      int fd = open("THEFILE",O_RDONLY);
      if(fd < 1)
	{
	  printf("File THEFILE cannot be opend for reading\n");
	  exit(-1);
	}
      
      while ((readin = read(fd,buff,3)) > 0)
	{
	  ptr = NULL;
	  switch(readin)
	    {
	    case 1:
	      ptr = decodeBase64Quad(&buff[0],NULL,NULL,NULL);
	      break;
	    case 2:
	      ptr = decodeBase64Quad(&buff[0],&buff[1],NULL,NULL);
	      break;
	    case 3:
	      ptr = decodeBase64Quad(&buff[0],&buff[1],&buff[2],NULL);
	      break;
	    case 4:
	      ptr = decodeBase64Quad(&buff[0],&buff[1],&buff[2],&buff[3]);
	      break;

	    }

	  if(NULL != ptr )
	    {
	      printf("%-3.3s",ptr);
	    }
	}

      close(fd);
      printf("\n\n");
      exit(0);
    }

  printf("[[[");
  for(i = 0 ; i < strlen(argv[1]); i += 4)
    {

      ptr = NULL;
      switch(strlen(&argv[1][i]))
	{
	case 0:
	  break;
	case 1:
	  ptr = decodeBase64Quad(&argv[1][i],NULL,NULL,NULL);
	  break;
	case 2:
	  ptr = decodeBase64Quad(&argv[1][i],&argv[1][(i+1)],NULL,NULL);
	  break;
	case 3:
	  ptr = decodeBase64Quad(&argv[1][i],&argv[1][(i+1)],&argv[1][(i+2)],NULL);
	  break;
	default:
	  ptr = decodeBase64Quad(&argv[1][i],&argv[1][(i+1)],&argv[1][(i+2)],&argv[1][(i+3)]);
	  break;
	}

      if(NULL == ptr)
	{
	  break;
	}

      printf("%-3.3s",ptr);

    }

  printf("]]]\n");

  exit(0);
}
