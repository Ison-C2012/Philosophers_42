/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:36:00 by by keitotak       #+#    #+#             */
/*   Updated: 2026/05/29 23:06:34 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	clean_philo(t_philo *philos, int nb)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (join_philo(philos, nb))
		exit_code = EXIT_FAILURE;
	if (destroy_mutex_philo(philos, nb))
		exit_code = EXIT_FAILURE;
	return (exit_code);
}

static int	init_philo(t_philo *philos, t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].shared = shared;
		philos[i].right_fork = &shared->forks[i];
		philos[i].left_fork = &shared->forks[(i + 1) % shared->nb_philo];
		philos[i].nb_eat = 0;
		philos[i].last_meal_time = get_elapsed_time(shared);
		if (pthread_mutex_init(&philos[i].meal_nb, NULL))
		{
			destroy_mutex_philo(philos, i);
			return (EXIT_FAILURE);
		}
		if (pthread_mutex_init(&philos[i].meal_time, NULL))
		{
			destroy_mutex_philo(philos, i);
			pthread_mutex_destroy(&philos[i].meal_nb);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	create_philo(t_philo *philos, t_shared *shared)
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
		clean_philo(philos, shared->nb_philo);
		free(philos);
		return (EXIT_FAILURE);
	}
	if (clean_philo(philos, shared->nb_philo))
	{
		free(philos);
		return (EXIT_FAILURE);
	}
	free(philos);
	return (EXIT_SUCCESS);
}
