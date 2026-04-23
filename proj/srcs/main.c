/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:00:12 by keitotak          #+#    #+#             */
/*   Updated: 2026/04/23 23:21:27 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_fork(pthread_mutex_t *fork, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	return (0);
}

int	clean_fork(pthread_mutex_t *forks, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	return (0);
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
		return (1);
	shared->forks = \
		(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * shared->nb_philo);
	init_fork(shared->forks, shared->nb_philo);
	shared->time_of_beginning = get_time_ms();
	shared->stop_flag = 0;
	pthread_mutex_init(&shared->flag, NULL);
	return (0);
}

void	print_shared(t_shared *shared)
{
	printf("number_of_philosophers=%d\n", shared->nb_philo);
	printf("time_to_die=%d\n", shared->time_to_die);
	printf("time_to_eat=%d\n", shared->time_to_eat);
	printf("time_to_sleep=%d\n", shared->time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat=%d\n", shared->nb_must_eat);
}

int	main(int argc, char **argv)
{
	t_shared	shared;

	if (argc != 5 && argc != 6)
		return (1);
	if (init_shared(&shared, &argv[1]))
		return (1);
	print_shared(&shared);
	if (philo(&shared))
		return (1);
	clean_fork(shared.forks, shared.nb_philo);
	free(shared.forks);
	pthread_mutex_destroy(&shared.flag);
	return (0);
}

/*signal function for Ctrl+C/Ctrl+D to prevent from memory leaks*/
