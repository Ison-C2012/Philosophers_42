/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:02:51 by keitotak          #+#    #+#             */
/*   Updated: 2026/04/14 11:26:49 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(char *str)
{
	if (*str == '-')
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

int	valid_value(t_shared *shared)
{
	if (shared->nb_philo < 0 || shared->time_to_die < 0 || shared->time_to_eat < 0\
		|| shared->time_to_sleep < 0 || shared->nb_must_eat < 0)
		return (1);
	return (0);
}
