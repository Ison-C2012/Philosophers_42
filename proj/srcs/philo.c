/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:36:00 by by keitotak       #+#    #+#             */
/*   Updated: 2026/05/07 14:59:15 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->shared->nb_philo == 1)
		return (solo_philo(philo));
	if (philo->id % 2)
		usleep(1000);
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

int	destroy_mutex_philo(t_philo *philos, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (pthread_mutex_destroy(&philos[i].eat))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_philo(t_philo *philos, t_shared *shared, t_arg *args, int i)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].status = THINKING;
		philos[i].shared = shared;
		philos[i].args = *args;
		philos[i].left_fork = &shared->forks[i];
		if (i > 0)
			philos[i].right_fork = &shared->forks[i - 1];
		else
			philos[i].right_fork = &shared->forks[shared.nb_philo - 1];
		philos[i].nb_to_eat = 0;
		philos[i].last_meal_time = get_elapsed_time(philo);
		if (pthread_mutex_init(&philos[i].eat, NULL))
		{
			destroy_mutex_philo(philos, i);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	remove_philo(t_philo *philos, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (pthread_join(philos[i].th, NULL))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	create_philo(t_philo *philos, t_shared *shared, t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		if (pthread_create(&philos[i].th, NULL, &philo_routine,
				(void *)&philos[i]))
		{
			destroy_mutex_philo(philos, i);
			remove_philo(philos, i);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	create_waiter(t_waiter *waiter, )

typedef struct s_waiter
{
	pthread_t	th;
	t_arg		args;
	t_shared	*shared;
	t_philo		*philos;
}	t_waiter;

int	init_waiter(t_waiter *waiter, t_shared *shared, t_arg *args)
{
	
}

int	philo(t_shared *shared, t_arg *args)
{
	t_philo		*philos;
	t_waiter	waiter;

	philos = (t_philo *)malloc(sizeof(t_philo) * args->nb_philo);
	if (philos == NULL)
		return (EXIT_FAILURE);
	if (init_philo(philos, shared, args))
		return (free(philos), EXIT_FAILURE);
	if (create_philo(philos, shared, args))
		return (free(philos), EXIT_FAILURE);
	if (pthread_create(&waiter, NULL, &waiter_routine, (void *)philos))
	if (pthread_join(waiter, NULL))
	init_waiter(&waiter, shared, args);
	if (destroy_mutex_philo(philos, args->nb_philo))
	if (remove_philo(philos, shared))
	free(philos);
	return (EXIT_SUCCESS);
}
