#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>

void *thread(void* arg){ 
printf("Hello World %d\n", (int)arg);
sleep(1);
return NULL;}

int main(){
pthread_t p[20];
printf("main:start\n");

for(int i=0; i<20; i++){
int x = i+1;
pthread_create(&p[i], NULL, thread, (void*)x);}

for(int i=0; i<20; i++) pthread_join(p[i], NULL);

return 0;
}


/*
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>

void *thread(void* arg){ 
printf("Hello World %d\n", (int)arg);
sleep(1);
return NULL;}

int main(){
pthread_t p[20];
printf("main:start\n");

for(int i=0; i<20; i++){
int x = i+1;
pthread_create(&p[i], NULL, thread, (void*)x);}

for(int i=0; i<20; i++) pthread_join(p[i], NULL);

return 0;
}
*/
