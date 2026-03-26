#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void	*threadFunc(void *arg)
{
	int	*num = (int *)arg;

	*num = 10;
	usleep(1000000);
	printf("thread num: %d\n", *num);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread;
	int			value = 42;

	if (pthread_create(&thread, NULL, threadFunc, (void *)&value))
		printf("Failed to create thread.\n");
	usleep(500000);
	value = 2;
	printf("main num: %d\n", value);
	pthread_join(thread, NULL);
	return (0);
}
