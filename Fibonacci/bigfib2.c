#include<stdlib.h>
#include<stdio.h>
#include <string.h>

#include<sys/types.h>
#include<unistd.h>

#include<sys/stat.h>
#include<fcntl.h>

#define MAX_BUCKET_VALUE (unsigned long)1000000000

void addNumToPos(unsigned long num,int pos, int fd)
{
  unsigned long thischar = 0;
  int readin;
  int wrote;
  unsigned long carry = 0;

  for(;;)
  {
    if(num == 0)
      {
        /*no need to go further*/
        break;
      }

    lseek(fd,pos*sizeof(unsigned long),SEEK_SET);
    readin = read(fd,&thischar,sizeof(unsigned long));

    if(readin < sizeof(unsigned long))
      {
        thischar = 0L;
      }

    num += thischar;

    carry = 0;

    if(num >= MAX_BUCKET_VALUE)
      {
        carry =  1;
        num = num - MAX_BUCKET_VALUE;
      }

    thischar = num;

    lseek(fd,pos*sizeof(unsigned long),SEEK_SET);

    wrote = write(fd,&thischar,sizeof(unsigned long));

    if(carry)
      {
        pos++;
        num = carry;
        continue;
      }

    break;
  }
}


void writeNumber(int fd)
{
  int lim;
  int i;
  unsigned long thischar;
  int readin;
  char buffer[20];
  int first = 1;
  int j;

  lim = lseek(fd,0,SEEK_END);
  for(i = (lim/sizeof(unsigned long))-1; i > -1; i--)
    {
      lseek(fd,i*sizeof(unsigned long),SEEK_SET);

      readin = read(fd,&thischar,sizeof(unsigned long));
      if(first)
	{
	  printf("%d",thischar);
	}
      else
	{
	  /*printf("%9d",thischar);*/
	  snprintf(buffer,sizeof(buffer),"%9d",thischar);
	  for(j = 0; j < 9;j++)
	    {
	      if(buffer[j] == ' ')
		{
		  buffer[j] = '0';
		  continue;
		}
	      break;
	    }
	  printf("%9.9s",buffer);
	}

      first = 0;
    }
  printf("\n");
}

void addSmallToBig(int sm,int bg)
{
  int pos;
  int i;
  unsigned long thischar;
  int readin;

  pos = lseek(sm,0,SEEK_END);

  for(i = ((pos/sizeof(unsigned long))-1); i > -1; i--)
    {
      lseek(sm,i*sizeof(unsigned long),SEEK_SET);
      readin = read(sm,&thischar,sizeof(unsigned long));
      addNumToPos(thischar,i, bg);
    }
}


int main(int argc, char *argv[])
{

  int smallf = -1;
  int bigf = -1;
  int tmp = -1;
  int i,lim;
  unsigned long one = 1;

  if(argc < 2)
    {
      printf("%s number\n",argv[0]);
      exit(-1);
    }

  fprintf(stderr,"Size of unsigned long :%d\n\n",sizeof(unsigned long));

  lim = atoi(argv[1]);

  smallf = open("num1-32",O_RDWR|O_CREAT|O_TRUNC,0666);
  write(smallf,&one,sizeof(unsigned long));

  bigf = open("num2-32",O_RDWR|O_CREAT|O_TRUNC,0666);
  write(bigf,&one,sizeof(unsigned long));

  for(i = 2; i < lim ; i++)
    {

      /*swap file handles*/
      tmp = smallf;
      smallf = bigf;
      bigf = tmp;

      addSmallToBig(smallf,bigf);

      fprintf(stderr,"\r%d",i);

    }
  fprintf(stderr,"\n\n");

  writeNumber(bigf);

  exit(0);
}
