/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:26:56 by keitotak          #+#    #+#             */
/*   Updated: 2026/04/20 16:36:37 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *p)
{
	printf("%lld %d is thinking\n", get_elapsed_time(p), p->id);
}

void	eating(t_philo *p)
{
	printf("%lld %d is eating\n", get_elapsed_time(p), p->id);
	usleep(p->shared->time_to_eat * 1000);
	pthread_mutex_lock(p->meal_log);
	p->last_meal_time = get_elapsed_time(p);
	pthread_mutex_unlock(p->meal_log);
}

void	sleeping(t_philo *p)
{
	printf("%lld %d is sleeping\n", get_elapsed_time(p), p->id);
	usleep(p->shared->time_to_sleep * 1000);
}

void	died(t_philo *p)
{
	printf("%lld %d died.\n", get_elapsed_time(p), p->id);
	p->shared->stop_flag = 1;
}
