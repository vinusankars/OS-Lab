#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

int count = 0;
int first = 0;
int second = 0;
int arr[8000] = {0};
for(int i=0; i<8000; i++)
arr[i] = 1;

void *f1(void *arg){
printf("Started 1\n");
for(int i=0; i<4000; i++) 
first += arr[i];
return NULL;}

void *f2(void *arg){
printf("Started 2\n");
for(int i=4000; i<8000; i++)
second += arr[i];
return NULL;}

int main(int argc, char *argv[]){
pthread_t p[2];
int rc1, rc2;
printf("main: begin\n");

rc1 = pthread_create(&p[0], NULL, f1, (void *)(1));
rc2 = pthread_create(&p[1], NULL, f2, (void *)(2));

printf("Waiting for 1\n");
rc1 = pthread_join(p[0], NULL);
printf("Waiting for 2\n");
rc2 = pthread_join(p[1], NULL);

printf("\nAnswer: %d\n", (first+second));

printf("main: end\n");
return 0;}
