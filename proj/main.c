/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:00:12 by keitotak          #+#    #+#             */
/*   Updated: 2026/04/13 17:35:41 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_val(t_val *val, char **av)
{
	if (is_numbers(&av[1]))
		return (1);
	val->nb_philo = ft_atoi(av[0]);
	val->tm_die = ft_atoi(av[1]);
	val->tm_eat = ft_atoi(av[2]);
	val->tm_sleep = ft_atoi(av[3]);
	if (av[4] == NULL)
		val->nb_eat = 0;
	else
		val->nb_eat = ft_atoi(av[4]);
	if (valid_value(val))
		return (1);
	return (0);
}

void	print_vals(t_val *vals)
{
	printf("number_of_philosophers=%d\n", vals->nb_philo);
	printf("time_to_die=%d\n", vals->tm_die);
	printf("time_to_eat=%d\n", vals->tm_eat);
	printf("time_to_sleep=%d\n", vals->tm_sleep);
	printf("number_of_times_each_philosopher_must_eat=%d\n", vals->nb_eat);
}

int	main(int argc, char **argv)
{
	t_val	vals;

	if (argc != 5 && argc != 6)
		return (1);
	if (init_val(&vals, &argv[1]))
		return (1);
	print_vals(&vals);
	philo(&vals);
	return (0);
}
