#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char* argv[])
{
long long int mem;
float time;
if(argc == 3){
time = atof(argv[2]);
mem = atoi(argv[1]);}

else exit(0);

int *x;
size_t i = 0;

mem = mem*1024*1024;
x = (int*)malloc(mem);

clock_t begin = clock();
int* y;

while((double)(clock()-begin)/CLOCKS_PER_SEC<time){
*(x+i) = 0;
i += (int)(sizeof(int));
printf("%f\n", (double)(clock()-begin)/CLOCKS_PER_SEC);
if(i>=mem){i = 0; y = x;}}

return 0;
}
