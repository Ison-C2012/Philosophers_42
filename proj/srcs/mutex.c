/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 00:13:01 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/07 00:15:31 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutexes(pthread_mutex_t *mutexes, int tnd)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (pthread_mutex_destroy(&mutexes[i++]))
		{
			free(mutexes);
			return (EXIT_FAILURE);
		}
	}
	free(mutexes);
	return (EXIT_SUCCESS);
}

int	init_mutexes(pthread_mutex_t *mutexes, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (pthread_mutex_init(mutexes[i], NULL))
		{
			destroy_mutexes(mutexes, i);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
