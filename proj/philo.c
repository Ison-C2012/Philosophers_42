/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Creatinged: 2026/04/13 17:36:01 by keitotak          #+#    #+#             */
/*   Updated: 2026/04/19 15:15:28 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	thinking(t_philo *p)
{
	printf("%d is thinking\n", p->id);
//	usleep(1000);
}

void	pick_up_left_right(t_philo *p)
{
	pthread_mutex_lock(&p->left_fork);
	printf("%d has taken a fork\n", p->id);
	pthread_mutex_lock(&p->right_fork);
	printf("%d has taken a fork\n", p->id);
}

void	pick_up_right_left(t_philo *p)
{
	pthread_mutex_lock(&p->right_fork);
	printf("%d has taken a fork\n", p->id);
	pthread_mutex_lock(&p->left_fork);
	printf("%d has taken a fork\n", p->id);
}

void	eating(t_philo *p)
{
	printf("%d is eating spaghetti.\n", p->id);
	usleep(p->shared->time_to_eat * 1000);
}

void	put_down_left_right(t_philo *p)
{
	pthread_mutex_unlock(&p->left_fork);
	printf("%d has put down a fork\n", p->id);
	pthread_mutex_unlock(&p->right_fork);
	printf("%d has put down a fork\n", p->id);
}

void	put_down_right_left(t_philo *p)
{
	pthread_mutex_unlock(&p->right_fork);
	printf("%d has put down a fork\n", p->id);
	pthread_mutex_unlock(&p->left_fork);
	printf("%d has put down a fork\n", p->id);
}

void	sleeping(t_philo *p)
{
	printf("%d is sleeping.\n", p->id);
	usleep(p->shared->time_to_sleep * 1000);
}

void	*philo_routine(void *p)
{
	t_philo	*philo = (t_philo *)p;

	while (1)
	{
		thinking(philo);
		if (philo->id % 2 == 0)
			pick_up_left_right(philo);
		else
			pick_up_right_left(philo);
		eating(philo);
		if (philo->id % 2 == 0)
			put_down_left_right(philo);
		else
			put_down_right_left(philo);
		sleeping(philo);
	}
	return (NULL);
}

int	philo(t_shared *shared)
{
	t_philo	philos[shared->nb_philo];
	int			i, j;

	i = 0;
	while (i < shared->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].shared = shared;
		philos[i].left_fork = shared->forks[i];
		philos[i].right_fork = i > 0 ? shared->forks[i - 1] : shared->forks[shared->nb_philo - 1];
		if (pthread_create(&philos[i].th, NULL, &philo_routine, (void *)&philos[i]))
			return (1);
		i++;
	}
	j = 0;
	while (j < shared->nb_philo)
	{
		if (pthread_join(philos[j].th, NULL))
			return (1);
		j++;
	}
	return (0);
}
