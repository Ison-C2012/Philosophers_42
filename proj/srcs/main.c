/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:00:12 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/07 00:36:43 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_args(t_arg *args, char **av)
{
	if (is_numbers(&av[1]))
		return (EXIT_FAILURE);
	args->nb_philo = ft_atoi(av[0]);
	args->time_to_die = ft_atoi(av[1]);
	args->time_to_eat = ft_atoi(av[2]);
	args->time_to_sleep = ft_atoi(av[3]);
	if (av[4] == NULL)
		args->nb_must_eat = 0;
	else
		args->nb_must_eat = ft_atoi(av[4]);
	if (is_valid_args(args))
		return (EXIT_FAILURE);
	args->time_of_beginning = get_time_ms();
	return (EXIT_SUCCESS);
}

int	init_shared(t_shared *shared, int nb)
{
	shared->stop_flag = 0;
	shared->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * nb);
	if (shared->forks == NULL)
		return (EXIT_FAILURE);
	if (init_mutexes(shared->forks, nb))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&shared->flag, NULL))
	{
		destroy_mutexes(shared->forks, nb);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&shared->print, NULL))
	{
		destroy_mutexes(shared->forks, nb);
		pthread_mutex_destroy(&shared->flag);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	clean_shared(t_shared *shared, int nb)
{
	if (destroy_mutexes(shared->forks, nb))
		return (EXIT_FAILURE);
	if (pthread_mutex_destroy(&shared->flag))
		return (EXIT_FAILURE);
	if (pthread_mutex_destroy(&shared->print))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_arg		args;
	t_shared	shared;

	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	if (get_args(&args, &argv[1]))
		return (EXIT_FAILURE);
	if (init_shared(&shared, args.nb_philo))
		return (EXIT_FAILURE);
	if (philo(&shared, &args))
		return (EXIT_FAILURE);
	if (clean_shared(&shared, args.nb_philo))
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
