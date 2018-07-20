
#include "malloc.h"
#include <string.h>
#include <stdio.h>

int main()
{
	char *test = (char*)ft_malloc(20);
	char *test2 = (char*)ft_malloc(20);
	strcpy(test, "01234567890123456789012345");
	strcpy(test2, "How are you");
	printf("It works: %s\n", test);
	printf("It works: %s\n", test2);
	ft_free(test2);
	return (0);
}