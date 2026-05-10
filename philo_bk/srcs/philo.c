/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:36:00 by by keitotak       #+#    #+#             */
/*   Updated: 2026/05/10 20:35:03 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *philos, t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].status = THINKING;
		philos[i].shared = shared;
		philos[i].left_fork = &shared->forks[i];
		if (i > 0)
			philos[i].right_fork = &shared->forks[i - 1];
		else
			philos[i].right_fork = &shared->forks[shared->nb_philo - 1];
		philos[i].nb_to_eat = 0;
		philos[i].last_meal_time = get_elapsed_time(philos);
		if (pthread_mutex_init(&philos[i].meal_mutex, NULL))
		{
			destroy_mutex_philo(philos, i);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	join_philo(t_philo *philos, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (pthread_join(philos[i].th, NULL))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	create_philo(t_philo *philos, t_shared *shared)
{
	int	i;

	if (init_philo(philos, shared))
		return (EXIT_FAILURE);
	i = 0;
	while (i < shared->nb_philo)
	{
		if (pthread_create(&philos[i].th, NULL, &philo_routine,
				(void *)&philos[i]))
		{
			join_philo(philos, i);
			destroy_mutex_philo(philos, shared->nb_philo);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	clean_philo(t_philo *philos, int nb)
{
	if (join_philo(philos, nb))
	{
		destroy_mutex_philo(philos, nb);
		free(philos);
		return (EXIT_FAILURE);
	}
	destroy_mutex_philo(philos, nb);
	free(philos);
	return (EXIT_SUCCESS);
}

int	philo(t_shared *shared)
{
	t_philo		*philos;

	philos = (t_philo *)malloc(sizeof(t_philo) * shared->nb_philo);
	if (philos == NULL)
		return (EXIT_FAILURE);
	if (create_philo(philos, shared))
	{
		free(philos);
		return (EXIT_FAILURE);
	}
	if (waiter(philos))
	{
		join_philo(philos, shared->nb_philo);
		destroy_mutex_philo(philos, shared->nb_philo);
		free(philos);
		return (EXIT_FAILURE);
	}
	if (clean_philo(philos, shared->nb_philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
