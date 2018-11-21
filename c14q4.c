#include<stdio.h>
#include<stdlib.h>

int main()
{
int* x;
x = (int*)malloc(8);
*x = 10;
printf("Value of x is %d\n", *x);
return 0;
}
