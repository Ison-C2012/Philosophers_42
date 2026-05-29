/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 15:00:36 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/29 23:11:05 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define USAGE_MSG "Usage:\t./philo arg1 arg2 arg3 arg4 <arg5>\n"
#define ARG1_MSG "arg1:\tnumber of philosophers\n"
#define ARG2_MSG "arg2:\ttime to die [milliseconds]\n"
#define ARG3_MSG "arg3:\ttime to eat [milliseconds]\n"
#define ARG4_MSG "arg4:\ttime to sleep [milliseconds]\n"
#define ARG5_MSG "arg5:\tnumber of times each philosophers must eat <option>\n"
#define RNG_MSG "All of arguments must be greater than 0 and within INT_MAX.\n"

void	err_msg(void)
{
	write(2, USAGE_MSG, ft_strlen(USAGE_MSG) + 1);
	write(2, ARG1_MSG, ft_strlen(ARG1_MSG) + 1);
	write(2, ARG2_MSG, ft_strlen(ARG2_MSG) + 1);
	write(2, ARG3_MSG, ft_strlen(ARG3_MSG) + 1);
	write(2, ARG4_MSG, ft_strlen(ARG4_MSG) + 1);
	write(2, ARG5_MSG, ft_strlen(ARG5_MSG) + 1);
	write(2, RNG_MSG, ft_strlen(RNG_MSG) + 1);
}

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
