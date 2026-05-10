/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 21:58:38 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/10 21:55:02 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *p)
{
	/*if (p->id % 2)
	{
		pthread_mutex_lock(p->left_fork);
		print_status(p, "has taken a fork");
		pthread_mutex_lock(p->right_fork);
		print_status(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(p->right_fork);
		print_status(p, "has taken a fork");
		pthread_mutex_lock(p->left_fork);
		print_status(p, "has taken a fork");
	}*/
	pthread_mutex_lock(p->left_fork);
	print_status(p, "has taken a fork");
	pthread_mutex_lock(p->right_fork);
	print_status(p, "has taken a fork");
}

void	put_forks(t_philo *p)
{
	/*if (p->id % 2)
	{
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
	}
	else
	{
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
	}*/
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}
