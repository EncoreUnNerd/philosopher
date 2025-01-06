#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *func_test()
{
	printf("ouais !!");
	return (NULL);
}

int main()
{
	pthread_t thread1;

	pthread_create(&thread1, NULL, func_test, NULL);
	pthread_join(thread1, NULL);

	return (0);
}