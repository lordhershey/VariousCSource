#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    int i,j,k;
 
    k = 0;
    for(i = 0 ; i < 100 ; i++)
      {
	for (j = 0 ; j < 10 ; j++)
	  {
	    k++;
	    printf("INSERT INTO doc_detail VALUES ('4','','TD%04d','','','','','','','','DOCTYPE','20','/tmp','Fake-%05d.txt','001','2015-10-14','','','','','','','','','','','','','','','','','');\n",i,k);

	    fprintf(stderr,"echo \"ABCDEFGHIJKLMNOPQRSTUVWXYZ\" > /tmp/Fake-%05d.txt ; chmod 644 /tmp/Fake-%05d.txt \n",k,k);

	  }
      }

    return (0);
}
