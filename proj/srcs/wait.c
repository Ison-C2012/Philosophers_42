/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:57:28 by keitotak          #+#    #+#             */
/*   Updated: 2026/04/24 00:45:13 by keitotak         ###   ########.fr       */
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

int	check_starvation(t_philo *p)
{
	long long	lmt;

	pthread_mutex_lock(&p->meal_log);
	lmt = p->last_meal_time;
	pthread_mutex_unlock(&p->meal_log);
	return (get_elapsed_time(p) - lmt >= p->shared->time_to_die);
}

void	died(t_philo *p)
{
	printf("%lld %d died\n", get_elapsed_time(p), p->id);
	pthread_mutex_lock(&p->shared->flag);
	p->shared->stop_flag = 1;
	pthread_mutex_unlock(&p->shared->flag);
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
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

