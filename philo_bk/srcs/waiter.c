/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:57:28 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/10 20:35:21 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	flag_up(t_philo *p)
{
	pthread_mutex_lock(&p->shared->flag);
	p->shared->stop_flag = 1;
	pthread_mutex_unlock(&p->shared->flag);
}

int	check_starvation(t_philo *p)
{
	long long	pt;
	long long	lmt;

	pt = get_elapsed_time(p);
	pthread_mutex_lock(&p->meal_mutex);
	lmt = p->last_meal_time;
	pthread_mutex_unlock(&p->meal_mutex);
	return (pt - lmt >= p->shared->time_to_die);
}

int	check_termination(t_philo *p)
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
			return (0);
		}
		pthread_mutex_unlock(&p[i].meal_mutex);
		i++;
	}
	return (1);
}

void	*waiter_routine(void *p)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)p;
	while (1)
	{
		i = 0;
		while (i < philos[0].shared->nb_philo)
		{
			if (check_starvation(&philos[i]))
			{
				died(&philos[i]);
				return (NULL);
			}
			i++;
		}
		if (check_termination(philos) && philos->shared->nb_must_eat)
		{
			flag_up(philos);
			return (NULL);
		}
		usleep(1000);
	}
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
