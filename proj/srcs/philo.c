/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:36:00 by by keitotak       #+#    #+#             */
/*   Updated: 2026/05/05 21:03:55 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2)
		usleep(1000);
	while (1)
	{
		if (check_stop(philo))
			break ;
		thinking(philo);
		take_forks(philo);
		if (check_stop(philo))
		{
			put_forks(philo);
			break ;
		}
		eating(philo);
		put_forks(philo);
		if (check_stop(philo))
			break ;
		sleeping(philo);
	}
	return (NULL);
}

void	init_philo(t_philo *philo, t_shared *shared, int i)
{
	philo->id = i + 1;
	philo->status = THINKING;
	philo->shared = shared;
	philo->left_fork = &shared->forks[i];
	if (i > 0)
		philo->right_fork = &shared->forks[i - 1];
	else
		philo->right_fork = &shared->forks[shared->nb_philo - 1];
	philo->nb_to_eat = 0;
	philo->last_meal_time = get_elapsed_time(philo);
	pthread_mutex_init(&philo->meal_log, NULL);
}

int	create_philo(t_philo *philos, t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->nb_philo)
	{
		init_philo(&philos[i], shared, i);
		if (pthread_create(&philos[i].th, NULL, &philo_routine,
				(void *)&philos[i]))
			return (1);
		i++;
	}
	return (0);
}

int	remove_philo(t_philo *philos, t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->nb_philo)
	{
		if (pthread_join(philos[i].th, NULL))
			return (1);
		pthread_mutex_destroy(&philos[i].meal_log);
		i++;
	}
	return (0);
}

int	philo(t_shared *shared)
{
	t_philo		*philos;
	pthread_t	waiter;

	philos = (t_philo *)malloc(sizeof(t_philo) * shared->nb_philo);
	if (!philos)
		return (1);
	if (create_philo(philos, shared))
		return (1);
	if (pthread_create(&waiter, NULL, &waiter_routine, (void *)philos))
		return (1);
	if (pthread_join(waiter, NULL))
		return (1);
	if (remove_philo(philos, shared))
		return (1);
	free(philos);
	return (0);
}
