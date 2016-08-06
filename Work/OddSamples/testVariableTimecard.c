#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define DELETE_CHAR_MARKER (char)127

void FindTimecardEntrySizeAndLocation(int fd,int *bufsize,off_t *loc,int *recordsize,int *numrecords)
{
    off_t curloc = 0;

    off_t place = 0;
    int i,j;
    int len = 0; 
    int longest = -1;

    int lastlen = 0;

    int grabnextpos = 0;

    int readin;
    char buff[512];

    off_t lastplace = 0;
    int numrecs=0;

    curloc = lseek(fd,0,SEEK_CUR);

    lseek(fd,0,SEEK_SET);

    j = 0;
    for(memset(buff,'\0',512);
	(readin = read(fd,buff,512)) > 0;
	memset(buff,'\0',512))
      {
	for(i = 0; i < readin ; i++,j++)
	  {
	    len++;
	    if(DELETE_CHAR_MARKER == buff[i])
	      {
		numrecs++;
		lastlen = len;
		if(len > longest)
		  {
		    longest = len;
		  }
		len = 0;
		grabnextpos = 1;
		continue;
	      }

	    if(grabnextpos)
	      {
		grabnextpos = 0;
		lastplace = place;
		place = j;
	      }

	  }
      }

    if(!grabnextpos)
      {
	/*a delete character should be the last thing seen, if it is not then
	  there is a new line or other bit of garbage at the end of the record
	  which means we do not want it.*/
	place = lastplace;
      }

    *bufsize = longest;
    *loc = place;

    if(NULL != recordsize)
      {
	*recordsize = lastlen;
      }

    if(NULL != numrecords)
      {
	*numrecords = numrecs;
      }

    lseek(fd,curloc,SEEK_SET);
}


int main(int argc, char *argv[])
{
  int fd = -1;

  off_t curloc = 0;
  int size = 0;
  int readin;
  int lastsize = 0;
  int numrecs = 0;

  char *buff = NULL;

  fd = open ("testcard.txt",O_RDWR);

  FindTimecardEntrySizeAndLocation(fd,&size,&curloc,&lastsize,&numrecs);


  printf("Location : %d, Max Size : %d, Last Record Size : %d, Records in File : %d\n",(int)curloc,size,lastsize,numrecs); 


  /*note - no error check on size or locaiton*/

  buff = malloc(size * sizeof(char));

  memset(buff,'\0',size);

  lseek(fd,curloc,SEEK_SET);

  readin = read(fd,buff,lastsize);

  printf("Read in %d Bytes..\n",readin);
  printf("Record (Del Char not seen) [%*.*s]\n",lastsize,lastsize,buff);


  close(fd);
}
