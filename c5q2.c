#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int fd = open("file.txt", O_RDONLY);
	printf("Fd is %d\n", fd);
	int rc = fork();
	if (rc < 0) printf("Error\n");
	else if (rc == 0) printf("Child: %d\n", fd);
	else printf("Parent: %d\n", fd);
	close(fd);
	return 0;
}
