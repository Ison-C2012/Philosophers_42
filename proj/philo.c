/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Creatinged: 2026/04/13 17:36:01 by keitotak       #+#    #+#             */
/*   Updated: 2026/04/20 16:59:36 by keitotak         ###   ########.fr       */
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

int	check_starvation(t_philo *p)
{
	long long	lmt;

	pthread_mutex_lock(p->meal_log);
	lmt = p->last_meal_time;
	pthread_mutex_unlock(p->meal_log);
	return (get_elapsed_time(p) - lmt >= p->shared->time_to_die);
}

void	*watcher_routine(void *p)
{
	t_philo	**philos = (t_philo **)p;
	int		i;

	while (1)
	{
		i = 0;
		while (i < philos[i]->shared->nb_philo)
		{
			if (check_starvation(philos[i]))
			{
				died(philos[i]);
				break ;
			}
			i++;
		}
	}
	return (NULL);
}

int	philo(t_shared *shared)
{
	t_philo		philos[shared->nb_philo];
	pthread_t	watcher;
	int			i, j;

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
	if (pthread_create(&watcher, NULL, &watcher_routine, (void *)&philos))
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
