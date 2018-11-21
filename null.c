#include<stdlib.h>
#include<stdlib.h>

int main()
{
int* p;
p = malloc(sizeof(int));
*p = 10;
p = NULL;
free(p);
return 0;
}
