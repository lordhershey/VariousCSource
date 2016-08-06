#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char** graph(int inputsize,char *input[], int *ressize)
{

  char *rootseen;
  char *currentsearch;
  char *nextsearch;
  
  int arrsize = sizeof(char) * (inputsize);
  int maxlen = 0;


  printf("Input size : %d\n",inputsize);

  {
    int i;
    for(i = 0 ; i < inputsize ; i++)
      {
	printf("%s\n",input[i]);
	if(strlen(input[i]) > maxlen)
	  {
	    maxlen = strlen(input[i]);
	  }
      }
  }

  maxlen++;

  char *arr = malloc(arrsize * maxlen);
  memset(arr,'\0',sizeof(char) * arrsize * maxlen);


  rootseen = malloc(sizeof(char) * maxlen);
  currentsearch = malloc(sizeof(char) * maxlen);
  nextsearch = malloc(sizeof(char) * maxlen);

  memset(rootseen,'\0',maxlen);
  memset(currentsearch,'\0',maxlen);
  memset(nextsearch,'\0',maxlen);

  nextsearch[0] = input[inputsize-1][0];

  int topi = 0;
  int first = 1;

  do{
    memcpy(currentsearch,nextsearch,maxlen);
    memset(nextsearch,'\0',maxlen);

    printf("Current Search : %s\n",currentsearch);
    sprintf(&arr[strlen(arr)],"%s|",currentsearch);

    topi++;

    int curri;
    for(curri = 0 ; curri < strlen(currentsearch) ; curri++)
      {

	/*find the root of the current guy*/
	int rootidx = -1;
	for(rootidx = 0 ; rootidx < (inputsize - 1); rootidx++)
	  {
	    if(input[rootidx][0] == currentsearch[curri])
	      {
		break;
	      }
	  }

	if(rootidx >= (inputsize - 1))
	  {
	    /*Not Found Continue*/
	    continue;
	  }

	/*Go through found root add to the next search those who are not seen*/
	int addi;
	for(addi = 2 ; addi < strlen(input[rootidx]); addi +=2)
	  {

	    /*Make sure the current guy is not on the list*/
	    int seeni;
	    for(seeni = 0 ; seeni < strlen(rootseen) ; seeni++)
	      {
		if(input[rootidx][addi] == rootseen[seeni])
		  {
		    break;
		  }
	      }

	    if(seeni >= strlen(rootseen))
	      {
		/*we have not seen this add it to the next search - provided it doesn't already exist
		  here and provided the element*/
		int nexti;
		for(nexti = 0 ; nexti < strlen(nextsearch);nexti++)
		  {
		    if(input[rootidx][addi] == nextsearch[nexti])
		      {
			break;
		      }
		  }

		if(nexti >= strlen(nextsearch))
		  {
		    /*Make sure it does not already exist on the results*/
		    int ii;
		    int found = 0;
		    for(ii = 0 ; ii< strlen(arr) ; ii++)
		      {
			if(input[rootidx][addi] == arr[ii])
			  {
			    found = 1;
			    break;
			  }
		      }
		    if(!found)
		      {
			nextsearch[strlen(nextsearch)] = input[rootidx][addi];
		      } 
		  }

	      }

	  }

	/*at this point we should have added everybody to the next search for this node*/
	/*Mark this as a seen root*/
	rootseen[strlen(rootseen)] = currentsearch[curri];

      }

  }while('\0' != nextsearch[0]);


  printf("All Results: %s\n",arr);
    
  *ressize = 0;
  
  char **backstructure = NULL;

  if(topi > 1)
    {
      *ressize = (topi-1);
      int sz = (topi-1);

      backstructure = (char **)malloc(sizeof(char *) * sz);
      int i;
      for(i = 0; i < sz ; i++)
	{
	  /*give way too much padding*/
	  backstructure[i] = (char *)malloc(sizeof(char) * (maxlen * 2));
	  memset(backstructure[i],'\0',sizeof(char) * (maxlen * 2));
	}

      int j = 0;
      for(i = 2; i < strlen(arr) -1;i++)
	{
	  if(arr[i] == '|')
	    {
	      j++;
	      if(j >= sz)
		{
		  break;
		}
	      continue;
	    }

	  sprintf(&backstructure[j][strlen(backstructure[j])],"%c,",arr[i]);
	}

      for(i = 0 ; i < sz;i++)
	{
	  int tt = strlen(backstructure[i]);
	  if(tt > 1)
	    {
	      backstructure[i][tt-1] = '\0';
	    }
	}

    }

  free(rootseen);
  free(currentsearch);
  free(nextsearch);
  free(arr);

  return backstructure;
}

int main() {
  /*FILE *f = fopen(getenv("OUTPUT_PATH"), "w");*/
    FILE *f = stdout;
    int res_size;
    char** res;
    
    int _input_size, _input_i;
    scanf("%d\n", &_input_size);
    char* _input[_input_size];
    for(_input_i = 0; _input_i < _input_size; _input_i++) {
        char* _input_item;
        _input_item = (char *)malloc(10240 * sizeof(char));
        scanf("\n%[^\n]",_input_item);
        _input[_input_i] = _input_item;
    }
    
    res = graph(_input_size, _input, &res_size);
    int res_i;
    for(res_i=0; res_i < res_size; res_i++) {
    
        fprintf(f, "%s\n", res[res_i]);
        
    }
    
    
    fclose(f);
    return 0;
}
