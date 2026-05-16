/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:57:28 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/16 15:08:34 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_flag(t_philo *p)
{
	pthread_mutex_lock(&p->shared->flag);
	p->shared->stop_flag = 1;
	pthread_mutex_unlock(&p->shared->flag);
}

static bool	check_starvation(t_philo *p)
{
	int	i;
	int	nb_philo;
	long long	pt;
	long long	lmt;

	i = 0;
	nb_philo = p[0].shared->nb_philo;
	while (i < nb_philo)
	{
		pt = get_elapsed_time(p[i].shared);
		pthread_mutex_lock(&p[i].meal_mutex);
		lmt = p->last_meal_time;
		pthread_mutex_unlock(&p[i].meal_mutex);
		if (pt - lmt >= p->shared->time_to_die)
			return (true);
		i++;
	}
	return (false);
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
			return (false);
		}
		pthread_mutex_unlock(&p[i].meal_mutex);
		i++;
	}
	return (true);
}

void	judge_who_eat(t_philo *philos)
{
	int	i;
	int	nb_philo;
	int	left_status;
	int	right_status;

	i = 0;
	nb_philo = p[0].shared->nb_philo;
	while (i < nb_philo)
	{
		pthread_mutex_lock(&p[i].status_mutex);
		left_status = philos[(i + 1) % nb_philo].status;
		if (i)
			right_status = philos[i - 1].status;
		else
			right_status = philos[nb_philo - 1].status;
		if (left_status != EATING && right_status != EATING)
		{
			pthread_mutex_unlock(&p[i].status_mutex);
			return (false);
		}
		pthread_mutex_unlock(&p[i].status_mutex);
		i++;
	}
}

static void	*waiter_routine(void *p)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)p;
	while (1)
	{
		i = 0;
		if (check_starvation(&philos[i]))
		{
			set_flag(p);
			died(&philos[i]);
			break ;
		}
		if (check_termination(philos))
		{
			set_flag(philos);
			break ;
		}
		judge_who_eat(philos);
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
