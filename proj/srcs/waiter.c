/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:57:28 by keitotak          #+#    #+#             */
/*   Updated: 2026/04/24 13:26:41 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_starvation(t_philo *p)
{
	long long	lmt;

	pthread_mutex_lock(&p->meal_log);
	lmt = p->last_meal_time;
	pthread_mutex_unlock(&p->meal_log);
	return (get_elapsed_time(p) - lmt >= p->shared->time_to_die);
}

void	flag_up(t_philo *p)
{
	pthread_mutex_lock(&p->shared->flag);
	p->shared->stop_flag = 1;
	pthread_mutex_unlock(&p->shared->flag);
}

int	check_termination(t_philo *p)
{
	int	i;
	int		nb_philo;

	i = 0;
	nb_philo = p[0].shared->nb_philo;
	while (i < nb_philo)
	{
		if (p[i].nb_to_eat < p->shared->nb_must_eat)
			return (0);
		i++;
	}
	return (1);
}

void	*waiter_routine(void *p)
{
	t_philo	*philos = (t_philo *)p;
	int		i;
	int		nb_philo;

	nb_philo = philos[0].shared->nb_philo;
	while (1)
	{
		i = 0;
		while (i < nb_philo)
		{
			if (check_starvation(&philos[i]))
			{
				died(&philos[i]);
				flag_up(p);
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

