#include <pthread.h>

int	main(void)
{
	pthread_mutex_t mutex;

//	pthread_mutex_init(&mutex, NULL);
	int rs = pthread_mutex_destroy(&mutex);
	return rs;
}
