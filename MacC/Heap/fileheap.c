
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int h_fd = -1;
FILE *infile = NULL;

#define KEYSIZE 10

void insertIntoHeap(char *trimbuff);
int binarySearchList(char *key,int a, int c);
int turnHeapIntoOrderedList();

int main(int argc, char *argv[])
{
  char inbuf[1000];
  char trimbuff[11];
  int ret;
  int hiidx;
  if(argc < 3)
    {
      fprintf(stderr,"USAGE:%s file1 file2",argv[0]);
      exit(-1);
    }
  
  h_fd = open("SortedHeap",O_RDWR|O_CREAT|O_TRUNC,0666);
  
  if(h_fd < 0)
    {
      fprintf(stderr,"Unable to overwrite SortedHeap file");
      exit(-1);
    }
  
  infile = fopen(argv[1],"r");
  
  if(NULL == infile)
    {
      fprintf(stderr,"Cannot open %s for reading",argv[1]);
      exit(-1);
    }
  
  /*insert into file*/
  for(memset(inbuf,'\0',1000);
      NULL != fgets(inbuf,1000,infile);
      memset(inbuf,'\0',1000))
    {
      /*kinda hacky if it was a proper record use memcpy
	if the line is shorter than 10 thenj the newline will become
	part of the key - this is just a toy anyway.*/
      snprintf(trimbuff,11,"%-10.10s             ",inbuf);
      insertIntoHeap(trimbuff);
    }

  fclose(infile);

  /*Turn the heap into linear array - there are goinf to be
    dups I did not want to get to complicated see program notes
    for removing dups*/
  turnHeapIntoOrderedList();  
  infile = fopen(argv[2],"r");

  for(memset(inbuf,'\0',1000);
      NULL != fgets(inbuf,1000,infile);
      memset(inbuf,'\0',1000))
    {
      /*this is the simulated second file*/
      snprintf(trimbuff,11,"%-10.10s             ",inbuf);
      hiidx = lseek(h_fd,0,SEEK_END) / KEYSIZE - 1;

      ret = binarySearchList(trimbuff,0,hiidx);
      if(ret > -1)
	{
	  printf("[%-10.10s] - Yes\n",trimbuff);
	}
      else
	{
	  printf("[%-10.10s] - No\n",trimbuff);
	}
    }

return(0);
}

int binarySearchList(char *key,int a, int c)
{
  int b;
  char buff[KEYSIZE];
  off_t loc;
  int readin;

  b = (a + c) / 2;

  if(c < a)
    {
      return(-1);
    }

  loc = lseek(h_fd,b * KEYSIZE,SEEK_SET);
  
  readin = read(h_fd,buff,KEYSIZE);

  /*printf("[%-10.10s], [%-10.10s] %d %d\n",key,buff,a,c);*/

  if(memcmp(key,buff,KEYSIZE) == 0)
    {
      return(b);
    }

  if(memcmp(key,buff,KEYSIZE) < 0)
    {
      return (binarySearchList(key,a,b - 1));
    }

  return(binarySearchList(key,b + 1, c));
}

void insertIntoHeap(char *trimbuff)
{
  off_t loc = 0;
  char buff[KEYSIZE];
  int wrote = 0;
  int index = -1;
  int parentindex = -1;
  int readin = 0;

  /*To not insert duplucated we would have to search
    the head the property of a heap in this case is the 
    higher value keys sit above the lower level keys it can make
    search a little difficult cause
  6         6
 4 5       5 4 
    are bot heaps. You would have to test the node, if it did not
    then you would need to check the right child to see if the value 
    could possibly be under it, if not found or not possible then check
    the other branch - basically you have to perfom a binary search
    in both directions - worst case scenario is that you hit each 
    element and that will only be n log base 2 n operations.
    if you find it then exit the routine here and you get no duplicates*/

  loc = lseek(h_fd,0,SEEK_END);

  index = (int)(loc / KEYSIZE);

  wrote = write(h_fd,trimbuff,KEYSIZE);

  for(parentindex = ((index * 2 - 1) / 4);
      parentindex != index && index != 0 && parentindex >= 0;
      index = parentindex,parentindex = ((index * 2 - 1) / 4))
    {

      loc = lseek(h_fd,parentindex * KEYSIZE,SEEK_SET);
      readin = read(h_fd,buff,KEYSIZE);

      if(memcmp(buff,trimbuff,KEYSIZE) == 0)
	{
	  break;
	}

      if(memcmp(buff,trimbuff,KEYSIZE) < 0)
	{
	  loc = lseek(h_fd,index * KEYSIZE,SEEK_SET);
	  wrote = write(h_fd,buff,KEYSIZE);

	  loc = lseek(h_fd,parentindex * KEYSIZE,SEEK_SET);
	  wrote = write(h_fd,trimbuff,KEYSIZE);

	  continue;
	}
      break;
    }

  return;
}

int heapDown(int index,int sizeofheap)
{
  int lc = (index + 1) * 2 -1;
  int rc = (index + 1) * 2; 
  int mididx = -1;
  char key[KEYSIZE];
  char midchild[KEYSIZE];
  char leftchild[KEYSIZE];
  char rightchild[KEYSIZE];
  off_t loc = 0;
  int numrecs = 0;
  int readin = 0;
  int wrote = 0;

  numrecs = sizeofheap;

  if(index >= numrecs || lc >= numrecs)
    {
      return(0);
    }

  loc = lseek(h_fd, index * KEYSIZE, SEEK_SET);
  readin = read(h_fd,key,KEYSIZE);

  loc = lseek(h_fd, lc * KEYSIZE, SEEK_SET);
  readin = read(h_fd,leftchild,KEYSIZE);

  if(rc > numrecs)
    {
      if(memcmp(key,leftchild,KEYSIZE) < 0)
	{
	  loc = lseek(h_fd, index * KEYSIZE, SEEK_SET);
	  wrote = write(h_fd,leftchild,KEYSIZE);

	  loc = lseek(h_fd, lc * KEYSIZE, SEEK_SET);
	  wrote = write(h_fd,key,KEYSIZE);
	}
      return (0);
    }

  loc = lseek(h_fd, rc * KEYSIZE, SEEK_SET);
  readin = read(h_fd,rightchild,KEYSIZE);

  if(memcmp(leftchild,rightchild,KEYSIZE) < 0)
    {
      memcpy(midchild,rightchild,KEYSIZE);
      mididx = rc;
    }
  else
    {
      memcpy(midchild,leftchild,KEYSIZE);
      mididx = lc;
    }

  if(memcmp(key,midchild,KEYSIZE) < 0)
    {
      loc = lseek(h_fd, index * KEYSIZE, SEEK_SET);
      wrote = write(h_fd,midchild,KEYSIZE);

      loc = lseek(h_fd, mididx * KEYSIZE, SEEK_SET);
      wrote = write(h_fd,key,KEYSIZE);
      heapDown(mididx,sizeofheap);
    }

  return(0);
}

int turnHeapIntoOrderedList()
{
  int numrecs = -1;
  int i = 0;
  off_t loc = 0;
  char key[KEYSIZE];
  char last[KEYSIZE];
  int readin;
  int wrote;

  loc = lseek(h_fd,0,SEEK_END);
  numrecs = loc / KEYSIZE;

  for(i = (numrecs - 1) ; i > 0 ; i--)
    {
      loc = lseek(h_fd,i * KEYSIZE,SEEK_SET);
      readin = read(h_fd,last,KEYSIZE);

      loc = lseek(h_fd,0,SEEK_SET);
      readin = read(h_fd,key,KEYSIZE);

      loc = lseek(h_fd,0,SEEK_SET);
      wrote = write(h_fd,last,KEYSIZE);

      loc = lseek(h_fd,i * KEYSIZE,SEEK_SET);
      wrote = write(h_fd,key,KEYSIZE);
      heapDown(0,i-1);
    } 

  return(0);
}

