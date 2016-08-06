/* Can compile for 32 vor 64 bit */

#include<stdlib.h>
#include<stdio.h>

#include<sys/types.h>
#include<unistd.h>

#include<sys/stat.h>
#include<fcntl.h>

void addNumToPos(char num,int pos, int fd)
{
  char thischar;
  int readin;
  int wrote;
  int carry;

  num = num - '0';

  for(;;)
  {
    if(num < 1)
      {
	/*no need to go further*/
	break;
      }
    lseek(fd,pos,SEEK_SET);
    readin = read(fd,&thischar,1);

    if(readin < 1)
      {
	thischar = '0';
      }

    num += (thischar - '0');

    carry = 0;

    if(num > 9)
      {
	carry = 1;
	num = num - 10;
      }

    thischar = '0' + num;

    lseek(fd,pos,SEEK_SET);
    wrote = write(fd,&thischar,1);

    if(carry)
      {
	pos++;
	num = 1;
	continue;
      }

    break;
  }
}

void writeNumber(int fd)
{
  int lim;
  int i;
  char thischar;
  int readin;

  lim = lseek(fd,0,SEEK_END);
  for(i = lim-1; i > -1; i--)
    {
      lseek(fd,i,SEEK_SET);
      readin = read(fd,&thischar,1);
      printf("%c",thischar);
    }
  printf("\n");
}

void addSmallToBig(int sm,int bg)
{
  int pos;
  int i;
  char thischar;
  int readin;

  pos = lseek(sm,0,SEEK_END);

  for(i = pos-1; i > -1; i--)
    {
      lseek(sm,i,SEEK_SET);
      readin = read(sm,&thischar,1);
      addNumToPos(thischar,i, bg);
    }
}

int main(int argc, char *argv[])
{

  int smallf = -1;
  int bigf = -1;
  int tmp = -1;
  int i,lim;


  if(argc < 2)
    {
      printf("%s number\n",argv[0]);
      exit(-1);
    }

  lim = atoi(argv[1]);

  smallf = open("num1",O_RDWR|O_CREAT|O_TRUNC,0666);
  write(smallf,"1",1);

  bigf = open("num2",O_RDWR|O_CREAT|O_TRUNC,0666);
  write(bigf,"1",1);

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
