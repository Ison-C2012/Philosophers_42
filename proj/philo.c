/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:36:01 by keitotak          #+#    #+#             */
/*   Updated: 2026/04/16 23:04:20 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	*philo_routine(void *p)
{
	t_philo	*philo = (t_philo *)p;

//	printf("No.%d\n", philo->id);
	if (philo->id % 2 == 0)
	{

	}
	else
	{

	}
	return (NULL);
}

int	philo(t_shared *shared)
{
	t_philo	philos[shared->nb_philo];
	int			i, j;

	i = 0;
	while (i < shared->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].shared = shared;
		philos[i].left_fork = shared->forks[i];
		philos[i].right_fork = i > 0 ? shared->forks[i - 1] : shared->forks[shared->nb_philo - 1];
		if (pthread_create(&philos[i].th, NULL, &philo_routine, (void *)&philos[i]))
			return (1);
		i++;
	}
	j = 0;
	while (j < shared->nb_philo)
	{
		if (pthread_join(philos[j].th, NULL))
			return (1);
		j++;
	}
	return (0);
}
