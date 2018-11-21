#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ll = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t rl = PTHREAD_MUTEX_INITIALIZER;

int forks[5] = {0};

void getl(int phil)
{
	pthread_mutex_lock(&lock);
	while(forks[phil%5] == 1)
		pthread_cond_wait(&ll, &lock);
	printf("Get left fork for philosopher %d\n", phil+1);
	forks[phil%5] = 1;
	pthread_mutex_unlock(&lock);
}

void getr(int phil)
{
	pthread_mutex_lock(&lock);
	while(forks[(phil+1)%5] == 1)
		pthread_cond_wait(&rl, &lock);
	printf("Get right fork for philosopher %d\n", phil+1);
	forks[(phil+1)%5] = 1;
	pthread_mutex_unlock(&lock);
}

void putl(int phil)
{
	pthread_mutex_lock(&lock);
	forks[phil%5] = 0;
	pthread_cond_signal(&ll);
	pthread_mutex_unlock(&lock);
}

void putr(int phil)
{
	pthread_mutex_lock(&lock);
	forks[(phil+1)%5] = 0;
	pthread_cond_signal(&rl);
	pthread_mutex_unlock(&lock);
}

void *phil(void* arg)
{
	int ph = (int*)arg;

	if(ph == 4)
	{
		getr(ph);
		getl(ph);
		printf("Philosopher %d ate\n", ph+1);
		sleep(1);
		putr(ph);
		putr(ph);
	}

	else
	{
		getl(ph);
		getr(ph);
		printf("Philosopher %d ate\n", ph+1);
		sleep(1);
		putl(ph);
		putr(ph);
	}

	return NULL;
}

int main()
{
	pthread_t p[5];

	for(int i=0; i<5; i++)
		pthread_create(&p[i], NULL, phil, (void*)i);

	for(int i=0; i<5; i++)
		pthread_join(p[i], NULL);

	return 0;
}