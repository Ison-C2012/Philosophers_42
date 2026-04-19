/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Creatinged: 2026/04/13 17:36:01 by keitotak          #+#    #+#             */
/*   Updated: 2026/04/19 18:07:05 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	thinking(t_philo *p)
{
	printf("%lld %d is thinking\n", get_elapsed_time(p), p->id);
}

void	eating(t_philo *p)
{
	printf("%lld %d is eating\n", get_elapsed_time(p), p->id);
	usleep(p->shared->time_to_eat * 1000);
}

void	sleeping(t_philo *p)
{
	printf("%lld %d is sleeping\n", get_elapsed_time(p), p->id);
	usleep(p->shared->time_to_sleep * 1000);
}

void	*philo_routine(void *p)
{
	t_philo			*philo = (t_philo *)p;

	while (1)
	{
		thinking(philo);
		if (philo->id % 2 == 0)
			pick_up_left_right(philo);
		else
			pick_up_right_left(philo);
		eating(philo);
		if (philo->id % 2 == 0)
			put_down_left_right(philo);
		else
			put_down_right_left(philo);
		sleeping(philo);
	}
	return (NULL);
}

int	philo(t_shared *shared)
{
	t_philo	philos[shared->nb_philo];
	int		i, j;

	i = 0;
	while (i < shared->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].shared = shared;
		philos[i].left_fork = &shared->forks[i];
		philos[i].right_fork = i > 0 ? &shared->forks[i - 1] : &shared->forks[shared->nb_philo - 1];
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
