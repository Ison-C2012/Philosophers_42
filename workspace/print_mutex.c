#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_share {
	int	nb_of_th;
	int	count_created_thread;
	long long	time_of_beginning;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	count_mutex;
}	t_share;

typedef struct s_thread {
	int	id;
	t_share	*share;
	pthread_t	th;
}	t_thread;

long long	get_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long) tv.tv_sec * 1000000 + tv.tv_usec);
}

long long	get_elapsed_time(t_share *share)
{
	return (get_time_us() - share->time_of_beginning);
}

void	print(t_share *share, char *s)
{
	pthread_mutex_lock(&share->print_mutex);
	printf("%lld %s\n", get_elapsed_time(share), s);
	pthread_mutex_unlock(&share->print_mutex);
}

void	*routine(void *t)
{
	t_thread *thread = (t_thread *) t;
	t_share *share = thread->share;

	pthread_mutex_lock(&share->count_mutex);
	share->count_created_thread++;
	pthread_mutex_unlock(&share->count_mutex);
	while (1)
	{
		pthread_mutex_lock(&share->count_mutex);
		if (share->count_created_thread == share->nb_of_th)
		{
			pthread_mutex_unlock(&share->count_mutex);
			break ;
		}
		pthread_mutex_unlock(&share->count_mutex);
		usleep(100);
	}
	print(share, "printed.");
}

int	main(void)
{
	t_thread	*thread;
	struct s_share	share;

	share.nb_of_th = 100;
	share.count_created_thread = 0;
	share.time_of_beginning = get_time_us();
	if (pthread_mutex_init(&share.print_mutex, NULL))
		return 1;
	if (pthread_mutex_init(&share.count_mutex, NULL))
		return 1;
	thread = (t_thread *)malloc(sizeof(t_thread) * share.nb_of_th);
	if (!thread)
		return 1;
	for (int i=0;i<share.nb_of_th;i++)
	{
		thread[i].id = i+1;
		thread[i].share = &share;
	}
	for (int i=0;i<share.nb_of_th;i++)
		pthread_create(&thread[i].th, NULL, &routine, (void *)thread);
	for (int i=0;i<share.nb_of_th;i++)
		pthread_join(thread[i].th, NULL);
	pthread_mutex_destroy(&share.count_mutex);
	pthread_mutex_destroy(&share.print_mutex);
	free(thread);
	return 0;
}
