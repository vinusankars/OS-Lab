#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

int count = 0;

void *our_thread(void *arg){
printf("Started %d: count %d\n", (int)arg, count);
for(int i=0; i<10; i++) count++;
sleep(1);
return NULL;}

int main(int argc, char *argv[]){
pthread_t p[20];
int rc;
printf("main: begin\n");
for(int i=0; i<20; i++)
rc = pthread_create(&p[i], NULL, our_thread, (void *)(i));

for(int i=0; i<20; i++){
printf("Waiting for %d\n", i);
rc = pthread_join(p[i], NULL);}

printf("main: end\n");
return 0;}
