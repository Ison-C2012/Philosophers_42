/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 21:58:38 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/20 23:01:18 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_a_fork(t_philo *p, int fork_nb)
{
	while (1)
	{
		pthread_mutex_lock(&p->shared->forks[fork_nb]);
		pthread_mutex_lock(&p->shared->fork_mutex[fork_nb]);
		if (p->shared->fork_status[fork_nb] == AVAILABLE)
			break ;
		pthread_mutex_unlock(&p->shared->fork_mutex[fork_nb]);
		pthread_mutex_unlock(&p->shared->forks[fork_nb]);
		usleep(1000);
	}
	p->shared->fork_status[fork_nb] = TAKEN;
	pthread_mutex_unlock(&p->shared->fork_mutex[fork_nb]);
	print_status(p, "has taken a fork");
}

int	left_fork_nb(t_philo *p)
{
	return (p->id % p->shared->nb_philo);
}

int	right_fork_nb(t_philo *p)
{
	return (p->id - 1);
}

void	take_forks(t_philo *p)
{
	if (p->id == 1)
	{
		take_a_fork(p, left_fork_nb(p));
		take_a_fork(p, right_fork_nb(p));
	}
	else
	{
		take_a_fork(p, right_fork_nb(p));
		take_a_fork(p, left_fork_nb(p));
	}
}

void	put_forks(t_philo *p)
{
	pthread_mutex_t	*fork_mutex;
	int				fork_nb;

	fork_mutex = p->shared->fork_mutex;
	fork_nb = right_fork_nb(p);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_lock(&fork_mutex[fork_nb]);
	p->shared->fork_status[fork_nb] = AVAILABLE;
	pthread_mutex_unlock(&fork_mutex[fork_nb]);
	fork_nb = left_fork_nb(p);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_lock(&fork_mutex[fork_nb]);
	p->shared->fork_status[fork_nb] = AVAILABLE;
	pthread_mutex_unlock(&fork_mutex[fork_nb]);
}
