#ifndef __MY_COMMON_CODE__
#define __MY_COMMON_CODE__

/* ###################################################################### */
/*             Raw Token Parsing and Handling Structures                  */
/* ###################################################################### */

#define CHARACTER_QUEUE_BUFFER_SIZE 50

/*Will Hold All Characters readin*/
struct CHARACTER_QUEUE
{
    char buffer[CHARACTER_QUEUE_BUFFER_SIZE];
    int len;
    struct CHARACTER_QUEUE *next;
};

#  define TOKEN_QUEUE_BUFFER_SIZE 20

struct TOKEN_QUEUE
{
    char *token[TOKEN_QUEUE_BUFFER_SIZE];
    int len;
    struct TOKEN_QUEUE *next;
};

struct FILE_STATE
{
  int fd;
  char readChar[512];
  int readin;
  int sc;
  int lineNumber;

  int newLine;
};

typedef struct FILE_STATE FILE_STATE;

/* *INDENT-OFF*
   ############################################################
   #           Library Prototype for Common Code              #
   ############################################################
   *INDENT-ON* */
#ifndef MY_COMMON_CODE_PROTO

int trimSpaceAndZeroFromEnd(char *s, int sz);
int trimSpaceAndZeroFromBeginToEnd(char *s, int sz);


int setCharField(char *fld, int size, char *src);



int enqueueCharacter(struct CHARACTER_QUEUE **head, char inChar);
int dumpCharQueueToStr(char *str, struct CHARACTER_QUEUE *head);
int freeCharacterQueue(struct CHARACTER_QUEUE **head);
int enqueueToken(struct TOKEN_QUEUE **head, char *token);
char *getTokenNumber(struct TOKEN_QUEUE *head, int tokenNumber);
int freeTokenQueue(struct TOKEN_QUEUE **head);
int fillTokensFromFile(FILE_STATE *fs, struct TOKEN_QUEUE **tokenHead,
		       char delimiter, int tokenLimit,
		       int newLineBreaks,char quote);


#endif
#endif
