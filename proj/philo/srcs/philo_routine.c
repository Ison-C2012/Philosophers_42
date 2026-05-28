/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 10:32:56 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/28 19:52:30 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_stop(t_shared *shared)
{
	pthread_mutex_lock(&shared->flag);
	if (shared->stop_flag)
	{
		pthread_mutex_unlock(&shared->flag);
		return (true);
	}
	pthread_mutex_unlock(&shared->flag);
	return (false);
}

static void	*philo_solo_routine(t_philo *philo)
{
	print_status(philo, "is thinking");
	print_status(philo, "has taken a fork");
	while (1)
	{
		if (check_stop(philo->shared))
			break ;
		usleep(1000);
	}
	return (NULL);
}

static void	set_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->start);
	philo->shared->created_thread_nb++;
	pthread_mutex_unlock(&philo->shared->start);
	while (1)
	{
		pthread_mutex_lock(&philo->shared->start);
		if (philo->shared->created_thread_nb == philo->shared->nb_philo)
		{
			if (philo->id == 1)
			{
				philo->shared->time_of_beginning = get_time_us();
				philo->shared->start_flag = 1;
			}
		}
		if (philo->shared->start_flag)
			break ;
		pthread_mutex_unlock(&philo->shared->start);
		usleep(10);
	}
	pthread_mutex_unlock(&philo->shared->start);
}

static void	first_thinking(t_philo *philo, t_shared *shared)
{
	if (philo->id % 2)
	{
		if (shared->time_to_die <= shared->time_to_eat)
			thinking(philo, shared->time_to_die);
		else if (shared->time_to_die <= shared->time_to_eat * 2)
		{
			if (shared->nb_philo % 2 && philo->id == 1)
				thinking(philo, shared->time_to_die);
			else
				thinking(philo, shared->time_to_eat);
		}
		else
		{
			if (shared->nb_philo % 2 && philo->id == 1)
				thinking(philo, shared->time_to_eat * 2);
			else
				thinking(philo, shared->time_to_eat);
		}
	}
}

void	*philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->shared->nb_philo == 1)
		return (philo_solo_routine(philo));
	set_start(philo);
	first_thinking(philo, philo->shared);
	while (!check_stop(philo->shared))
	{
		take_forks(philo);
		if (check_stop(philo->shared))
		{
			put_forks(philo);
			break ;
		}
		eating(philo);
		put_forks(philo);
		sleeping(philo);
		thinking(philo, philo->shared->time_to_think);
	}
	return (NULL);
}
