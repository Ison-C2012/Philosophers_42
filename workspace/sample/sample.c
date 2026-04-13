#include <stdio.h>
#include <pthread.h>

#define NUM_THREAD 6

void	*threadFunc(void *arg)
{
	int	*thread_num = (int *)arg;
	int	sum = 0;

	printf("thread number: %d\n", *thread_num);
	if (*thread_num == 2)
	{
		printf("Thread %d exited.\n", *thread_num);
		pthread_exit(NULL);
	}
	for (int i = 1; i <= 10; i++)
		sum = sum + i;
	printf("SUM: %d Thread: %d\n", sum, *thread_num);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread[NUM_THREAD];

	for (int i = 0; i < NUM_THREAD; i++)
	{
		if (pthread_create(&thread[i], NULL, threadFunc, (void *)&i) != 0)
			printf("Failed to create thread.\nThread number: %d\n", i);
	}
//	sleep(1);
	for (int j = 0; j < NUM_THREAD; j++)
		pthread_join(thread[j], NULL);
	return (0);
}
