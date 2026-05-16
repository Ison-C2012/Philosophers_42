/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 10:32:56 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/16 10:33:07 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_even_routine(t_philo *philo)
{
	if (philo->id % 2)
		usleep(400);
	while (!check_stop(philo))
	{
		thinking(philo);
		take_forks(philo);
		if (check_stop(philo))
		{
			put_forks(philo);
			break ;
		}
		eating(philo);
		put_forks(philo);
		sleeping(philo);
	}
	return (NULL);
}

void	*philo_odd_routine(t_philo *philo)
{
	while (!check_stop(philo))
	{
		thinking(philo);
		take_forks(philo);
		if (check_stop(philo))
		{
			put_forks(philo);
			break ;
		}
		eating(philo);
		put_forks(philo);
		sleeping(philo);
	}
	return (NULL);
}

void	*philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->shared->nb_philo == 1)
		return (solo_philo(philo));
	set_start(philo);
	if (philo->shared->nb_philo % 2 == 0)
		return (philo_even_routine(philo));
	else
		return (philo_odd_routine(philo));
}
