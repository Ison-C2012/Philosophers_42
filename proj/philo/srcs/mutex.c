/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 10:24:16 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/16 10:29:57 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutex(pthread_mutex_t *mutex, int i)
{
	while (i--)
		pthread_mutex_destroy(&mutex[i]);
	return (EXIT_SUCCESS);
}

static int	init_forks(t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->nb_philo)
	{
		if (pthread_mutex_init(&shared->forks[i], NULL))
		{
			destroy_mutex(shared->forks, i);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_mutex(t_shared *shared)
{
	if (init_forks(shared))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&shared->start, NULL))
	{
		destroy_mutex(shared->forks, shared->nb_philo);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&shared->flag, NULL))
	{
		destroy_mutex(shared->forks, shared->nb_philo);
		pthread_mutex_destroy(&shared->start);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&shared->print, NULL))
	{
		destroy_mutex(shared->forks, shared->nb_philo);
		pthread_mutex_destroy(&shared->start);
		pthread_mutex_destroy(&shared->print);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
