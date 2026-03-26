#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void	*threadFunc(void *arg)
{
	int	*num = (int *)arg;

	pthread_mutex_lock(&mutex);
	*num = 10;
	usleep(1000000);
	printf("thread num: %d\n", *num);
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread;
	int			value = 42;

	if (pthread_create(&thread, NULL, threadFunc, (void *)&value))
		printf("Failed to create thread.\n");
	usleep(500000);
	pthread_mutex_lock(&mutex);
	value = 2;
	printf("main num: %d\n", value);
	pthread_mutex_unlock(&mutex);
	pthread_join(thread, NULL);
	return (0);
}
