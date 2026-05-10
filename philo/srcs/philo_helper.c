/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 17:49:52 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/11 02:14:12 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_stop(t_philo *p)
{
	pthread_mutex_lock(&p->shared->flag);
	if (p->shared->stop_flag)
	{
		pthread_mutex_unlock(&p->shared->flag);
		return (true);
	}
	pthread_mutex_unlock(&p->shared->flag);
	return (false);
}

void	*solo_philo(t_philo *philo)
{
	print_status(philo, "is thinking");
	print_status(philo, "has taken a fork");
	while (1)
	{
		if (check_stop(philo))
			break ;
	}
	return (NULL);
}

int	destroy_mutex_philo(t_philo *philos, int i)
{
	while (i--)
	{
		if (pthread_mutex_destroy(&philos[i].meal_mutex))
			return (EXIT_FAILURE);
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
