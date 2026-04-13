/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:03:33 by keitotak          #+#    #+#             */
/*   Updated: 2026/04/03 18:07:35 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <limits.h>

typedef struct	s_val
{
	int	nb_philo;
	int	tm_die;
	int	tm_eat;
	int	tm_sleep;
	int	nb_eat;
}	t_val;

int	ft_atoi(const char *nptr);
int	ft_isdigit(char c);
int	is_numbers(char **av);
int	valid_value(t_val *val);

#endif
