
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void	*start_routine(void *nb)
{
	int	*n = (int *)nb;
	for (int j=0;j<*n;j++)
		printf("hello.\n");
	return (NULL);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	int	nb = atoi(av[1]);
	pthread_t	**threadlist = (pthread_t **)malloc(sizeof(pthread_t *) * nb);
	int	*i = (int *)malloc(sizeof(int) * 1);

	*i = 0;
	while (*i<nb)
	{
		pthread_create(threadlist[*i], NULL, start_routine, (void *)i);
		*i++;
	}
	return 0;
}
