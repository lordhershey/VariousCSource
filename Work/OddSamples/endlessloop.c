#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{

  here:
  
  printf("Endless Loop\n");

  goto here;

}
