#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int x = 100;

int main()
{
	int rc = fork();
	if (rc < 0) printf("Error\n");
	else if ( rc == 0) {x = 50; printf("Child: x is %d\n", x);}
	else {x = 10; printf("Parent: x is %d\n", x);}
	printf("Done x is %d\n", x);
	return 0;
}
