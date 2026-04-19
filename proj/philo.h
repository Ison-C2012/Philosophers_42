/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:03:33 by keitotak          #+#    #+#             */
/*   Updated: 2026/04/19 17:50:54 by keitotak         ###   ########.fr       */
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
	pthread_mutex_t	*forks;
}	t_shared;

typedef struct s_philo
{
	int				id;
	t_shared		*shared;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		th;
}	t_philo;

int	ft_atoi(const char *nptr);
int	ft_isdigit(char c);
int	is_numbers(char **av);
int	valid_value(t_shared *shared);
int	philo(t_shared *shared);

void	pick_up_left_right(t_philo *p);
void	pick_up_right_left(t_philo *p);
void	put_down_left_right(t_philo *p);
void	put_down_right_left(t_philo *p);

long long	get_time(void);
long long	get_elapsed_time(t_philo *p);

#endif
