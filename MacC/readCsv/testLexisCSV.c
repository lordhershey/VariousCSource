#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LN_NUM_TOKENS 300
#define LN_TOKEN_LEN 300

struct CSV_TOKENS{
    int sz;
    char tokens[LN_NUM_TOKENS][LN_TOKEN_LEN];
};

struct LN_PHONE_1 {
    /*! Phone Numbers can come from debtor home, work, mobile,
      phone database, or transaction scan*/
    char number[10];
};

struct LN_DEDUP_ADDR{
    /*! Tran scan Address 1*/
    char address1[50];
    /*! Tran scan Address 2*/
    char address2[50];
    /*! Tran scan City*/
    char city[50];
    /*! Tran Scan State*/
    char state[50];
    /*! Tran Scan Zip*/
    char zip[50];
};

struct LN_SUBJ_ADDR {
    char address[50];
    char city[28];
    char state[2];
    char zipCode[10];
    char lastSeenDateNCOAMoveDate[8];
    char cassDPVFlagNCOA[1]; /*from old CSV 8 new 1*/
};

struct LN_SUBJ_PHONE {
    char phone[10];
    char phoneName[65];
    char phoneType[2];
    char phoneTypeSwitchType[4];
};

struct LN_ADDR_PHONE {
    char firstName[20];
    char lastName[20];
    char address[50];
    char city[28];
    char state[2];
    char zipCode[10];
    char phone[10];
};

struct LN_PROPERTY {
    char parcel[45];
    char ownerName[80]; /*in new CSV owner 2 is 62 chars*/
    char coOwnerName[80];
    char address[50];
    char city[28];
    char state[2];
    char zip[10];
    char saleDate[8];
    char salePrice[11];
    char totalValue[11];
    char typeFinancing[4];
    char loanTermMonths[5];
    char foreclosure[1];
    char refiFlag[1];
    char equityFlag[1];
    char assessmentMatchLandUseCode[4];
    char useCode[3];
    char type[1];
};

struct LN_MOTOR_VEHICLE {
    char vehicleDesc[120];
    char lienholderName[66];
    char tag[10];
    char vin[25];
    char ownerName1[65];
    char ownerName2[65];
    char registrantName1[65];
    char registrantName2[65];
};

struct LN_PEOPLE_AT_WORK {
    char count[3];
    char company[120];
    char address[50];
    char city[28];
    char state[2];
    char zip[10];
    char phone[10];
    char date[8];
    char confCode[1];
};

struct LN_JUDGMENT_LIEN {
    char totalHitCount[10];
    char debtorName[32];
    char filingType[50];
    char amount[12];
    char filingDate[8];
    char creditor[32];
    char caseNumber[17];
};

/*! These fields could be expanded or resized since they are
  written out on a CSV file.
 */
struct LEXIS_NEXIS_REQ{
    /*! CRS user reference number used to uniquely identify the 
      debtor record.*/
    char customerAccountNumber[20];
    /*! Not Used */
    char uniqueNumber[20];
    /*! The CRS first name sometimes has the middle initial 
      appended to it. The middle initial will be removed 
      and added to the middle name field below.*/
    char firstName[30];
    /*! CRS does not use the middle name. If the middle initial 
      has been appended to the first name, it will be removed 
      and added here.*/
    char middleName[30];
    /*! If the suffix (JR, SR, I, II, III) exists on the CRS 
      last name field, it will added to the Suffix field. 
      The CRS last name without the suffix will be added 
      to the Last_Name field.*/
    char lastName[30];
    /*! If the suffix exists in the CRS last name field it 
      will be added here.*/
    char suffix[5];
    /*! SSN will be obtained from CRS in a similar manner as 
      the other skiptrace modules do - by checking the
      defaults of how the field is used, if not for SSN then
      we search the aux page for first SSN field, if not there 
      then it will be blank. */
    char ssnTaxIDNumber[11];
    /*! Master Record Address 1 */
    char address1[50];
    /*! Master Record Address 2 */
    char address2[50];
    /*! Master Record City */
    char city[28];
    /*! Master Record State*/
    char state[2];
    /*! Master Record Zip*/
    char zip[10];

    struct LN_PHONE_1 phone[5];

    /*! The Date_of_Birth field will be populated from the CRS 
      database. */
    char dateOfBirth[8];
    /*! The user has the option to populate the Account_Open_Date 
      field with the CRS " Recd" date field plus or minus a date 
      offset.*/
    char accountOpenDate[8];
  
    /*! Driver's License Number - AUX 1. Not any Field labeled
      AUX 1 means if it is exists in the AUX page then it can be 
      retrieved but the field must fit and be a text field*/
    char driversLicense[17];
    /*! Driver's License State - AUX 1 */
    char driversLicenseState[2];
    /*! Motor Vehicle Plate Number - AUX 1 */
    char motorVehiclePlateNumber[9];
    /*! Motor Vehicle Plate State - AUX 1*/
    char motorVehiclePlateState[2];

    /*! The Debt_Type will be populated based on a module default. 
      01 = Retail,02 = Medical,03 = Utilities/Wireless,04 = Other */
    char debtType[2]; 
    /*! The user has the option to populate the Original Charge 
      Off Date field with the CRS "Date Lst" field plus or minus 
      a date offset.*/
    char originalChargeOffDate[8];
    /*! The user has the option to populate the Last Payment 
      Date field with CRS payment information.*/
    char lastPaymentDate[8];
    /*! The user has the option to populate the Charge Off 
      Balance the sum of the CRS "Orig" amount. All amount
      fields here rounded to nearest dollar - no charts used
      for Cents*/
    char chargeOffBalance[6];
    /*! The Current Balance will be populated with the sum of the 
      CRS "Tot Bal" amounts.*/
    char currentBalance[6];
    /*! The user has the option to populate the Client Defined Score 
      with the behavior score, a score from the CRS AUX 1 Page, or
      nothing*/
    char clientDefinedScore[3];
  
    /*! The Service_Request will be populated based on the individual 
      module default settings. Selected services are listed one after
      the other with no separator*/
    char serviceRequest[20];

    /*! 01 - add, 02 - delete, 03 - Monitor (03 must exist in own file */
    char recordType[2];
  
    struct LN_DEDUP_ADDR dedupAddress[5];
};

/*! 
  These data members could be expanded if needed since they come
  in on a csv line it is not a raw record write
 */
struct LEXIS_NEXIS_BOOK{
    char customerAccountNumber[20];
    char uniqueNumber[20];
    char recordType[2];
    char adlNumber[20];
    char clientDefinedScore[3];

    char returnedProcess[20];

  /*These fields taken out of LN_SUBJ_ADDR*/
    char first[20];
    char middle[20];
    char last[20];
    char suffix[5];
    char bestSSN[9];
    char dob[8];

    struct LN_SUBJ_ADDR subjAddress[5];

    struct LN_SUBJ_PHONE subjPhone[5];

    char bkCaseNumber[12];
    char bkChapterCode[2];
    char bkFileDate[8];
    char bkStatusdate[8];
    char bkReinstatedDate[8];
    char bkClosedDate[8];
    char bkDisp[2];
    char bkMatchCode[10];

    char dcdReported[1];
    char dcdSubjFirst[20];
    char dcdSubjLast[20];
    char dcdSubjDOB[8];
    char dcdSubjDOD[8];
    char dcdZipGvtBenefit[5];
    char dcdZipDeathBenefit[5];

    char flagAddressVerified[1];
    char flagPhoneVerified[1];
    char flagProperty[2];
    char flagAddressIncomeEst[1];

    char flagPossibleLitigiousDebtor[1]; /* was reserved in old CSV */
    char flagMVR[2]; /*was 1 from before */
    char flagRelatives[1];
    char flagAssociates[1];
    char flagPeopleAtWork[1];
    char flagIGTLien[1];

    char reserved_1[2];

    char lnCustomScore[3];
    char hostedSolutionTacticsCodes[20];
    char stabilityIndexScore[3]; /*was liquidityScore*/
    char contactabilityScore[3];
    char recoverScoreNonFCRA[3];

    struct LN_ADDR_PHONE rel[3];

    struct LN_ADDR_PHONE assoc[3];

    struct LN_ADDR_PHONE nearby[3];

    struct LN_PROPERTY prop[2];

    struct LN_MOTOR_VEHICLE mvr[3];

    struct LN_PEOPLE_AT_WORK paw;

    struct LN_JUDGMENT_LIEN jl;

};


int trimSpaceAndZeroFromEnd(char *s, int sz);
int trimSpaceAndZeroFromBeginToEnd(char *s, int sz);
void serializeLexisNexisRequest(FILE *f,
			       struct LEXIS_NEXIS_REQ *req);
char *csvStr(char *cb,int cbsz);

int fillBookingStructure(struct LEXIS_NEXIS_BOOK *books,
			  struct CSV_TOKENS *tok,
			  int *expected,
		      int *overflow);
int takeField(char *target, 
	      int sz,
	      struct CSV_TOKENS *tok,
	      int ind,
	      int *count);

struct LEXIS_NEXIS_REQ in;
struct LEXIS_NEXIS_BOOK out;
struct CSV_TOKENS csvt;

char *csvCol(int i);

int main (int argc,char *argv[])
{
    FILE *f = NULL;
    char buffer[6000];
    int ret;
    int lineno = 0;
    int i;
    
    int expected = 0;
    int overflow = 0;

    memset((char *)&in,'0',sizeof(in));
    
    printf("Input Output CSV Parse Test\n");
    
    serializeLexisNexisRequest(stdout,&in);
    
    f = fopen("in.csv","r");
    
    printf("Size of Input  : %d\n",sizeof(struct LEXIS_NEXIS_REQ));
    printf("Size of Output : %d\n",sizeof(struct LEXIS_NEXIS_BOOK));
    printf("Size of        : %d\n",sizeof(struct LN_SUBJ_ADDR) * 5);
    printf("Size of        : %d\n",sizeof(struct LN_SUBJ_PHONE) * 5);
    printf("Size of        : %d\n",sizeof(struct LN_ADDR_PHONE) * 3);
    printf("Size of        : %d\n",sizeof(struct LN_ADDR_PHONE) * 3);
    printf("Size of        : %d\n",sizeof(struct LN_ADDR_PHONE) * 3);
    printf("Size of        : %d\n",sizeof(struct LN_PROPERTY) * 2);
    printf("Size of        : %d\n",sizeof(struct LN_MOTOR_VEHICLE) * 3);
    printf("Size of        : %d\n",sizeof(struct LN_PEOPLE_AT_WORK));
    printf("Size of        : %d\n",sizeof(struct LN_JUDGMENT_LIEN));
    
    while(NULL != f && fgets(buffer,6000,f) != NULL)
      {
	ret = fillTokensFromString(buffer,&csvt);
	for(i = 0; i < csvt.sz ; i++)
	  {
	    printf("%2s %s\n",csvCol(i),csvt.tokens[i]);
	  }
	printf("LINE NO %5d, Tokens %3d ===========================\n",
	       lineno++,ret);
	
	memset((char *)&out,'\0',
	       sizeof(struct LEXIS_NEXIS_BOOK));

	expected = 0;
	overflow = 0;

	fillBookingStructure(&out,&csvt,&expected,&overflow);
      }
    
    if(NULL != f)
      {
	fclose(f);
	f = NULL;
      }
    
    exit(0);
    return (0);
}

/*!
  \brief serialize the Lexis Nexis request
 */
void serializeLexisNexisRequest(FILE *f,
			       struct LEXIS_NEXIS_REQ *req)
{
    int i;

    fprintf(f,"%s,",csvStr(req->customerAccountNumber,
			   sizeof(req->customerAccountNumber)));
    fprintf(f,"%s,",csvStr(req->uniqueNumber,
			   sizeof(req->uniqueNumber)));
    fprintf(f,"%s,",csvStr(req->firstName,
			   sizeof(req->firstName)));
    fprintf(f,"%s,",csvStr(req->middleName,
			   sizeof(req->middleName)));
    fprintf(f,"%s,",csvStr(req->lastName,
			   sizeof(req->lastName)));
    fprintf(f,"%s,",csvStr(req->suffix,
			   sizeof(req->suffix)));
    fprintf(f,"%s,",csvStr(req->ssnTaxIDNumber,
			   sizeof(req->ssnTaxIDNumber)));
    fprintf(f,"%s,",csvStr(req->address1,
			   sizeof(req->address1)));
    fprintf(f,"%s,",csvStr(req->address2,
			   sizeof(req->address2)));
    fprintf(f,"%s,",csvStr(req->city,
			   sizeof(req->city)));
    fprintf(f,"%s,",csvStr(req->state,
			   sizeof(req->state)));
    fprintf(f,"%s,",csvStr(req->zip,
			   sizeof(req->zip)));

    for(i = 0 ; i < 5 ; i++)
    {
	fprintf(f,"%s,",csvStr(req->phone[i].number,
			       sizeof(req->phone[i].number)));
    }

   
    fprintf(f,"%s,",csvStr(req->dateOfBirth,
			   sizeof(req->dateOfBirth)));
    fprintf(f,"%s,",csvStr(req->accountOpenDate,
			   sizeof(req->accountOpenDate)));
    fprintf(f,"%s,",csvStr(req->driversLicense,
			   sizeof(req->driversLicense)));
    fprintf(f,"%s,",csvStr(req->driversLicenseState,
			   sizeof(req->driversLicenseState)));
    fprintf(f,"%s,",csvStr(req->motorVehiclePlateNumber,
			   sizeof(req->motorVehiclePlateNumber)));
    fprintf(f,"%s,",csvStr(req->motorVehiclePlateState,
			   sizeof(req->motorVehiclePlateState)));
    fprintf(f,"%s,",csvStr(req->debtType,
			   sizeof(req->debtType)));
    fprintf(f,"%s,",csvStr(req->originalChargeOffDate,
			   sizeof(req->originalChargeOffDate)));
    fprintf(f,"%s,",csvStr(req->lastPaymentDate,
			   sizeof(req->lastPaymentDate)));
    fprintf(f,"%s,",csvStr(req->chargeOffBalance,
			   sizeof(req->chargeOffBalance)));
    fprintf(f,"%s,",csvStr(req->currentBalance,
			   sizeof(req->currentBalance)));
    fprintf(f,"%s,",csvStr(req->clientDefinedScore,
			   sizeof(req->clientDefinedScore)));
    fprintf(f,"%s,",csvStr(req->serviceRequest,
			   sizeof(req->serviceRequest)));

    for(i = 0 ; i < 4 ; i++)
    {
	fprintf(f,"%s,",csvStr(req->dedupAddress[i].address1,
			       sizeof(req->dedupAddress[i].address1)));
	fprintf(f,"%s,",csvStr(req->dedupAddress[i].address2,
			       sizeof(req->dedupAddress[i].address2)));    
	fprintf(f,"%s,",csvStr(req->dedupAddress[i].city,
			       sizeof(req->dedupAddress[i].city)));
	fprintf(f,"%s,",csvStr(req->dedupAddress[i].state,
			       sizeof(req->dedupAddress[i].state)));
	fprintf(f,"%s,",csvStr(req->dedupAddress[i].zip,
			       sizeof(req->dedupAddress[i].zip)));
    }

    /*Unroll the l;ast loop interation*/
    fprintf(f,"%s,",csvStr(req->dedupAddress[i].address1,
			   sizeof(req->dedupAddress[i].address1)));
    fprintf(f,"%s,",csvStr(req->dedupAddress[i].address2,
			       sizeof(req->dedupAddress[i].address2)));    
    fprintf(f,"%s,",csvStr(req->dedupAddress[i].city,
			   sizeof(req->dedupAddress[i].city)));
    fprintf(f,"%s,",csvStr(req->dedupAddress[i].state,
			   sizeof(req->dedupAddress[i].state)));
    fprintf(f,"%s\n",csvStr(req->dedupAddress[i].zip,
			   sizeof(req->dedupAddress[i].zip)));
    
}

char *csvCol(int i)
{

    static char buffer[3];
    buffer [2] = '\0';

    if(0 == (int)(i / 26))
      {
	buffer[0] = ' ';
      }
    else
      {
	buffer[0] = 'A' + (i / 26) - 1;
      }
    buffer[1] = 'A' + (i % 26); 
    return (buffer);
}

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
    int i,j;

    if (NULL == s || sz < 1)
    {
        return (-1);
    }

    /*cut off white space on front*/
    for (i = 0 ; i < (sz - 1) && 
	   ('\0' == s[0] || 
	    ' ' == s[0] || 
	    '\n' == s[0] || 
	    '\r' == s[0] || 
	    '\t' == s[0]); 
	 i++)
    {  
        for(j = 1 ; j < sz ; j++)
	{
	    s[(j - 1)] = s[j];
	    s[j] = ' ';
	}
    }
    return (trimSpaceAndZeroFromEnd(s,sz));
}

/*!
  \brief print out a string in proper csv
 */
char *csvStr(char *cb,int cbsz)
{
    static char lbuf[400];
    static char lbuff2[600];
    static char retBuff [10][600];
    static int buffNum = 0;
    int i,j;
    
    buffNum++;
    buffNum = buffNum % 10;
    
    memset(lbuf,'\0',sizeof(lbuf));
    snprintf(lbuf,sizeof(lbuf),"%.*s",cbsz,cb);
    
    trimSpaceAndZeroFromBeginToEnd(lbuf,strlen(lbuf));
    
    memset((char *)&retBuff[buffNum][0],'\0',600);
    
    if(strlen(lbuf) < 1)
    {
	snprintf(&retBuff[buffNum][0],600,"\"\"");
	return (&retBuff[buffNum][0]);
    }
    
    memset((char *)&lbuff2,'\0',600);
    
    for(i = 0 , j = 0 ; i < strlen(lbuf) ; i++)
    {
	if('\"' == lbuf[i])
	{
	    lbuff2[j] = '\"';
	    j++;
	}
	
	lbuff2[j] = lbuf[i];
	j++;
    }
    
    snprintf(&retBuff[buffNum][0],600,"\"%s\"",lbuff2);
    
    return (&retBuff[buffNum][0]);
}

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


/*!
  \brief take a field and stick it in the target

  \param[in] target the target buffer to put the toekn into
  \param[in] sz the size of the target
  \param[in] tok the toekn array we have
  \param[in] ind the index of the tokens we are trying to get
  \param[out] count a counter we can incrememnt if we get a positive
  result

  \retval 0 successfully got the token
  \retval -1 cannot take that token
*/
int takeField(char *target, 
	      int sz,
	      struct CSV_TOKENS *tok,
	      int ind,
	      int *count)
{

    int theSize = 0;
    char lbuffer[LN_TOKEN_LEN + 1];

    memset(lbuffer,'\0',sizeof(lbuffer));

    /*Impossible to take a token in these circumstances*/
    if(NULL == tok || 
       ind < 0 || 
       ind >= tok->sz ||
       NULL == target ||
       sz < 1)
      {
	return (-1);
      }

    theSize = sz;
    snprintf(lbuffer,sizeof(lbuffer),"%.*s",
	     LN_TOKEN_LEN,
	     tok->tokens[ind]);
    
    if(theSize > strlen(lbuffer))
      {
	theSize = strlen(lbuffer);
      }

    memcpy(target,lbuffer,theSize);

    if(NULL != count)
      {
	*count = *count + 1;
      }

    return (0);
}

/*!
  \brief fill up the Booking Structure

  \param[out] books the result struture we are tying
  to fill with the booking result
  \param[in] tok the tokens struture
  \param[in] expected pointer to int of number of expected tokens
  \param[in] overflow pointer to an int - set to one if more tokens 
  exist on the line

  \retval >= 0 the number of tokens in structure
  \retval -1 books or tok null
 */
int  fillBookingStructure(struct LEXIS_NEXIS_BOOK *books,
			  struct CSV_TOKENS *tok,
			  int *expected,
			  int *overflow)
{
    int count = 0;
    int ind = 0;    
    int ret = 0;
    int i;

    int ret2;
    char lbuf[100];

    if(NULL == books || NULL == tok)
      {
	return (-1);
      }
    
    ret = takeField(books->customerAccountNumber, 
		    sizeof(books->customerAccountNumber),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->uniqueNumber, 
		    sizeof(books->uniqueNumber),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->recordType, 
		    sizeof(books->recordType),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->adlNumber, 
		    sizeof(books->adlNumber),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->clientDefinedScore, 
		    sizeof(books->clientDefinedScore),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->returnedProcess, 
		    sizeof(books->returnedProcess),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->first, 
		    sizeof(books->first),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->middle, 
		    sizeof(books->middle),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->last, 
		    sizeof(books->last),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->suffix, 
		    sizeof(books->suffix),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->bestSSN, 
		    sizeof(books->bestSSN),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->dob, 
		    sizeof(books->dob),
		    tok,
		    ind++,
		    &count);
    
    for(i = 0; i < 5; i++)
      {
	ret = takeField(books->subjAddress[i].address, 
			sizeof(books->subjAddress[i].address),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->subjAddress[i].city, 
			sizeof(books->subjAddress[i].city),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->subjAddress[i].state, 
			sizeof(books->subjAddress[i].state),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->subjAddress[i].zipCode, 
			sizeof(books->subjAddress[i].zipCode),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->subjAddress[i].lastSeenDateNCOAMoveDate, 
			sizeof(books->subjAddress[i].lastSeenDateNCOAMoveDate),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->subjAddress[i].cassDPVFlagNCOA, 
			sizeof(books->subjAddress[i].cassDPVFlagNCOA),
			tok,
			ind++,
			&count);
	
      }
    
    for(i = 0 ; i < 5 ; i++)
      {
	ret = takeField(books->subjPhone[i].phone, 
			sizeof(books->subjPhone[i].phone),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->subjPhone[i].phoneName, 
			sizeof(books->subjPhone[i].phoneName),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->subjPhone[i].phoneType, 
			sizeof(books->subjPhone[i].phoneType),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->subjPhone[i].phoneTypeSwitchType, 
			sizeof(books->subjPhone[i].phoneTypeSwitchType),
			tok,
			ind++,
			&count);
      }
    
    ret = takeField(books->bkCaseNumber, 
		    sizeof(books->bkCaseNumber),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->bkChapterCode, 
		    sizeof(books->bkChapterCode),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->bkFileDate, 
		    sizeof(books->bkFileDate),
		    tok,
		    ind++,
		    &count);

    ret = takeField(books->bkStatusdate, 
		    sizeof(books->bkStatusdate),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->bkReinstatedDate, 
		    sizeof(books->bkReinstatedDate),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->bkClosedDate, 
		    sizeof(books->bkClosedDate),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->bkDisp, 
		    sizeof(books->bkDisp),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->bkMatchCode, 
		    sizeof(books->bkMatchCode),
		    tok,
		    ind++,
		    &count);

    ret = takeField(books->dcdReported, 
		    sizeof(books->dcdReported),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->dcdSubjFirst, 
		    sizeof(books->dcdSubjFirst),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->dcdSubjLast, 
		    sizeof(books->dcdSubjLast),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->dcdSubjDOB, 
		    sizeof(books->dcdSubjDOB),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->dcdSubjDOD, 
		    sizeof(books->dcdSubjDOD),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->dcdZipGvtBenefit, 
		    sizeof(books->dcdZipGvtBenefit),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->dcdZipDeathBenefit, 
		    sizeof(books->dcdZipDeathBenefit),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->flagAddressVerified, 
		    sizeof(books->flagAddressVerified),
		    tok,
		    ind++,
		    &count);

    ret = takeField(books->flagPhoneVerified, 
		    sizeof(books->flagPhoneVerified),
		    tok,
		    ind++,
		    &count);

    ret = takeField(books->flagProperty, 
		    sizeof(books->flagProperty),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->flagAddressIncomeEst, 
		    sizeof(books->flagAddressIncomeEst),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->flagPossibleLitigiousDebtor, 
		    sizeof(books->flagPossibleLitigiousDebtor),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->flagMVR, 
		    sizeof(books->flagMVR),
		    tok,
		    ind++,
		    &count);

    ret = takeField(books->flagRelatives, 
		    sizeof(books->flagRelatives),
		    tok,
		    ind++,
		    &count);

    ret = takeField(books->flagAssociates, 
		    sizeof(books->flagAssociates),
		    tok,
		    ind++,
		    &count);

    ret = takeField(books->flagPeopleAtWork, 
		    sizeof(books->flagPeopleAtWork),
		    tok,
		    ind++,
		    &count);

    ret = takeField(books->flagIGTLien, 
		    sizeof(books->flagIGTLien),
		    tok,
		    ind++,
		    &count);

    /*RESERVED FLAG*/
    ret = takeField(books->reserved_1, 
		    sizeof(books->reserved_1),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->lnCustomScore, 
		    sizeof(books->lnCustomScore),
		    tok,
		    ind++,
		    &count);

    ret = takeField(books->hostedSolutionTacticsCodes, 
		    sizeof(books->hostedSolutionTacticsCodes),
		    tok,
		    ind++,
		    &count);

    ret = takeField(books->stabilityIndexScore, 
		    sizeof(books->stabilityIndexScore),
		    tok,
		    ind++,
		    &count);

    ret = takeField(books->contactabilityScore, 
		    sizeof(books->contactabilityScore),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->recoverScoreNonFCRA, 
		    sizeof(books->recoverScoreNonFCRA),
		    tok,
		    ind++,
		    &count);

    /*Relatives Phone and Address*/
    for(i = 0; i < 3 ; i++)
      {
	ret = takeField(books->rel[i].firstName, 
			sizeof(books->rel[i].firstName),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->rel[i].lastName, 
			sizeof(books->rel[i].lastName),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->rel[i].address, 
			sizeof(books->rel[i].address),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->rel[i].city, 
			sizeof(books->rel[i].city),
			tok,
			ind++,
			&count);

	ret = takeField(books->rel[i].state, 
			sizeof(books->rel[i].state),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->rel[i].zipCode, 
			sizeof(books->rel[i].zipCode),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->rel[i].phone, 
			sizeof(books->rel[i].phone),
			tok,
			ind++,
			&count);
      }
    
    /*associates Phone and Address*/
    for(i = 0; i < 3 ; i++)
      {
	ret = takeField(books->assoc[i].firstName, 
			sizeof(books->assoc[i].firstName),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->assoc[i].lastName, 
			sizeof(books->assoc[i].lastName),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->assoc[i].address, 
			sizeof(books->assoc[i].address),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->assoc[i].city, 
			sizeof(books->assoc[i].city),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->assoc[i].state, 
			sizeof(books->assoc[i].state),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->assoc[i].zipCode, 
			sizeof(books->assoc[i].zipCode),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->assoc[i].phone, 
			sizeof(books->assoc[i].phone),
			tok,
			ind++,
			&count);
      }
    
    /*Nearby Phone And  Addresses*/
    for(i = 0; i < 3 ; i++)
      {
	ret = takeField(books->nearby[i].firstName, 
			sizeof(books->nearby[i].firstName),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->nearby[i].lastName, 
			sizeof(books->nearby[i].lastName),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->nearby[i].address, 
			sizeof(books->nearby[i].address),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->nearby[i].city, 
			sizeof(books->nearby[i].city),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->nearby[i].state, 
			sizeof(books->nearby[i].state),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->nearby[i].zipCode, 
			sizeof(books->nearby[i].zipCode),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->nearby[i].phone, 
			sizeof(books->nearby[i].phone),
			tok,
			ind++,
			&count);
      }
    
    /*Properties*/
    for(i = 0 ; i < 2 ; i++)
      {
	ret = takeField(books->prop[i].parcel, 
			sizeof(books->prop[i].parcel),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->prop[i].ownerName, 
			sizeof(books->prop[i].ownerName),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->prop[i].coOwnerName, 
			sizeof(books->prop[i].coOwnerName),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->prop[i].address, 
			sizeof(books->prop[i].address),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->prop[i].city, 
			sizeof(books->prop[i].city),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->prop[i].state, 
			sizeof(books->prop[i].state),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->prop[i].zip, 
			sizeof(books->prop[i].zip),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->prop[i].saleDate, 
			sizeof(books->prop[i].saleDate),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->prop[i].salePrice, 
			sizeof(books->prop[i].salePrice),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->prop[i].totalValue, 
			sizeof(books->prop[i].totalValue),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->prop[i].typeFinancing, 
			sizeof(books->prop[i].typeFinancing),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->prop[i].loanTermMonths, 
			sizeof(books->prop[i].loanTermMonths),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->prop[i].foreclosure, 
			sizeof(books->prop[i].foreclosure),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->prop[i].refiFlag, 
			sizeof(books->prop[i].refiFlag),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->prop[i].equityFlag, 
			sizeof(books->prop[i].equityFlag),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->prop[i].assessmentMatchLandUseCode, 
			sizeof(books->prop[i].assessmentMatchLandUseCode),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->prop[i].useCode, 
			sizeof(books->prop[i].useCode),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->prop[i].type, 
			sizeof(books->prop[i].type),
			tok,
			ind++,
			&count);
      }

    /*Motor Vehicles*/
    for(i = 0 ; i < 3 ; i++)
      {
	ret = takeField(books->mvr[i].vehicleDesc, 
			sizeof(books->mvr[i].vehicleDesc),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->mvr[i].lienholderName, 
			sizeof(books->mvr[i].lienholderName),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->mvr[i].tag, 
			sizeof(books->mvr[i].tag),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->mvr[i].vin, 
			sizeof(books->mvr[i].vin),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->mvr[i].ownerName1, 
			sizeof(books->mvr[i].ownerName1),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->mvr[i].ownerName2, 
			sizeof(books->mvr[i].ownerName2),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->mvr[i].registrantName1, 
			sizeof(books->mvr[i].registrantName1),
			tok,
			ind++,
			&count);
	
	ret = takeField(books->mvr[i].registrantName2, 
			sizeof(books->mvr[i].registrantName2),
			tok,
			ind++,
			&count);
      }
    
    /*People at Work*/
    ret = takeField(books->paw.count, 
		    sizeof(books->paw.count),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->paw.company, 
		    sizeof(books->paw.company),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->paw.address, 
		    sizeof(books->paw.address),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->paw.city, 
		    sizeof(books->paw.city),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->paw.state, 
		    sizeof(books->paw.state),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->paw.zip, 
		    sizeof(books->paw.zip),
		    tok,
		    ind++,
		    &count);

    ret = takeField(books->paw.phone, 
		    sizeof(books->paw.phone),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->paw.date, 
		    sizeof(books->paw.date),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->paw.confCode, 
		    sizeof(books->paw.confCode),
		    tok,
		    ind++,
		    &count);
    
    /*Lien/Judgment*/
    ret = takeField(books->jl.totalHitCount, 
		    sizeof(books->jl.totalHitCount),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->jl.debtorName, 
		    sizeof(books->jl.debtorName),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->jl.filingType, 
		    sizeof(books->jl.filingType),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->jl.amount, 
		    sizeof(books->jl.amount),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->jl.filingDate, 
		    sizeof(books->jl.filingDate),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->jl.creditor, 
		    sizeof(books->jl.creditor),
		    tok,
		    ind++,
		    &count);
    
    ret = takeField(books->jl.caseNumber, 
		    sizeof(books->jl.caseNumber),
		    tok,
		    ind++,
		    &count);
    
    ret2 = takeField(lbuf, 
		     sizeof(lbuf),
		     tok,
		     ind,
		     NULL);

    if(NULL != expected)
    {
	*expected = ind;
    }

    if(NULL != overflow)
    {
	*overflow = 0;
	if(0 == ret2)
	{
	    *overflow = 1;
	}
	else
	{
	    if(count < ind)
	    {
		*overflow = -1;
	    }
	}
    }

    /*
      ret = takeField(books->, 
      sizeof(books->),
      tok,
      ind++,
      &count);
    */

    return (count);
}
