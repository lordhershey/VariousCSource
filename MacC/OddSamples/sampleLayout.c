#include <stdio.h>
#include <stdlib.h>
#include <strings.h>


void fake()
{
    int i;
    int segmentSize;
    int scoreLo[20];
    int scoreHi[20];
    int scoreNo[20];
    int scorePd[20];
    int ii, jj, kk;
    int nn, mm;
    int numberPaid = 0;
    double amountPd[20];
    double amountOr[20];
    double amountOrig = 0.;
    double amountPaid = 0.;

    printf("%p\n",&i);
    printf("%p\n",&segmentSize);
    printf("%p\n",scoreLo);
    printf("%p\n",scoreHi);
    printf("%p\n",scoreNo);
    printf("%p\n",scorePd);
    printf("%p\n",&ii);
    printf("%p\n",&jj);
    printf("%p\n",&kk);
    printf("%p\n",&nn);
    printf("%p\n",&mm);
    printf("%p\n",&numberPaid);
    printf("%p\n",&amountPd);
    printf("%p\n",&amountOr);
    printf("%p\n",&amountOrig);
    printf("%p\n",&amountPaid);

}

int main(int argc, char *argv)
{
  fake();
}
