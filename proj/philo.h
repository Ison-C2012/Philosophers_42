/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:03:33 by keitotak          #+#    #+#             */
/*   Updated: 2026/04/14 11:28:14 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>

typedef struct	s_shared
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_must_eat;

	pthread_mutex_t	*forks;
}	t_shared;

int	ft_atoi(const char *nptr);
int	ft_isdigit(char c);
int	is_numbers(char **av);
int	valid_value(t_shared *shared);
int	philo(t_shared *shared);

#endif
