
int main(int argc, char *argv[])
{
#if 0
int num[3][4] = {
{10,20,30,40}, {50,60,70,80},{90,100,110,120}};
int n = *(*(num+1)+1)+1;
printf("%d\n", n);

 printf("%d\n",num+1);
 printf("%d\n",*(num+1));
 printf("%d\n",**(num+1));
 printf("%d\n",**(num+1)+1);
 printf("%d\n",*(*(num+1)+1));
#endif

struct { char c[3]; short s; } num[4] = { 
{10,20,30},{40,50,60},{70,80,90},{100,110,120}}; 
int n = *((*(num+1)).c+6)+1; 
printf("%d\n", n); 
}
