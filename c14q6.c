#include<stdio.h>
#include<stdlib.h>

int main()
{
int* data;
data = (int*)malloc(100*sizeof(int));
for(int i=0; i<100; i++)
*(data+i*sizeof(data)) = 0;
for(int i=0; i<100; i++)
free(data+i*sizeof(int));
printf("Value is %d\n", *(data+4*sizeof(int)));
return 0;
}

