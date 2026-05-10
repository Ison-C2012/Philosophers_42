/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:02:51 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/06 23:32:04 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

int	is_numbers(char **av)
{
	while (*av)
	{
		if (is_number(*av))
			return (1);
		av++;
	}
	return (0);
}

int	is_valid_args(t_arg *args)
{
	if (args->nb_philo <= 0)
		return (EXIT_FAILURE);
	if (args->time_to_die <= 0)
		return (EXIT_FAILURE);
	if (args->time_to_eat <= 0)
		return (EXIT_FAILURE);
	if (args->time_to_sleep <= 0)
		return (EXIT_FAILURE);
	if (args->nb_must_eat < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
