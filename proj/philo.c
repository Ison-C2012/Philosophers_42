/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:36:01 by keitotak          #+#    #+#             */
/*   Updated: 2026/04/13 17:55:14 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	*work(void *arg)
{
	(void)arg;
	printf("hello.\n");
	return (NULL);
}

int	philo(t_val *vals)
{
	pthread_t	philo[vals->nb_philo];
	pthread_mutex_t	mutex;
	int	i, j;

	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < vals->nb_philo)
	{
		if (pthread_create(&philo[i], NULL, &work, NULL))
			return (1);
		i++;
	}
	j = 0;
	while (j < vals->nb_philo)
	{
		if (pthread_join(philo[j], NULL))
			return (1);
		j++;
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}
