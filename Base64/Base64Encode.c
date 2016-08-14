#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* INDENT-OFF */
char table[] = {'A','B','C','D','E','F','G','H',
		'I','J','K','L','M','N','O','P',
		'Q','R','S','T','U','V','W','X',
		'Y','Z','a','b','c','d','e','f',
		'g','h','i','j','k','l','m','n',
		'o','p','q','r','s','t','u','v',
		'w','x','y','z','0','1','2','3',
		'4','5','6','7','8','9','+','/'};
/* INDENT-ON */

char *encodeBase64Tripple(unsigned char *a1, 
			  unsigned char *a2, 
			  unsigned char *a3)
{
  static char buff[4];
  char readbuf[3];
  int size = 1;

  int idx;

  unsigned char mask1 = 0xFC;
  unsigned char mask2a = 0x03;
  unsigned char mask2b = 0xF0;
  unsigned char mask3a = 0x0F;
  unsigned char mask3b = 0xC0;
  unsigned char mask4 = 0x3F;

    /* INDENT-OFF
  11111100 00000000 00000000
  00000011 11110000 00000000
  00000000 00001111 11000000
  00000000 00000000 00111111
    INDENT-ON */

  memset(readbuf,'\0',3);

  if(NULL == a1)
    {
      return(NULL);
    }

  readbuf[0] = *a1;
  if(a2 != NULL)
    {
      size++;
      readbuf[1] = *a2;
      
      if (a3 != NULL)
	{
	  size++;
	  readbuf[2] = *a3;
	}
    }

  idx = (mask1 & readbuf[0]) >> 2;

  buff[0] = table[idx];

  idx = ((mask2a & readbuf[0]) << 4) | ((mask2b & readbuf[1]) >> 4);

  buff[1] = table[idx];

  idx = ((mask3a & readbuf[1]) << 2) | ((mask3b & readbuf[2]) >> 6);

  buff[2] = table[idx];

  idx = (mask4 & readbuf[2]);

  buff[3] = table[idx];

  if(size < 3)
    {
      buff[3] = '=';

      if(size < 2)
	{
	  buff[2] = '=';
	}

    }

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
	      ptr = encodeBase64Tripple(&buff[0],NULL,NULL);
	      break;
	    case 2:
	      ptr = encodeBase64Tripple(&buff[0],&buff[1],NULL);
	      break;
	    case 3:
	      ptr = encodeBase64Tripple(&buff[0],&buff[1],&buff[2]);
	      break;

	    }

	  if(NULL != ptr )
	    {
	      printf("%4.4s",ptr);
	    }
	}

      close(fd);
      printf("\n\n");
      exit(0);
    }

  for(i = 0 ; i < strlen(argv[1]); i += 3)
    {

      ptr = NULL;
      switch(strlen(&argv[1][i]))
	{
	case 0:
	  break;
	case 1:
	  ptr = encodeBase64Tripple(&argv[1][i],NULL,NULL);
	  break;
	case 2:
	  ptr = encodeBase64Tripple(&argv[1][i],&argv[1][(i+1)],NULL);
	  break;
	default:
	  ptr = encodeBase64Tripple(&argv[1][i],&argv[1][(i+1)],&argv[1][(i+2)]);
	  break;
	}

      if(NULL == ptr)
	{
	  break;
	}

      printf("%4.4s",ptr);

    }

  printf("\n");

  exit(0);
}
