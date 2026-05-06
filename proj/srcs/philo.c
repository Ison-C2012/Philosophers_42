/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:36:00 by by keitotak       #+#    #+#             */
/*   Updated: 2026/05/06 13:44:20 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->shared->nb_philo == 1)
		return (solo_philo(philo));
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

int	init_philo(t_philo *philo, t_shared *shared, int i)
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
	if (pthread_mutex_init(&philo->meal_log, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	create_philo(t_philo *philos, t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->nb_philo)
	{
		if (init_philo(&philos[i], shared, i))
			return (EXIT_FAILURE);
		if (pthread_create(&philos[i].th, NULL, &philo_routine,
				(void *)&philos[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	remove_philo(t_philo *philos, t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->nb_philo)
	{
		if (pthread_join(philos[i].th, NULL))
			return (EXIT_FAILURE);
		if (pthread_mutex_destroy(&philos[i].meal_log))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	philo(t_shared *shared)
{
	t_philo		*philos;
	pthread_t	waiter;

	philos = (t_philo *)malloc(sizeof(t_philo) * shared->nb_philo);
	if (philos == NULL)
		return (EXIT_FAILURE);
	if (create_philo(philos, shared))
		return (EXIT_FAILURE);
	if (pthread_create(&waiter, NULL, &waiter_routine, (void *)philos))
		return (EXIT_FAILURE);
	if (pthread_join(waiter, NULL))
		return (EXIT_FAILURE);
	if (remove_philo(philos, shared))
		return (EXIT_FAILURE);
	free(philos);
	return (EXIT_SUCCESS);
}
