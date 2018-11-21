#include<stdio.h>
#include<stdlib.h>

int main(){
int *a;
*a = 10;
a = NULL;
printf("Dereferenced value is %d", *a);
return 0;
}
