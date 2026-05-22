/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 21:58:38 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/23 07:00:04 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_a_fork(t_philo *p, int fork_nb)
{
	pthread_mutex_lock(&p->shared->forks[fork_nb]);
	print_status(p, "has taken a fork");
}

void	take_forks(t_philo *p)
{
	int	right_fork_nb;
	int	left_fork_nb;

	right_fork_nb = p->id - 1;
	left_fork_nb = p->id % p->shared->nb_philo;
	if (p->id == 1)
	{
		take_a_fork(p, left_fork_nb);
		take_a_fork(p, right_fork_nb);
	}
	else
	{
		take_a_fork(p, right_fork_nb);
		take_a_fork(p, left_fork_nb);
	}
}

void	put_forks(t_philo *p)
{
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
}
