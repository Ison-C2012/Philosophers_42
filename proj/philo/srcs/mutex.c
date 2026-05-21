/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 10:24:16 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/21 18:28:51 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutex(pthread_mutex_t *mutex, int i)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	while (i--)
		if (pthread_mutex_destroy(&mutex[i]))
			exit_code = EXIT_FAILURE;
	return (exit_code);
}

static int	init_forks_mutex(pthread_mutex_t *forks, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			destroy_mutex(forks, i);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_mutex(t_shared *shared)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (init_forks_mutex(shared->forks, shared->nb_philo))
		exit_code = EXIT_FAILURE;
	if (init_forks_mutex(shared->fork_mutex, shared->nb_philo))
		exit_code = EXIT_FAILURE;
	if (pthread_mutex_init(&shared->start, NULL))
		exit_code = EXIT_FAILURE;
	if (pthread_mutex_init(&shared->flag, NULL))
		exit_code = EXIT_FAILURE;
	if (pthread_mutex_init(&shared->print, NULL))
		exit_code = EXIT_FAILURE;
	if (exit_code == EXIT_FAILURE)
	{
		destroy_mutex(shared->forks, shared->nb_philo);
		destroy_mutex(shared->fork_mutex, shared->nb_philo);
		pthread_mutex_destroy(&shared->start);
		pthread_mutex_destroy(&shared->print);
	}
	return (exit_code);
}
