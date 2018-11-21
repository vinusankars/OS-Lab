#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

sem_t s[5];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//sem_t mutex;

void get(int phil)
{
	//sem_wait(&mutex);
	pthread_mutex_lock(&lock);
	if(phil == 4)
	{
		sem_wait(&s[(phil+1)%5]);
		printf("Get %d\n", phil+1);
		sem_wait(&s[phil%5]);
	}
	else
	{
		sem_wait(&s[phil%5]);
		printf("Get %d\n", phil+1);
		sem_wait(&s[(phil+1)%5]);
	}
	pthread_mutex_unlock(&lock);
	//sem_post(&mutex);
}

void put(int phil)
{
	//sem_wait(&mutex);
	//pthread_mutex_lock(&lock);
	if(phil == 4)
	{
		sem_post(&s[(phil+1)%5]);
		printf("Put %d\n", phil+1);
		sem_post(&s[phil%5]);
	}
	else
	{
		sem_post(&s[phil%5]);
		printf("Put %d\n", phil+1);
		sem_post(&s[(phil+1)%5]);
	}
	//pthread_mutex_unlock(&lock);
	//sem_post(&mutex);
}

void *phil(void* arg)
{
	int ph = (int*)arg;

	if(ph == 4)
	{
		get(ph);
		printf("Philosopher %d ate\n", ph+1);
		sleep(1);
		put(ph);
	}

	else
	{
		get(ph);
		printf("Philosopher %d ate\n", ph+1);
		sleep(1);
		put(ph);
	}

	return NULL;
}

int main()
{
	pthread_t p[5];

	//sem_init(&mutex, 0, 1); 
	for(int i = 0; i < 5; i++)   
   		sem_init(&s[i], 0, 1); 

	for(int i=0; i<5; i++)
		pthread_create(&p[i], NULL, phil, (void*)i);

	for(int i=0; i<5; i++)
		pthread_join(p[i], NULL);

	return 0;
}