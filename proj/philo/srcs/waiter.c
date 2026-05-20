/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:57:28 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/20 21:37:09 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_flag(t_shared *shared)
{
	pthread_mutex_lock(&shared->flag);
	shared->stop_flag = 1;
	pthread_mutex_unlock(&shared->flag);
}

static bool	check_starvation(t_philo *p)
{
	int	i;
	int	nb_philo;
	long long	pt;

	i = 0;
	nb_philo = p[0].shared->nb_philo;
	while (i < nb_philo)
	{
		pt = get_elapsed_time(p[i].shared);
		pthread_mutex_lock(&p[i].meal_mutex);
		if (pt - p[i].last_meal_time >= p->shared->time_to_die)
		{
			pthread_mutex_unlock(&p[i].meal_mutex);
			set_flag(p->shared);
			died(&p[i]);
			return (false);
		}
		pthread_mutex_unlock(&p[i].meal_mutex);
		i++;
	}
	return (true);
}

static bool	check_termination(t_philo *p)
{
	int	i;
	int	nb_philo;

	i = 0;
	nb_philo = p[0].shared->nb_philo;
	while (i < nb_philo)
	{
		pthread_mutex_lock(&p[i].meal_mutex);
		if (p[i].nb_to_eat < p->shared->nb_must_eat)
		{
			pthread_mutex_unlock(&p[i].meal_mutex);
			return (true);
		}
		pthread_mutex_unlock(&p[i].meal_mutex);
		i++;
	}
	set_flag(p->shared);
	return (false);
}

static void	*waiter_routine(void *p)
{
	t_philo	*philos;

	philos = (t_philo *)p;
	while ((check_starvation(philos)) && (check_termination(philos)))
		usleep(1000);
	return (NULL);
}

int	waiter(t_philo *philos)
{
	pthread_t	waiter;

	if (pthread_create(&waiter, NULL, &waiter_routine, (void *)philos))
		return (EXIT_FAILURE);
	if (pthread_join(waiter, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
