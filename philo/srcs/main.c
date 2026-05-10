/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:00:12 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/10 19:48:36 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutex(pthread_mutex_t *mutex, int i)
{
	while (i--)
		pthread_mutex_destroy(&mutex[i]);
	return (EXIT_SUCCESS);
}

int	init_mutex(t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->nb_philo)
	{
		if (pthread_mutex_init(&shared->forks[i], NULL))
		{
			destroy_mutex(shared->forks, i);
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (pthread_mutex_init(&shared->flag, NULL))
	{
		destroy_mutex(shared->forks, i);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&shared->print, NULL))
	{
		destroy_mutex(shared->forks, i);
		pthread_mutex_destroy(&shared->print);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_shared(t_shared *shared, char **av)
{
	if (is_numbers(&av[1]))
		return (1);
	shared->nb_philo = ft_atoi(av[0]);
	shared->time_to_die = ft_atoi(av[1]);
	shared->time_to_eat = ft_atoi(av[2]);
	shared->time_to_sleep = ft_atoi(av[3]);
	if (av[4] == NULL)
		shared->nb_must_eat = 0;
	else
		shared->nb_must_eat = ft_atoi(av[4]);
	if (valid_value(shared))
		return (EXIT_FAILURE);
	shared->time_of_beginning = get_time_ms();
	shared->stop_flag = 0;
	shared->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * shared->nb_philo);
	if (shared->forks == NULL)
		return (EXIT_FAILURE);
	if (init_mutex(shared))
	{
		free(shared->forks);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	clean_shared(t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->nb_philo)
	{
		if (pthread_mutex_destroy(&shared->forks[i]))
			return (EXIT_FAILURE);
		i++;
	}
	free(shared->forks);
	if (pthread_mutex_destroy(&shared->flag))
		return (EXIT_FAILURE);
	if (pthread_mutex_destroy(&shared->print))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_shared	shared;

	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	if (init_shared(&shared, &argv[1]))
		return (EXIT_FAILURE);
	if (philo(&shared))
		return (EXIT_FAILURE);
	if (clean_shared(&shared))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
void	print_shared(t_shared *shared)
{
	printf("number_of_philosophers=%d\n", shared->nb_philo);
	printf("time_to_die=%d\n", shared->time_to_die);
	printf("time_to_eat=%d\n", shared->time_to_eat);
	printf("time_to_sleep=%d\n", shared->time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat=%d\n",
		shared->nb_must_eat);
}
*/

/*signal function for Ctrl+C/Ctrl+D to prevent from memory leaks*/
