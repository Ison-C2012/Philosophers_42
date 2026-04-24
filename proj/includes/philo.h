/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:03:33 by keitotak          #+#    #+#             */
/*   Updated: 2026/04/24 12:39:34 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_shared
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	long long		time_of_beginning;
	int				stop_flag;
	pthread_mutex_t	flag;
	pthread_mutex_t	*forks;
}	t_shared;

typedef struct s_philo
{
	int				id;
	t_shared		*shared;
	pthread_t		th;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_log;
	long long		last_meal_time;
	int				nb_to_eat;
}	t_philo;

int	ft_atoi(const char *nptr);
int	ft_isdigit(char c);
int	is_numbers(char **av);
int	valid_value(t_shared *shared);

int	philo(t_shared *shared);

void	*waiter_routine(void *p);
int		check_stop(t_philo *p);

void	take_forks(t_philo *p);
void	put_forks(t_philo *p);

void	thinking(t_philo *p);
void	eating(t_philo *p);
void	sleeping(t_philo *p);
void	died(t_philo *p);

long long	get_time_ms(void);
long long	get_elapsed_time(t_philo *p);

#endif
