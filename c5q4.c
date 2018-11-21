#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	int rc = fork();
	char *args[] = {"../../../bin/ls", NULL};
	if (rc < 0) printf("Error\n");
	else if (rc == 0) execvp(args[0], args);
	else printf("1\n");
	return 0;
}
