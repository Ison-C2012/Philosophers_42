/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:36:00 by by keitotak       #+#    #+#             */
/*   Updated: 2026/04/21 15:57:12 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *p)
{
	t_philo			*philo = (t_philo *)p;
	pthread_mutex_t	meal_log;

	pthread_mutex_init(&meal_log, NULL);
	philo->meal_log = &meal_log;
	while (1)
	{
		if (philo->shared->stop_flag)
			break ;
		thinking(philo);
		take_forks(philo);
		if (philo->shared->stop_flag)
			break ;
		eating(philo);
		put_forks(philo);
		if (philo->shared->stop_flag)
			break ;
		sleeping(philo);
	}
	pthread_mutex_destroy(&meal_log);
	return (NULL);
}

int	init_philo(t_philo *philo, t_shared *shared, int i)
{
	philo->id = i + 1;
	philo->shared = shared;
	philo->last_meal_time = get_elapsed_time(philo);
	philo->left_fork = &shared->forks[i];
	if (i > 0)
		philo->right_fork = &shared->forks[i - 1];
	else
		philo->right_fork = &shared->forks[shared->nb_philo - 1];
	return (0);
}

int	philo(t_shared *shared)
{
	t_philo		philos[shared->nb_philo];
	pthread_t	watcher;
	int			i, j;

	i = 0;
	while (i < shared->nb_philo)
	{
		init_philo(&philos[i], shared, i);
		if (pthread_create(&philos[i].th, NULL, &philo_routine, (void *)&philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&watcher, NULL, &watcher_routine, (void *)philos))
		return (1);
	j = 0;
	while (j < shared->nb_philo)
	{
		if (pthread_join(philos[j].th, NULL))
			return (1);
		j++;
	}
	pthread_join(watcher, NULL);
	return (0);
}
