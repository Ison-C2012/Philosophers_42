/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:36:01 by keitotak          #+#    #+#             */
/*   Updated: 2026/04/14 11:21:42 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

typedef struct s_rtval
{
	t_val	*setval;
	pthread_mutex_t	mutex;
	int	*st_fork;
	int	nb_seat;
}	t_rtval;

void	*routine(void *val)
{
	t_rtval	*rtval = (t_rtval *)val;
	int	left_nb, right_nb;

	left_nb = rtval->nb_seat;
	if (left_nb > 0)
		right_nb = left_nb - 1;
	else
		right_nb = rtval->setval->nb_philo - 1;
	rtval->st_fork[left_nb] = 1;
	rtval->st_fork[right_nb] = 1;
//	printf("No.%d\n", rtval->nb_seat);
	return (NULL);
}

int	philo(t_shared *shared);
{
	pthread_t	philo[shared->nb_philo];
	t_rtval		*rtvals;
	int			i, j;

	rtvals = (t_rtval *)malloc(sizeof(t_rtval));
	rtvals->setval = shared;
	pthread_mutex_init(&rtvals->mutex, NULL);
	rtvals->st_fork = (int *)malloc(sizeof(int) * shared->nb_philo);
	memset(rtvals->st_fork, 0, shared->nb_philo);
	i = 0;
	while (i < vals->nb_philo)
	{
		rtvals->nb_seat = i;
		if (pthread_create(&philo[i], NULL, &routine, (void *)rtvals))
			return (1);
		i++;
	}
	j = 0;
	while (j < vals->nb_philo)
	{
		if (pthread_join(philo[j], NULL))
			return (1);
		j++;
	}
	pthread_mutex_destroy(&rtvals->mutex);
	free(rtvals->st_fork);
	free(rtvals);
	return (0);
}
