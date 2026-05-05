/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:26:56 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/05 18:07:58 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *p, char *s)
{
	pthread_mutex_lock(&p->shared->print);
	pthread_mutex_lock(&p->shared->flag);
	if (p->shared->stop_flag)
	{
		pthread_mutex_unlock(&p->shared->flag);
		pthread_mutex_unlock(&p->shared->print);
		return ;
	}
	pthread_mutex_unlock(&p->shared->flag);
	printf("%lld %d %s\n", get_elapsed_time(p), p->id, s);
	if (p->status == DIED)
		flag_up(p);
	pthread_mutex_unlock(&p->shared->print);
}

void	eating(t_philo *p)
{
	p->status = EATING;
	print_status(p, "is eating");
	pthread_mutex_lock(&p->meal_log);
	p->last_meal_time = get_elapsed_time(p);
	pthread_mutex_unlock(&p->meal_log);
	usleep(p->shared->time_to_eat * 1000);
	pthread_mutex_lock(&p->meal_log);
	p->last_meal_time = get_elapsed_time(p);
	pthread_mutex_unlock(&p->meal_log);
	p->nb_to_eat++;
}

void	sleeping(t_philo *p)
{
	p->status = SLEEPING;
	print_status(p, "is sleeping");
	usleep(p->shared->time_to_sleep * 1000);
}

void	thinking(t_philo *p)
{
	p->status = THINKING;
	print_status(p, "is thinking");
}

void	died(t_philo *p)
{
	p->status = DIED;
	print_status(p, "died");
}
