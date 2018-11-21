#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

struct st{
int x;
int y;};

void *our_thread(void *arg){
struct st *i = (struct st*)(arg);
printf("Started: x is %d, y is %d\n", i->x, i->y);
sleep(1);
return NULL;}

int main(){
pthread_t p;
int rc;
printf("main: begin\n");

struct st i = {1,2};
rc = pthread_create(&p, NULL, our_thread, (void *)(&i));

printf("Waiting\n");
rc = pthread_join(p, NULL);

printf("main: end\n");
return 0;}
