/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 10:32:56 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/21 18:29:18 by keitotak         ###   ########.fr       */
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

static void	set_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->start);
	philo->shared->thread_created++;
	pthread_mutex_unlock(&philo->shared->start);
	while (1)
	{
		pthread_mutex_lock(&philo->shared->start);
		if (philo->shared->thread_created == philo->shared->nb_philo)
		{
			if (philo->id == philo->shared->nb_philo)
				philo->shared->time_of_beginning = get_time_ms();
			break ;
		}
		pthread_mutex_unlock(&philo->shared->start);
		usleep(10);
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
