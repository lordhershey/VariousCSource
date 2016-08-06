#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct TOKEN_NODE
{
  char *chars;
  int maxsize;
  struct TOKEN_NODE *next;
};

struct TOKEN_QUEUE
{
  struct TOKEN_NODE *head;
  int maxsize;
  int size;
  int pos;
  struct TOKEN_NODE *curr;
  struct TOKEN_NODE *end;
};


struct TOKEN_QUEUE *newTokenQueue(void)
{
    struct TOKEN_QUEUE *que = NULL;
    que = (struct TOKEN_QUEUE *)malloc(sizeof(struct TOKEN_QUEUE));

    /*TODO Check NULL*/
    que->head = NULL;
    /*! end point is used for exapanding the size of this Queue*/
    que->end = NULL;
    que->maxsize = 0;
    que->size = 0;
    /*! pos a quick look up to see if we are at the end.*/
    que->pos = 0;
    /*! this is our Reading head of the queue*/
    que->curr = NULL;
    return (que);
}

void clearTokenQueue(struct TOKEN_QUEUE *que)
{
    struct TOKEN_NODE *tok = NULL;

    que->end = NULL;
    que->maxsize = 0;

    if(que->head != NULL)
      {
	tok = que->head;
	while(tok != NULL)
	  {
	    /*We are one bigger*/
	    que->maxsize++;
	    que->end = tok;

	    if(tok->maxsize > 0)
	      {
		memset(tok->chars,'\0',tok->maxsize);
		/*Do Not Change Size if Non Zero*/
	      }
	    else
	      {
		/*force 0 and NULL*/
		tok->maxsize = 0;
		tok->chars = NULL;
	      }
	    tok = tok->next;
	  }
      }
    
    que->pos = 0;
    que->curr = que->head;
    que->size = 0;
}

void rewindTokenQueue(struct TOKEN_QUEUE *que)
{
    que->pos = 0;
    que->curr = que->head;
}

int enqueueToken(struct TOKEN_QUEUE *que,char *characters, int num)
{
    int i;
    struct TOKEN_NODE *tok = NULL;

    if (NULL == que || num < 0)
      {
	return (-1);
      }

    /*There are 2 cases - either we expand the que, or we recycle
      an old node (possibly expanding it)*/

    if(que->maxsize > que->size)
      {
	tok = que->head;
	/*We Recycle a node*/
	for(i=0 ; i < que->size ; i++)
	  {
	    tok=tok->next;
	    if(tok == NULL)
	      {
		/*FATAL Queue Integrity Error*/
		return (-2);
	      }
	  }

	/*expand Token*/
	if((NULL == tok->chars) || (tok->maxsize < (num + 1)))
	  {
	    if(NULL != tok->chars)
	      {
		free (tok->chars);
		tok->chars = NULL;
		tok->maxsize = 0;
	      }

	    tok->maxsize = (num + 1);
	    tok->chars = malloc(tok->maxsize * sizeof(char));
	  }
	memset(tok->chars,'\0',tok->maxsize);
	if(num > 0)
	  {
	    snprintf(tok->chars,tok->maxsize,"%.*s",num,characters);
	  }
	que->size++;
	return (que->size);
      }


    tok = (struct TOKEN_NODE *)malloc(sizeof(struct TOKEN_NODE));
    tok->maxsize=(num + 1);
    tok->chars = (char *)malloc(sizeof(char) * (tok->maxsize));
    tok->next = NULL;

    memset(tok->chars,'\0',tok->maxsize);
    if(num > 0)
      {
	snprintf(tok->chars,tok->maxsize,"%.*s",num,characters);
      }

    /*We need to expand the Queue*/
    /*First case, the head it NULL*/
    if(NULL == que->head)
      {
	que->head = tok;
	que->curr = que->head;
	que->maxsize=1;
	que->size=1;
	que->end=que->head;
	que->pos = 0;
	return (1);
      }

    /*attach to the end*/
    que->end->next = tok;
    que->end = que->end->next;
    que->maxsize++;
    que->size++;

    return(que->size);
}

char *popTokenQueue(struct TOKEN_QUEUE *que,int *errFlag,int *overCount)
{

    char *ptr = NULL;

    if(NULL != errFlag)
      {
	*errFlag = 0;
      }

    if (NULL == que)
      {
	if(NULL != errFlag)
	  {
	    *errFlag = -1;
	  }
	return (NULL);
      }

    if(que->pos >= que->size)
      {
	if(NULL != errFlag)
	  {
	    *errFlag = 1;
	  }
	if(NULL != overCount)
	  {
	    *overCount = (*overCount) + 1;
	  }
	return (NULL);
      }

    if(NULL == que->curr)
      {
	if(NULL != errFlag)
	  {
	    /*Integrity Error*/
	    *errFlag = -2;
	  }
	return (NULL);
      }

    ptr = que->curr->chars;
    que->curr = que->curr->next;
    que->pos++;
    return (ptr);
}

void parseTildeTokens(struct TOKEN_QUEUE *que,char *str)
{
    int i;
    int pos = 0;
    char *ptr = NULL;
    int ret;
    int flag = 0;
    int recordType = -1;

    if(NULL == str)
      {
	return;
      }

    for(i = 0; i < strlen(str);i++)
      {
	if('~' == str[i])
	  {
	    ptr = &str[pos];
	    /*
	    if (i == pos)
	      {
		printf("( EMPTY )\n");
	      }
	    else
	      {
		printf("%.*s\n",(i - pos),ptr);
	      }

	    */
	    ret = enqueueToken(que,ptr,(i - pos));
	    pos = i+1;
	  }
      }
    if(pos < i)
      {
	ptr = &str[pos];
	/*
	if (i == pos)
	  {
	    printf("( EMPTY )\n");
	  }
	else
	  {
	    printf("%.*s\n",(i - pos),ptr);
	  }
	*/
	ret = enqueueToken(que,ptr,(i - pos));
      }

    recordType = -1;
    ptr = popTokenQueue(que,&flag,NULL);
    if(NULL != ptr)
      {
	if(strcmp(ptr,"0") == 0)
	  {
	    /*Header Record*/
	    recordType = 0;
	  }
	if(strcmp(ptr,"9999999") == 0)
	  {
	    recordType = 1;
	  }
      }
    if(-1 == recordType)
      {
	popTokenQueue(que,NULL,NULL);
	ptr = popTokenQueue(que,&flag,NULL);
	if(NULL != ptr)
	  {
	    if(strcasecmp(ptr,"ACCOUNT") == 0)
	      {
		recordType = 2;
	      }
	    if(strcasecmp(ptr,"CUSTOMER") == 0)
	      {
		recordType = 3;
	      }
	    if(strcasecmp(ptr,"ADDRESS") == 0)
	      {
		recordType = 4;
	      }
	    if(strcasecmp(ptr,"2NDPARTY") == 0)
	      {
		recordType = 5;
	      }
	    if(strcasecmp(ptr,"NOTES") == 0)
	      {
		recordType = 6;
	      }
	  }
      }

    rewindTokenQueue(que);
    flag = 0;

    switch(recordType)
      {
      case 0:
	printf("====== HEADER RECORD TYPE   ======\n");
	break;
      case 1:
	printf("====== TRAILER RECORD TYPE  ======\n");
	break;
      case 2:
	printf("====== ACCOUNT RECORD TYPE  ======\n");
	break;
      case 3:
	printf("====== CUSTOMER RECORD TYPE ======\n");
	break;
      case 4:
	printf("====== ADDRESS RECORD TYPE  ======\n");
	break;
      case 5:
	printf("====== 2NDPARTY RECORD TYPE ======\n");
	break;
      case 6:
	printf("====== NOTES RECORD TYPE    ======\n");
	break;
      default:
	printf("====== UNKNOWN RECORD TYPE  ======\n");
	break;
      }

    while(!flag)
      {
	ptr = popTokenQueue(que,&flag,NULL);
	if (1 == flag)
	  {
	    printf("[ END ]\n");
	    break;
	  }
	if(NULL != ptr && *ptr)
	  {
	    printf("%s\n",ptr);
	  }
	else
	  {
	    printf("( EMPTY )\n");
	  }
      }
    
}

int main(int argc, char *argv[])
{

    FILE *f;
    char buffer[6001];
    int i,j;
    
    struct TOKEN_QUEUE *tokenQue = NULL;
    
    if (argc < 2)
      {
	printf("Need File Name\n");
	exit(0);
      }
    
    f = fopen(argv[1],"r");
    
    if(NULL == f)
      {
	printf("Sorry, Cannot open file %s\n",argv[1]);
	exit(-1);
      }
    
    tokenQue = newTokenQueue();
    
    for(memset(buffer,'\0',sizeof(buffer));
	fgets(buffer,sizeof(buffer),f) != NULL;
	memset(buffer,'\0',sizeof(buffer)))
      {
	clearTokenQueue(tokenQue);
	
	for(i = strlen(buffer) - 1; i >   strlen(buffer) - 5;i--)
	  {
	    if('\n' == buffer[i] || '\r' == buffer[i])
	      {
		buffer[i] = '\0';
	      }
	  }

	/*wipe out non printing binary characters*/
	for(i = strlen(buffer) - 1; i > -1 ; i--)
	  {
	    if(!isprint(buffer[i]))
	      {
		for (j = i + 1 ; j < strlen(buffer) -1 ; j++)
		  {
		    buffer[(j-1)] = buffer[j];
		  }
		buffer[j] = '\0';
	      }
	  }

	parseTildeTokens(tokenQue,buffer);
      }
    
    fclose(f);
    return(0);
}
