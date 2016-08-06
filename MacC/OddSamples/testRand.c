#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

double weightedRandom(double low, 
		      double high, 
		      double weightHigh);

int main(int argc, char *argv[])
{
  double low;
  double high;
  double weight;
  double answer;
  int i;

  printf("Enter Low Number ");
  scanf("%lf",&low);
  printf("Enter High Number ");
  scanf("%lf",&high);
  printf("Enter Weight 0.0 to 1.0 ");
  scanf("%lf",&weight);

  for(i = 0 ; i < 100; i++)
    {
      answer = weightedRandom(low,high,weight);
      printf("%.5f\n",answer);
    }

  return (0);
}


double weightedRandom(double plow, 
		      double phigh, 
		      double weightHigh)
{

  int num;  
  double prob  = 0.0;
  double high = 0.0;
  double diff = 0.0;

  num = rand();
  prob = (double)num / (double)RAND_MAX;

  if(weightHigh >= 1.0 || 
     prob >= (1.0 - weightHigh))
    {
      return (phigh);
    }
  
  high = 1.0 - weightHigh;
  
  /*get the ratio of what is left*/
  prob = prob / high;
  
  if(prob >= 1.0)
    {
      prob = 1.0;
    }
  
  diff = phigh - plow;
  
  return (plow + diff * prob) ;
  
}
