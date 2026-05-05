/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 17:49:52 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/05 21:06:38 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_stop(t_philo *p)
{
	pthread_mutex_lock(&p->shared->flag);
	if (p->shared->stop_flag)
	{
		pthread_mutex_unlock(&p->shared->flag);
		return (true);
	}
	pthread_mutex_unlock(&p->shared->flag);
	return (false);
}

void	take_forks(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	print_status(p, "has taken a fork");
	pthread_mutex_lock(p->right_fork);
	print_status(p, "has taken a fork");
}

void	put_forks(t_philo *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}
