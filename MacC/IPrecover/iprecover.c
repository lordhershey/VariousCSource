#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int A[4];

int main(int argc, char *argv[])
{
char buf[15];
int ret=0;

if(argc < 2)
	{
	fprintf(stderr,"usage:%s (ip address 4 to 10)\n",argv[0]);
	exit(-1);
	}
	
memset(buf,'\0',sizeof(buf));

snprintf(buf,sizeof(buf),"%s",argv[1]);

ret = figureOut(0,buf,strlen(buf));

if(!ret)
	{
	printf("Count not find valid IP Address Using %s\n",buf);
	exit(1);
	}
	
printf("A Valid IP Address is %d.%d.%d.%d\n",A[0],A[1],A[2],A[3]);
exit(0);
return (0);
}

int figureOut (int level,char *b,int sz)
{
int number;
char littlebuf[4];

if(level > 3)
	{
	/*All the Numbers are used up we did good*/
	if(sz < 1)
		{
		return (1);
		}
	/*numbers are left over - we suck*/
	return (0);
	}
	
if(sz < 1)
	{
	return (0);
	}
	
/*try 3*/
if('0' != b[0] && sz >= 3)
	{
	snprintf(littlebuf,4,"%3.3s",b);
	number = atoi(littlebuf);
	A[level] = number;
	if(number > 0 && number < 256)
		{
		if( figureOut((level+1),&b[3],(sz - 3)) )
			{
			return (1);
			}
		}
	}

/*try 2*/
if('0' != b[0] && sz >= 2)
	{
	snprintf(littlebuf,4,"%2.2s",b);
	number = atoi(littlebuf);
	A[level] = number;
	if(number > 0)
		{
		if(figureOut((level + 1), &b[2], (sz - 2) ) )
			{
			return (1);
			}
		}
	}

/*try 1*/
snprintf(littlebuf,4,"%1.1s",b);
number = atoi(littlebuf);
A[level] = number;
return ( figureOut((level + 1), &b[1], (sz - 1)) );
}

