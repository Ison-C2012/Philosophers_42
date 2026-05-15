/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 17:27:09 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/15 22:56:15 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long) tv.tv_sec * 1000000 + tv.tv_usec);
}

long long	get_elapsed_time(t_philo *p)
{
	long long	time_of_beginning;
	pthread_mutex_lock(&p->shared->start);
	time_of_beginning = p->shared->time_of_beginning;
	pthread_mutex_unlock(&p->shared->start);
	return ((get_time_ms() - time_of_beginning));
}
