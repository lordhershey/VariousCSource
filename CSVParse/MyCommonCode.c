#ifdef __linux__
#  include <getopt.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>   /* umask */ 
#include <fcntl.h>
#include <ctype.h>      /* isalnum, isdigit */
#include <stdarg.h>
#include <string.h>

/*
#define MY_COMMON_CODE_PROTO
*/

#include "MyCommonCode.h"

static int UpcaseTokens = 0;

int main(int argc, char argv[])
{
    int i,j;
    char sep[5] = ",,|\t ";
    char quot[5] = "\"\"\"\"\'";
    struct TOKEN_QUEUE *mytokens = NULL;
    FILE_STATE fs;
    int ret = 0;
    char txt[25];

    memset((void *)&fs,'\0',sizeof(fs));

    umask(0);

    fs.fd = open("sampleFile.csv", O_RDONLY);

    if (fs.fd < 0)
    {
        fprintf(stderr,"Cannot open %s for Reading", "sampleFile.csv");
        return (-1);
    }

    for(; ret > -1; 
	ret = fillTokensFromFile(&fs, 
				   &mytokens, 
				   ',', 
				   0, 
				   1,
				   '\"'))
      {

	if(ret < 1)
	  {
	    continue;
	  }

	printf("Tokens : %2d ",ret);

	for(j = 0 ; j < ret ; j++)
	{
	    setCharField(txt, sizeof(txt), getTokenNumber(mytokens, j));
	    trimSpaceAndZeroFromBeginToEnd(txt,sizeof(txt));
	    if(strlen(txt) > 0)
	    {
	        printf("[%*.*s]",strlen(txt),strlen(txt),txt);
	    }
	    else
	    {
		printf("[NULL]");
	    }
	}
	printf("\n");
        
        freeTokenQueue(&mytokens);
      }

    close(fs.fd);

}

/* *INDENT-OFF*
   ############################################################
   #              Input Options and Validation                #
   ############################################################
   *INDENT-ON* */
/*!
  \brief trim the spaces and null characters from a byte
  sequence replacing them with just spaces.
  
  \param[in] s the character buffer
  \param[in] z the size of the buffer
  \return 0 if ok, -1 if s is NULL or sz < 1
 */
int trimSpaceAndZeroFromEnd(char *s, int sz)
{
    int i;

    if (s == NULL || sz < 1)
    {
        return -1;
    }

    for (i = (sz - 1); i > -1; i--)
    {
        if (s[i] == '\0' || s[i] == ' ' || s[i] == '\n' || s[i] == '\r')
        {
            s[i] = '\0';
            continue;
        }
        break;
    }

    return 0;
}

/*!
  \brief clean out the white space from the front and back

  \param[in] s the string to clean
  \param[in] sz the size of the buffer
  \retval 0 success
  \retval -1 failure
 */
int trimSpaceAndZeroFromBeginToEnd(char *s, int sz)
{
    int i, j;

    if (NULL == s || sz < 1)
    {
        return (-1);
    }

    /*cut off white space on front */
    for (i = 0; i < (sz - 1) &&
         ('\0' == s[0] ||
          ' ' == s[0] || '\n' == s[0] || '\r' == s[0] || '\t' == s[0]); i++)
    {
        for (j = 1; j < sz; j++)
        {
            s[(j - 1)] = s[j];
            s[j] = ' ';
        }
    }
    return (trimSpaceAndZeroFromEnd(s, sz));
}

/*!
  \brief copy a CSV token to a fixed size buffer

  \param[out] fld the target character field
  \param[in] size the size of fld
  \param[in] src a null terminated string
  \return the size of the string
  \retval -1 some issue with fld or size of fld
 */
int setCharField(char *fld, int size, char *src)
{
    if (NULL == fld || size < 1)
    {
        return (-1);
    }

    memset(fld, '\0', size);

    if ((NULL == src) || (strlen(src) < 1))
    {
        return (1);
    }

    snprintf(fld, size, "%s", src);

    return (strlen(fld));
}




/* *INDENT-OFF*
   ############################################################
   #                Parsing and Data Handling                 #
   ############################################################
   *INDENT-ON* */

/*!
  \brief shoves a character onto an expanding array

  \param[out] head pointer to a pointer
  \param[in] inChar the character we wish to save
  \retval the length of queue
*/
int enqueueCharacter(struct CHARACTER_QUEUE **head, char inChar)
{
    struct CHARACTER_QUEUE *tmp = NULL;
    int block = 0;

    if (NULL == *head)
    {
        tmp = (struct CHARACTER_QUEUE *)malloc(sizeof(struct CHARACTER_QUEUE));
        memset((char *)tmp, '\0', sizeof(struct CHARACTER_QUEUE));
        tmp->len = 0;
        tmp->next = NULL;
        *head = tmp;
    }

    tmp = *head;

    while (tmp->next != NULL)
    {
        tmp = tmp->next;
        block++;
    }

    if (tmp->len > (CHARACTER_QUEUE_BUFFER_SIZE - 1))
    {
        /*we need a new block */
        tmp->next = (struct CHARACTER_QUEUE *)
                            malloc(sizeof(struct CHARACTER_QUEUE));
        memset((char *)tmp->next, '\0', sizeof(struct CHARACTER_QUEUE));
        tmp->next->len = 0;
        tmp->next->next = NULL;
        tmp = tmp->next;
        block++;
    }

    tmp->buffer[tmp->len++] = inChar;

    return (block * CHARACTER_QUEUE_BUFFER_SIZE + tmp->len);
}

/*!
  \brief dump the queue to a string

  \param[in] str is a string that is at least size + 1 of the characters
  in the character queue, it is up to the caller to make sure this is the
  case
  \param[in] head a point to a character queue
  \retval the total number of characters copied
 */
int dumpCharQueueToStr(char *str, struct CHARACTER_QUEUE *head)
{
    char *ptr = NULL;
    struct CHARACTER_QUEUE *tmp = NULL;
    int total = 0;

    tmp = head;
    ptr = str;

    while (tmp != NULL)
    {
        /*Take it on faith that the len is 1.. CHARACTER_QUEUE_BUFFER_SIZE */
        memcpy(ptr, tmp->buffer, tmp->len);
        total += tmp->len;
        /*Advance Pointer */
        ptr += tmp->len;
        tmp = tmp->next;
    }

    return (total);
}

/*!
  \brief frees the character queue

  \param[in] head pointer to a pointer
  \return the number of nodes freed
 */
int freeCharacterQueue(struct CHARACTER_QUEUE **head)
{
    struct CHARACTER_QUEUE *tmp = NULL;
    int ret = 0;

    if (NULL == *head)
    {
        return (0);
    }

    tmp = *head;
    ret = 1 + freeCharacterQueue(&tmp->next);

    free(*head);

    *head = NULL;
    return (ret);
}

/*!
  \brief put a parsed token into the token queue

  \param[out] head pointer to a pointer this is the queue
  that is modified when tokens are pushed to it
  \param[in] token a charactwer string to save t othe Queue
  \return the number of token in the queue
 */
int enqueueToken(struct TOKEN_QUEUE **head, char *token)
{
    struct TOKEN_QUEUE *tmp = NULL;
    int block = 0;

    if (NULL == *head)
    {
        tmp = (struct TOKEN_QUEUE *)malloc(sizeof(struct TOKEN_QUEUE));
        memset((char *)tmp, '\0', sizeof(struct TOKEN_QUEUE));
        tmp->len = 0;
        tmp->next = NULL;
        *head = tmp;
    }

    tmp = *head;

    while (tmp->next != NULL)
    {
        tmp = tmp->next;
        block++;
    }

    if (tmp->len > (TOKEN_QUEUE_BUFFER_SIZE - 1))
    {
        /*we need a new block */
        tmp->next = (struct TOKEN_QUEUE *)malloc(sizeof(struct TOKEN_QUEUE));
        memset((char *)tmp->next, '\0', sizeof(struct TOKEN_QUEUE));
        tmp->next->len = 0;
        tmp->next->next = NULL;
        tmp = tmp->next;
        block++;
    }

    if (NULL != token && strlen(token) > 0)
    {
        tmp->token[tmp->len] =
                            (char *)malloc(sizeof(char) * (strlen(token) + 1));
        memset(tmp->token[tmp->len], '\0', strlen(token) + 1);
        memcpy(tmp->token[tmp->len], token, strlen(token));
    }
    else
    {
        /*0 Length String */
        tmp->token[tmp->len] = (char *)malloc(sizeof(char) * 1);
        tmp->token[tmp->len][0] = '\0';
    }

    /*increase Number of Tokens */
    tmp->len++;

    return (block * TOKEN_QUEUE_BUFFER_SIZE + tmp->len);
}

/*!
  \brief Get the Token at position i starting from 0
  
  \param[in] head pointer to the token Queue
  \param[in] tokenNumber starting from position 0 get this given 
  token number
  \retval NULL tokenNumber Less than 0, head is NULL, or tokenNumber 
  out of range
  \return a valid character pointer to a NULL Terminated String
*/
char *getTokenNumber(struct TOKEN_QUEUE *head, int tokenNumber)
{
    struct TOKEN_QUEUE *tmp = NULL;
    int counter = 0;

    if (tokenNumber < 0)
    {
        return (NULL);
    }

    if (NULL == head)
    {
        return (NULL);
    }

    tmp = head;

    while (NULL != tmp)
    {
        if (counter >= tmp->len)
        {
            counter = 0;
            tmp = tmp->next;
            continue;
        }

        if (tokenNumber < 1)
        {
	    return ((char *)tmp->token[counter]);
        }

        counter++;
        tokenNumber--;
    }

    return ((char *)NULL);
}

/*!
  \brief this routine will free a token queue

  \param[in] head pointer to a pointer of token queue, each
  time will be freed and set to NULL or Zero
  \return the number of tokens that were on the Queue
 */
int freeTokenQueue(struct TOKEN_QUEUE **head)
{
    struct TOKEN_QUEUE *tmp = NULL;
    int i;
    int ret = 0;

    if (NULL == *head)
    {
        return (0);
    }

    tmp = *head;
    ret = freeTokenQueue(&tmp->next);

    for (i = 0; i < tmp->len; i++)
    {
        if (NULL != tmp->token[i])
        {
            free(tmp->token[i]);
            tmp->token[i] = NULL;
            ret++;
        }
    }

    tmp->len = 0;
    tmp->next = NULL;

    free(*head);

    *head = NULL;
    return (ret);
}

/*!
  \brief This routine reads tokens from a file.

  Will parse tokens out of the file, Blank lines are ignored. If

  \param[in] fd an int file descriptor pointing to a file that we move 
  through and parse the tokens from 
  \param[out] tokenHead a pointer to a pointer that the tokens that are 
  parsed out are stored to. 
  \param[in] delimiter a char that says what the delimiter of the
  tokens are.
  \param[in] tokenLimit an int that says only take up to this many
  tokens from the file, if set to less than 1 then all tokens will
  be taken in.
  \param[out] lineNumber pointer to an integer, will be increased whenever
  a new line character is encountered.
  \param[in] newLineBreaks, if set to 1 we will return  from the routine
  when we encounter a new line character
  \retval -1 file not open
  \retval -99 EOF
  \retval >= 0 number of CSV tokens on line 
 */
int fillTokensFromFile(FILE_STATE *fs, struct TOKEN_QUEUE **tokenHead,
		       char delimiter, int tokenLimit,
		       int newLineBreaks,char quote)
{

    char *tokenBuff = NULL;
    struct CHARACTER_QUEUE *head = NULL;

    int numTokens = 0;

    int size = 0;
    int ret = 0;

    int inQuote = 0;
    int quoteDepth = 0;
    int numQuotes = 0;

    if (fs->fd < 1)
    {
        return (-1);
    }

    /*try to read */
    if (fs->readin < 1 || fs->sc >= fs->readin)
    {
        fs->readin = read(fs->fd, fs->readChar, sizeof(fs->readChar));
        fs->sc = 0;
    }

    /*EOF Test */
    if (fs->readin < 1)
    {
         /*EOF*/ return (-99);
    }

    for (;;)
    {

        if (fs->sc >= fs->readin)
        {
            fs->readin = read(fs->fd, fs->readChar, sizeof(fs->readChar));
            if (fs->readin < 1)
            {
                break;
            }
            fs->sc = 0;
        }

	if(quote && (quote == fs->readChar[fs->sc]))
	  {
	    
	    inQuote = (inQuote + 1) % 2;
	      
	    numQuotes++;
	    if(2 == numQuotes)
	      {
		/*Enqueue Quoted Quote*/
		if(quoteDepth > 0)
		  {
		    /*We Do not upcase quote chars normally*/
		    if(2 == UpcaseTokens)
		    {
			size = enqueueCharacter(&head, toupper(quote));
		    }
		    else
		    {
			/*Do Not Uppercase*/
			size = enqueueCharacter(&head, quote);
		    }
		    numQuotes = 0;
		  }
		else
		  {
		    /*Just in case a quote is next*/
		    numQuotes = 1;
		  }
	      }  

	    if(!inQuote)
	      {
		quoteDepth++;
	      }

	    fs->sc++;
	    continue;
	  }

	numQuotes = 0;

        if ('\n' == fs->readChar[fs->sc])
        {
            /*increase the line count */
            fs->lineNumber = (fs->lineNumber) + 1;
        }

        if (((!inQuote) && (delimiter == fs->readChar[fs->sc])) ||
            '\r' == fs->readChar[fs->sc] || '\n' == fs->readChar[fs->sc])
        {

	    /*Reset Quote Vars*/
	    inQuote = 0;
	    quoteDepth = 0;
	    numQuotes = 0;

            if (fs->newLine)
            {
                /*multiple new line characters */
                fs->sc++;
                continue;
            }

            if (size > 0)
            {
                /*Malloc tokenBuff +1 Copy Character Queue to Buffer */
                tokenBuff = (char *)malloc(sizeof(char) * (size + 1));
                memset(tokenBuff, '\0', size + 1);
                dumpCharQueueToStr(tokenBuff, head);
                enqueueToken(tokenHead, tokenBuff);
                /*Clear Character Queue */
                ret = freeCharacterQueue(&head);
                head = NULL;
                /*printf("TOKEN : %s\n", tokenBuff); */
            }
            else if (delimiter == fs->readChar[fs->sc])
            {
                enqueueToken(tokenHead, "\0");
            }

            if ('\r' == fs->readChar[fs->sc] || '\n' == fs->readChar[fs->sc])
            {
                /*if the token breaker was a new line character 
                   then we mark it so in case multiple new line characters */
                fs->newLine = 1;
            }

            /*Assign tokenBuff pointer to Node (enqueue) */

            size = 0;
            free(tokenBuff);
            tokenBuff = NULL;

            fs->sc++;
            size = 0;
            /*Up the Number of Tokens */
            numTokens++;
            if (tokenLimit > 0)
            {
                if (numTokens >= tokenLimit)
                {
                    return (numTokens);
                }
            }

	    if(newLineBreaks && fs->newLine)
	      {
		return (numTokens);
	      }

            continue;
        }

        /*Enqueue readChar[sc] */
	if(0 != UpcaseTokens)
	{
	    size = enqueueCharacter(&head, toupper(fs->readChar[fs->sc]));
	}
	else
	{
	    size = enqueueCharacter(&head, fs->readChar[fs->sc]);
	}
        fs->newLine = 0;
        fs->sc++;
    }

    if (size > 0)
    {

        /*Malloc tokenBuff +1 Copy Character Queue to Buffer */
        tokenBuff = (char *)malloc(sizeof(char) * (size + 1));
        memset(tokenBuff, '\0', size + 1);
        dumpCharQueueToStr(tokenBuff, head);
        enqueueToken(tokenHead, tokenBuff);
        /*Clear Character Queue */
        ret = freeCharacterQueue(&head);
        head = NULL;
        /*printf("(last) TOKEN : %s\n", tokenBuff); */

        /*printf("[%s]\n",lbuff); */
        free(tokenBuff);
        tokenBuff = NULL;
        numTokens++;
    }

    return (numTokens);
}


