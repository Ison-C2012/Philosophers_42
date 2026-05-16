/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:00:12 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/16 10:30:54 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_shared(t_shared *shared, char **av)
{
	if (is_numbers(&av[1]))
		return (err_msg(), EXIT_FAILURE);
	shared->nb_philo = ft_atoi(av[0]);
	shared->time_to_die = (long long) ft_atoi(av[1]) * 1000;
	shared->time_to_eat = (long long) ft_atoi(av[2]) * 1000;
	shared->time_to_sleep = (long long) ft_atoi(av[3]) * 1000;
	if (av[4] == NULL)
		shared->nb_must_eat = 0;
	else
		shared->nb_must_eat = ft_atoi(av[4]);
	if (valid_value(shared))
		return (err_msg(), EXIT_FAILURE);
	shared->time_of_beginning = get_time_ms();
	shared->thread_created = 0;
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
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (destroy_mutex(shared->forks, shared->nb_philo))
		exit_code = EXIT_FAILURE;
	free(shared->forks);
	if (pthread_mutex_destroy(&shared->start))
		exit_code = EXIT_FAILURE;
	if (pthread_mutex_destroy(&shared->flag))
		exit_code = EXIT_FAILURE;
	if (pthread_mutex_destroy(&shared->print))
		exit_code = EXIT_FAILURE;
	return (exit_code);
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

//	print_shared(&shared);
/*signal function for Ctrl+C/Ctrl+D to prevent from memory leaks*/
