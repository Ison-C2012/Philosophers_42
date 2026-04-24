/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:36:00 by by keitotak       #+#    #+#             */
/*   Updated: 2026/04/24 13:29:55 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stop(t_philo *p)
{
	pthread_mutex_lock(&p->shared->flag);
	if (p->shared->stop_flag)
	{
		pthread_mutex_unlock(&p->shared->flag);
		return (1);
	}	
	pthread_mutex_unlock(&p->shared->flag);
	return (0);
}

void	*philo_routine(void *p)
{
	t_philo	*philo = (t_philo *)p;

	while (1)
	{
		if (check_stop(philo))
			break ;
		thinking(philo);
		take_forks(philo);
		if (check_stop(philo))
		{
			put_forks(philo);
			break ;
		}
		eating(philo);
		put_forks(philo);
		if (check_stop(philo))
			break ;
		sleeping(philo);
	}
	return (NULL);
}

int	init_philo(t_philo *philo, t_shared *shared, int i)
{
	philo->id = i + 1;
	philo->shared = shared;
	philo->last_meal_time = get_elapsed_time(philo);
	philo->left_fork = &shared->forks[i];
	if (i > 0)
		philo->right_fork = &shared->forks[i - 1];
	else
		philo->right_fork = &shared->forks[shared->nb_philo - 1];
	pthread_mutex_init(&philo->meal_log, NULL);
	philo->nb_to_eat = 0;
	return (0);
}

int	philo(t_shared *shared)
{
	t_philo		philos[shared->nb_philo];
	pthread_t	waiter;
	int			i, j;

	i = 0;
	while (i < shared->nb_philo)
	{
		init_philo(&philos[i], shared, i);
		if (pthread_create(&philos[i].th, NULL, &philo_routine, (void *)&philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&waiter, NULL, &waiter_routine, (void *)philos))
		return (1);
	pthread_join(waiter, NULL);
	j = 0;
	while (j < shared->nb_philo)
	{
		if (pthread_join(philos[j].th, NULL))
			return (1);
		pthread_mutex_destroy(&philos[j].meal_log);
		j++;
	}
	return (0);
}
