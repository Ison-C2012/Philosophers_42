/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 17:49:52 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/25 21:30:57 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutex_philo(t_philo *philos, int i)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	while (i--)
	{
		if (pthread_mutex_destroy(&philos[i].meal_nb))
			exit_code = EXIT_FAILURE;
		if (pthread_mutex_destroy(&philos[i].meal_time))
			exit_code = EXIT_FAILURE;
	}
	return (exit_code);
}

int	join_philo(t_philo *philos, int nb)
{
	int	i;
	int	exit_code;

	i = 0;
	exit_code = EXIT_SUCCESS;
	while (i < nb)
	{
		if (pthread_join(philos[i].th, NULL))
			exit_code = EXIT_FAILURE;
		i++;
	}
	return (exit_code);
}
