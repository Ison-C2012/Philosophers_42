/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 17:27:09 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/24 16:55:42 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long) tv.tv_sec * 1000000 + tv.tv_usec);
}

long long	get_elapsed_time(t_shared *shared)
{
	long long	time_of_beginning;

	pthread_mutex_lock(&shared->start);
	time_of_beginning = shared->time_of_beginning;
	pthread_mutex_unlock(&shared->start);
	return ((get_time_us() - time_of_beginning));
}

void	ft_usleep(long long time, t_shared *shared)
{
	long long	target_time;

	target_time = get_time_us() + time;
	while (get_time_us() < target_time)
	{
		if (check_stop(shared))
			break ;
		usleep(500);
	}
}
