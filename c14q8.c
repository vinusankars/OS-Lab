#include<stdio.h>
#include<stdlib.h>

int main()
{
int *x;
x = (int*)malloc(sizeof(int));
*x = 0;
for(int i=1; i<100; i++)
{
x = (int*)realloc(x,i*sizeof(int));
*(x+i*sizeof(int)) = 0;
} 
return 0;
}
