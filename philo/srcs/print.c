/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 15:00:36 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/25 20:07:35 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_died(t_philo *p, char *s)
{
	pthread_mutex_lock(&p->shared->print);
	printf("%lld %d %s\n", get_elapsed_time(p->shared) / 1000, p->id, s);
	pthread_mutex_unlock(&p->shared->print);
}

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
	printf("%lld %d %s\n", get_elapsed_time(p->shared) / 1000, p->id, s);
	pthread_mutex_unlock(&p->shared->print);
}

void	print_shared(t_shared *shared)
{
	printf("number_of_philosophers=%d\n", shared->nb_philo);
	printf("time_to_die=%lld\n", shared->time_to_die / 1000);
	printf("time_to_eat=%lld\n", shared->time_to_eat / 1000);
	printf("time_to_sleep=%lld\n", shared->time_to_sleep / 1000);
	printf("number_of_times_each_philosopher_must_eat=%d\n",
		shared->nb_must_eat);
}

void	err_msg(void)
{
	write(2, "Usage:\t./philo arg1 arg2 arg3 arg4 <arg5>\n", 43);
	write(2, "arg1:\tnumber of philosophers (>0)\n", 35);
	write(2, "arg2:\ttime to die (>0) [milliseconds]\n", 39);
	write(2, "arg3:\ttime to eat (>0) [milliseconds]\n", 39);
	write(2, "arg4:\ttime to sleep (>=0) [milliseconds]\n", 42);
	write(2, "arg5:\tnumber of times each philosophers must eat (>=0)", 55);
	write(2, " <option>\n", 11);
	write(2, "*all of arguments is expected under INT_MAX\n", 45);
}
