#include<stdio.h>
#include<stdlib.h>

int checkOrder5(int *c,int value);
int compareCards(int *a,int *b,int offset_a,int size_b);
int checkOrder4(int *c,int value,int high_f);

int main(int argc, char *argv[])
{

  int cards[5];
  char suits[5];

  char lastSuit = '\0';
  int suitchange = 0;
  int i,j;
  int jokers = 0;
  int neighbors[2];
  int bounds[2];
  int ind;
  int breaker_a = -1;
  int breaker_b = -1;
  int in_a_row = 0;
  int row_value = -1;

  int isRoyalFlush = 0;
  int isFlush = 0;

  int straights[13];

  int tmp;
  int isStraight = 0;
  int straightRank = -1;

  int isStraight4 = 0;
  int straightRank4 = -1;

  int possible5 = 0;

  int high4 = 0;
  int low4 = 0;

  if(argc < 7)
    {
      fprintf(stderr,"USAGE:%s n1 n2 n3 n4 n5 ind\n",argv[0]);
      exit(-1);
    }

  for(i = 0; i < 13 ; i++)
    {
      straights[i] = 0;
    }

  for(i = 0,jokers = 0 ; i < 5 ; i++)
    {
      cards[i] = atoi(argv[(i+1)]);
      suits[i] = '\0';
      if(cards[i] == -1)
	{
	  jokers++;
	  continue;
	}

      for(j = 0 ; j < strlen(argv[(i+1)]); j++)
	{
	  if(isalpha(argv[(i+1)][j]))
	    {
	      suits[i] = argv[(i+1)][j];
	      break;
	    }
	}

      if(cards[i] >= 0 && cards[i] < 13)
	{
	  straights[cards[i]] = 1;
	}
    }

  neighbors[0] = 0;
  neighbors[1] = 0;

  ind = atoi(argv[6]);

  if(ind < 0 )
    ind = 0;

  if(ind > 4)
    ind = 4;

  bounds[0] = ind;
  bounds[1] = ind;

  /*our card it not a joker*/
  for(i = ind - 1; i > -1; i--)
    {
      if(cards[i] == cards[ind] || cards[i] == -1)
	{
	  neighbors[0]++;
	  bounds[0] = i;
	  continue;
	}
      breaker_a = cards[i];
      break;
    }

  for(i = ind + 1; i < 5; i++)
    {
      if(cards[i] == cards[ind] || cards[i] == -1)
	{
	  neighbors[1]++;
	  bounds[1] = i;
	  continue;
	}
      breaker_b = cards[i];
      break;
    }

  in_a_row = 1 + neighbors[0] + neighbors[1];
  row_value = cards[ind];
  
  if(cards[ind] == -1)
    {      
      /*the card we flipped on is a joker*/
      if((breaker_a > -1) && (breaker_a < breaker_b))
	{
	  bounds[0]--;
	  row_value = breaker_a;
	  in_a_row++;
	}
      else if((breaker_b > -1) && (breaker_b < breaker_a))
	{
	  row_value = breaker_b;
	  bounds[1]++;
	  in_a_row++;
	}
      else if((breaker_a > -1) && (breaker_a == breaker_b))
	{
	  bounds[0]--;
	  bounds[1]++;
	  in_a_row += 2;
	  row_value = breaker_a;
	}
      else
	{
	  /*we have 5 jokers - make it a Royal Flush*/
	  in_a_row = 5;
	  isStraight = 0;
	  isFlush = 1;
	  isRoyalFlush = 0;
	  straightRank = 0;
	  row_value = 0; /*Aces*/
	  bounds[0] = 0;
	  bounds[1] = 4;
	}
    }

  for(i = 0; !isStraight && i < 9 ; i++)
    {
      straightRank = i;
      for(j = i,tmp = jokers ; j < (i + 5) ; j++)
	{
	  if(straights[j])
	    {
	      continue;
	    }
	  tmp--;
	  if(tmp < 0)
	    {
	      break;
	    }
	}

      if(j == (i + 5))
	{
	  bounds[0] = 0;
	  bounds[1] = 4;
	  possible5 = 1;
	  /*Check Straight order*/
	  isStraight = checkOrder5(cards,straightRank);
	}
    }

  if(!isStraight)
    {
      straightRank = -1;
    }

  if(in_a_row >= 3)
    {
      printf("Have a touple %d [%d .. %d]\n",row_value,bounds[0],bounds[1]);

      suitchange = 0;
      lastSuit = '\0';

      for(i = bounds[0] ; i <= bounds[1] ; i++)
	{
	  if(suits[i] == '\0')
	    {
	      continue;
	    } 
	  if(lastSuit == '\0')
	    {
	      lastSuit = suits[i];
	      continue;
	    }
	  if(lastSuit != suits[i])
	    {
	      suitchange = 1;
	    }
	}
      if(!suitchange)
	{
	  isFlush = 1;
	}
    }

  if(isStraight)
    {
      printf("This hand is a Straight Rank %d [%d .. %d]\n",
	     straightRank,bounds[0],bounds[1]);
      for(i = 0 ; i < 5 ; i++)
	{
	  if(suits[i] == '\0')
	    {
	      continue;
	    } 
	  if(lastSuit == '\0')
	    {
	      lastSuit = suits[i];
	      continue;
	    }
	  if(lastSuit != suits[i])
	    {
	      suitchange = 1;
	    }
	}
      if(!suitchange)
	{
	  isFlush = 1;
	  if( straightRank == 0)
	    {
	      isRoyalFlush = 1;
	    }
	}

    }
  else if(in_a_row < 3)
    {
      /*check for partial straits*/

      for(i = 0; !isStraight4 && i < 10 ; i++)
	{
	  straightRank4 = i;
	  for(j = i,tmp = jokers ; j < (i + 4) ; j++)
	    {
	      if(straights[j])
		{
		  continue;
		}
	      tmp--;
	      if(tmp < 0)
		{
		  break;
		}
	    }
	  
	  if(j == (i + 4))
	    {
	      low4 = 0;
	      high4 = 0;

	      if(4 != ind)
		{
		  low4 = checkOrder4(cards,straightRank4,0);
		  bounds[0] = 0;
		  bounds[1] = 3; 
		}
	      
	      if(!low4 && 0 != ind)
		{
		  high4 = checkOrder4(cards,straightRank4,1);
		  bounds[0] = 1;
		  bounds[1] = 4; 
		}

	      isStraight4 = (low4 || high4);

	      if(!isStraight4 && possible5)
		{
		  /*there was a possible 5 stright before try the
		    next rank down*/
		  straightRank4++;
		  low4 = 0;
		  high4 = 0;
		  if(4 != ind)
		    {
		      low4 = checkOrder4(cards,straightRank4,0);
		      bounds[0] = 0;
		      bounds[1] = 3; 
		    }
		  
		  if(!low4 && 0 != ind)
		    {
		      high4 = checkOrder4(cards,straightRank4,1);
		      bounds[0] = 1;
		      bounds[1] = 4; 
		    }
		  isStraight4 = (low4 || high4);
		}
	    }
	}

      if(!isStraight4)
	{
	  straightRank4 = -1;
	}
    }

  if(isStraight4)
    {

      lastSuit = '\0';
      printf("This hand is a Partial Straight Rank %d [%d .. %d]\n",
	     straightRank4,bounds[0],bounds[1]);
      for(i = bounds[0] ; i <= bounds[1] ; i++)
	{
	  if(suits[i] == '\0')
	    {
	      continue;
	    } 
	  if(lastSuit == '\0')
	    {
	      lastSuit = suits[i];
	      continue;
	    }
	  if(lastSuit != suits[i])
	    {
	      suitchange = 1;
	    }
	}

      if(!suitchange)
	{
	  isFlush = 1;
	}
    }

  if(isFlush)
    {
      printf("This hand has a flush element\n");
    }

  if(isRoyalFlush)
    {
      printf("This hand is a Royal Flush\n");
    }


}

int checkOrder5(int *c,int value)
{
  int d[5];
  int d2[5];
  int ret = 0;
  int i,j;

  /*set up forward and revered order hands*/
  for(i = 0 , j = 4 ; i < 5; i++,j--)
    {
      d[i] = value + i;
      d2[j] = d[i];
    }

  ret = (compareCards(c,d,0,5) || compareCards(c,d2,0,5));

  return (ret);
}

int checkOrder4(int *c,int value,int high_f)
{
  int d[4];
  int d2[4];
  int ret = 0;
  int i,j;

  /*this will play with the comparison subscript*/
  if(high_f > 0)
    {
      high_f = 1;
    }
  else
    {
      high_f = 0;
    }

  for(i = 0 , j = 3; i < 4 ; i++,j--)
    {
      d[i] = value + i;
      d2[j] = d[i];
    }

  ret = (compareCards(c,d,high_f,4) || compareCards(c,d2,high_f,4));
  
  return (ret);
}

int compareCards(int *a,int *b,int offset_a,int size_b)
{
  int i = 0;
  int j = 0;
  int found = 1;

  for(i = 0,j = offset_a ; i < size_b && found; i++,j++)
    {
      if(-1 == a[j])
	{
	  /*encountered a joker*/
	  continue;
	}

      if(a[j] != b[i])
	{
	  found = 0;
	}
    }

  return (found);
}
