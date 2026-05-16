/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 10:32:56 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/16 12:08:02 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_even_routine(t_philo *philo)
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

static void	*philo_odd_routine(t_philo *philo)
{
	while (!check_stop(philo))
	{
		thinking(philo);
		wait(philo);
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

static void	set_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->start);
	philo->shared->thread_created++;
	if (philo->id == philo->shared->nb_philo)
		philo->shared->time_of_beginning = get_time_ms();
	pthread_mutex_unlock(&philo->shared->start);
	while (1)
	{
		pthread_mutex_lock(&philo->shared->start);
		if (philo->shared->thread_created == philo->shared->nb_philo)
			break ;
		pthread_mutex_unlock(&philo->shared->start);
		usleep(100);
	}
	pthread_mutex_unlock(&philo->shared->start);
}

static void	*philo_solo_routine(t_philo *philo)
{
	print_status(philo, "is thinking");
	print_status(philo, "has taken a fork");
	while (1)
	{
		if (check_stop(philo))
			break ;
		usleep(1000);
	}
	return (NULL);
}

void	*philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->shared->nb_philo == 1)
		return (philo_solo_routine(philo));
	set_start(philo);
	if (philo->shared->nb_philo % 2)
		return (philo_odd_routine(philo));
	else
		return (philo_even_routine(philo));
}
