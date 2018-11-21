#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	int rc = fork();
	if (rc < 0) printf("Error\n");
	else if (rc == 0){
		int w1 = wait(NULL); 
		printf("hello Child PID: %d Wait: %d\n", (int) getpid(), w1);}
	else {int w = wait(NULL); printf("goodbye Parent PID: %d Wait: %d\n", (int) getpid(),  w);}
	return 0;
}
