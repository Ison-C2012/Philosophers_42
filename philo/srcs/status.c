/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:26:56 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/23 06:59:14 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define BUFFER_TIME 10000

void	eating(t_philo *p)
{
	print_status(p, "is eating");
	pthread_mutex_lock(&p->meal_mutex);
	p->last_meal_time = get_elapsed_time(p->shared);
	usleep(p->shared->time_to_eat);
	p->nb_to_eat++;
	pthread_mutex_unlock(&p->meal_mutex);
}

void	sleeping(t_philo *p)
{
	print_status(p, "is sleeping");
	usleep(p->shared->time_to_sleep);
}

void	thinking(t_philo *p, long long time)
{
	print_status(p, "is thinking");
	usleep(time - BUFFER_TIME);
}

void	died(t_philo *p)
{
	print_died(p, "died");
}
