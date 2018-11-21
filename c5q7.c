#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
int rc = fork();
if (rc == 0) fclose(stdout); printf("1\n");
return 0;
}
