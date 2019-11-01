#include <stdio.h>
typedef struct _array{
	int one;
	int two;
} ARRAY;
ARRAY *test_get_test()
{
	static ARRAY test;
	return &test;
	}
int main()
{
	ARRAY *test=NULL;
	test=test_get_test();
	if(test == NULL)
		printf("failed\n");
	else
		printf("success\n");
	return 0;
}
