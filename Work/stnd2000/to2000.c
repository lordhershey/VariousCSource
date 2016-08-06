#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_DN_HEADER                   8       /*!< LEN_DN for field definitions */
#define LEN_LAST_NAME                   30
#define LEN_FIRST_NAME                  16
#define LEN_PHONE_NBR                   16

#define LEN_ADDRESS                     30

#define EMAIL_ADDR_SIZE 160

#define LEN_CITY                        20
#define LEN_LOCALITY                    30
#define LEN_STATE_CODE                  4
#define LEN_POSTAL_CODE                 11
#define LEN_SSN                         16

struct L_CONV
{
    /*! Last name of responsible party. */
    char last_name[LEN_LAST_NAME];      /*0000 */
    /*! First name of responsible party. */
    char first_name[LEN_FIRST_NAME];    /*0030 */
    /*! Street address of responsible party. */
    char street_address[LEN_ADDRESS];   /*0046 */
    /*! Secondary address of responsible party. */
    char street_address2[LEN_ADDRESS];  /*0076 */
    /*! Tertiary address of responsible party. */
    char street_address3[LEN_ADDRESS];  /*0106 */
    /*! City where responsible party lives. */
    char city[LEN_CITY];        /*0136 */
    /*! Postal abbreviation for the state where responsible party resides. */
    char state[LEN_STATE_CODE]; /*0156 */
    /*! Standard five-digit or extended nine-digit (no hyphen) zip code. */
    char zip[LEN_POSTAL_CODE];  /*0160 */
    /*! Responsible party's social security number. */
    char soc_sec_no[LEN_SSN];   /*0171 */
    /*! Responsible party's home phone number. */
    char home_phone[LEN_PHONE_NBR];     /*0187 */
    /*! Responsible party's work/employer phone number. */
    char work_phone[LEN_PHONE_NBR];     /*0203 */
    /*! Responsible party's mobile phone number. */
    char mobile_phone[LEN_PHONE_NBR];   /*0219 */
    /*! Name of responsible party's employer. */
    char employer[20];          /*0235 */
    /*! Responsible party's date of birth. */
    char birthday[6];           /*0255 */
    /*! Responsible party's email address. */
    char email_address[EMAIL_ADDR_SIZE];        /*0261 */
    /*! User defined field indicating the account origin. The client code is
	 six characters in length plus an optional office code, and can
	 consist of numbers, letters, or a combination of both. */
    char client_code[7];        /*0421 */
    /*! Unique identifier assigned to the account by the original client. If
	 one is linking accounts (tying several detail records to a master)
	 they should be leary of linking on account number alone as many
	 clients may use the same numbers. */
    char account_no[20];        /*0428 */
    /*! Original amount referred for collection. */
    char original_balance[10];  /*0448 */
    /*! Outstanding principle amount currently due on the account. */
    char current_balance[10];   /*0458 */
    /*! Outstanding costs amount currently due on the account (which might
	 include legal fees and court costs. */
    char costs[10];             /*0468 */
    /*! Outstanding collection charges currently due on the account. */
    char collection_charge[10]; /*0478 */
    /*! Outstanding interest amount currently due on the account. */
    char interest_amount[10];   /*0488 */
    /*! Date of last charge on the account before the client turned it over
	 for collection (also referred to as "Date of Last Activity" or "Date
	 of Service"). Medical accounts will usually use this field for
	 "Discharge Date". */
    char date_of_last_charge[6];        /*0498 */
    /*! Date on which interest was last updated on the account. */
    char interest_post_date[6]; /*0504 */
    /*! Rate at which interest will be calculated on the account (e.g.18.5%
	 as 0001850). */
    char int_rate[6];           /*0510 */
    /*! Rate at which commission will be calculated. */
    char commission_rate[6];    /*0516 */
    /*! Additional information that can be used to describe the account
	 (e.g. patient name for medical account or credit card description). */
    char regarding[30];         /*0522 */
    /*! Name of responsible party's spouse. */
    char spouse_name[20];       /*0552 */
    /*! Flag used to indicate if the account is commercial. */
    char commercial_flag[1];    /*0572 */
    /*! This flag indicates if mail had been returned due to a bad address. */
    char mr_flag[1];            /*0573 */
    /*! Outstanding other amount currently due on the account. */
    char other_amt[10];         /*0574 */
    /*! Free-form text field that provides additional information relating to
	 the detail of the master. */
    char comments[6][30];       /*0584 */
    /*! Free-format text field that provides additional account information. */
    char notes[9][30];          /*0764 */
    /*! Last name of the co-maker. */
    char co_last_name[LEN_LAST_NAME];   /*1034 */
    /*! First name of the co-maker. */
    char co_first_name[LEN_FIRST_NAME]; /*1064 */
    /*! Co-maker's street address. */
    char co_address1[LEN_ADDRESS];      /*1080 */
    /*! Co-maker's secondary address. */
    char co_address2[LEN_ADDRESS];      /*1110 */
    /*! Co-maker's tertiary address. */
    char co_address3[LEN_ADDRESS];      /*1140 */
    /*! City where co-maker resides. */
    char co_city[LEN_CITY];     /*1170 */
    /*! Postal abbreviation for the state where co-maker resides. */
    char co_state[LEN_STATE_CODE];      /*1190 */
    /*! Standard five-digit or extended nine-digit (no-hyphen) zip code for
	 co-maker. */
    char co_zip[LEN_POSTAL_CODE];       /*1194 */
    /*! Co-maker's home phone. */
    char co_home_phone[LEN_PHONE_NBR];  /*1205 */
    /*! Co-maker's work/employer phone number. */
    char co_work_phone[LEN_PHONE_NBR];  /*1221 */
    /*! Co-maker's mobile phone number. */
    char co_mobile_phone[LEN_PHONE_NBR];        /*1237 */
    /*! Name of co-maker's employer. */
    char co_employer[20];       /*1253 */
    /*! Co-maker's social security number. */
    char co_soc_sec_no[LEN_SSN];        /*1273 */
    /*! Co-maker's date of birth. */
    char co_birthday[6];        /*1289 */
    /*! Flag used to indicate if the co-maker is commercial. */
    char co_commercial_flag[1]; /*1295 */
    /*! Co-maker's email address. */
    char co_email_address[EMAIL_ADDR_SIZE];     /*1296 */
    /*! Filler. */
    char filler[543];           /*1456 */
    /*! Line feed. */
    char newline;               /*1999 */
};                              /*2000 */

#define LN_NUM_TOKENS 300
#define LN_TOKEN_LEN 300

struct CSV_TOKENS{
    int sz;
    char tokens[LN_NUM_TOKENS][LN_TOKEN_LEN];
};


int clearTokensStruct(struct CSV_TOKENS *t)
{
	int i;
	
	if(NULL == t)
    {
		return (-1);
    }
	
	t->sz = 0;
	
	for(i = 0 ; i < LN_NUM_TOKENS ; i ++)
    {
		memset((char *)&t->tokens[i][0],'\0',LN_TOKEN_LEN);
    }
	
	return (0);
}


/*!
 \brief 
 
 \param[in] line
 \param[in] t
 \return the number of tokens on the line
 */
int fillTokensFromString(char *line,struct CSV_TOKENS *t){
	
    char lbuff[LN_TOKEN_LEN];
    int inToken = 0;
    int lc = 0;
    int sc = 0;
    int numTokens = 0;    
	
    if(NULL == t)
	{
		return (-1);
	}
    
    clearTokensStruct(t);
    
    inToken = 0;
    lc = 0;
    memset(lbuff,'\0',LN_TOKEN_LEN);
    for(sc = 0 ; sc < strlen(line) ; sc++)
	{
		if(!inToken && ',' == line[sc])
		{
			/*save & clear the token*/
			if(t->sz < LN_NUM_TOKENS)
			{
				memcpy(t->tokens[t->sz],lbuff,LN_TOKEN_LEN);
				t->sz++;
			}
			/*printf("[%s]\n",lbuff);*/
			lc = 0;
			memset(lbuff,'\0',LN_TOKEN_LEN);
			numTokens++;
			continue;
		}
		
		if('\"' == line[sc])
		{
			if(!inToken)
			{
				/*double quote*/
				inToken = 1; 
				if(lc > 0)
				{
					if(lc < LN_TOKEN_LEN)
					{
						lbuff[lc] = '\"';
						lc++;
					}
				}
			}
			else
			{
				inToken = 0;
			}	   
			
			continue; 	    
		}
		
		if('\r' == line[sc] || '\n' == line[sc])
		{
			continue;
		}
		
		if(lc < (LN_TOKEN_LEN - 1))
		{
			lbuff[lc] = line[sc];
			lc++;
		}
	} 
    
    if(lc > 0)
	{
		/*if we have a token chunk*/
		if(t->sz < LN_NUM_TOKENS)
		{
			memcpy(t->tokens[t->sz],lbuff,LN_TOKEN_LEN);
			t->sz++;
		}
		/*printf("[%s]\n",lbuff);*/
		lc = 0;
		memset(lbuff,'\0',LN_TOKEN_LEN);
		numTokens++;
	}
    
    return(numTokens);
}

struct ACCOUNT{
  char first_name[LEN_FIRST_NAME + 1];
  char last_name[LEN_LAST_NAME + 1];
  char account_no [21];
  char client_no[8];
};

int main (int argc, char *argv[])
{
  FILE *f = NULL;
  char buffer[3000];
  int ret;
  struct CSV_TOKENS tok;
  int i;
  struct L_CONV out2000;
  struct ACCOUNT curr,hold;
  char sPlac[11];
  char ssn[10];

  int lineNo = 0;
  /*Fake SSN*/
  int SSN = 229109332;
  /*Fake Placement Amount*/
  int PLACEMENT = 1000;
  
  f=fopen("Placement.csv","r");
  
  
  if (NULL == f)
    {
      fprintf(stderr,"Flibity Gibit, Cannot Open %s\n","Placement.csv");
      exit(-1);
    }

  memset((char *)&hold,'\0',sizeof(hold));  
  memset(buffer,'\0',sizeof(buffer));
  while(fgets(buffer,sizeof(buffer),f) != NULL)
    {
      lineNo++;
      ret = fillTokensFromString(buffer,&tok);

      /*
      for (i = 0 ; i < ret; i++)
	{
	  printf("[%s] ",tok.tokens[i]);
	}
      */

      snprintf(curr.first_name,(LEN_FIRST_NAME + 1),
	       "%-*.*s                                ",
	       (LEN_FIRST_NAME + 1),(LEN_FIRST_NAME + 1),tok.tokens[0]);
      snprintf(curr.last_name,(LEN_LAST_NAME + 1),
	       "%-*.*s                                ",
	       (LEN_LAST_NAME + 1),(LEN_LAST_NAME + 1),tok.tokens[1]);
      snprintf(curr.account_no,(21),
	       "%-*.*s                                ",
	       (21),(21),tok.tokens[2]);
      snprintf(curr.client_no,(8),
	       "%-*.*s                                ",
	       (8),(8),tok.tokens[3]);
      
      if (memcmp((char *)&curr,(char *)&hold,sizeof(hold)) != 0)
	{
	  /*up the SSN and Placement AMount*/
	  SSN += lineNo;
	  PLACEMENT += lineNo;
	}

      snprintf(sPlac,11,"%10d          ",PLACEMENT);
      snprintf(ssn,10  ,"%d          ",SSN);
   
      memset((char *)&out2000,' ',sizeof(out2000));
      memcpy(out2000.first_name,curr.first_name,LEN_FIRST_NAME);
      memcpy(out2000.last_name,curr.last_name,LEN_LAST_NAME);
      memcpy(out2000.account_no,curr.account_no,20);
      memcpy(out2000.client_code,curr.client_no,7);
      memcpy(out2000.original_balance,sPlac,10);
      memcpy(out2000.current_balance,sPlac,10);
      memcpy(out2000.soc_sec_no,ssn,9);
      out2000.newline = '\n';

      write(1,(char *)&out2000,sizeof(out2000));
      /*printf("\n");*/
      memset(buffer,'\0',sizeof(buffer));
    }
}
