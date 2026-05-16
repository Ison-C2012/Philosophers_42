/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:03:33 by keitotak          #+#    #+#             */
/*   Updated: 2026/05/16 10:34:08 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H 
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# define EATING 0
# define SLEEPING 1
# define THINKING 2
# define DIED 3

typedef struct s_shared
{
	int				nb_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nb_must_eat;
	long long		time_of_beginning;
	int				thread_created;
	int				stop_flag;
	pthread_mutex_t	start;
	pthread_mutex_t	flag;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
}	t_shared;

typedef struct s_philo
{
	int				id;
	int				status;
	int				nb_to_eat;
	long long		last_meal_time;
	t_shared		*shared;
	pthread_t		th;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

//ft_atoi.c
int			ft_atoi(const char *nptr);
int			ft_isdigit(char c);

//valid.c
int			is_numbers(char **av);
int			valid_value(t_shared *shared);

//mutex.c
int			init_mutex(t_shared *shared);
int			destroy_mutex(pthread_mutex_t *mutex, int i);

//philo.c
int			philo(t_shared *shared);

//philo_routine.c
void		*philo_routine(void *p);
void		*philo_odd_routine(t_philo *philo);
void		*philo_even_routine(t_philo *philo);

//philo_helpher.c
bool		check_stop(t_philo *p);
void		*solo_philo(t_philo *philo);
void		set_start(t_philo *philo);
int			join_philo(t_philo *philos, int nb);
int			destroy_mutex_philo(t_philo *philos, int i);

//waiter.c
int			waiter(t_philo *philos);
void		*waiter_routine(void *p);
int			check_starvation(t_philo *p);
void		flag_up(t_philo *p);

//fork.c
void		take_forks(t_philo *p);
void		put_forks(t_philo *p);

//status.c
void		eating(t_philo *p);
void		sleeping(t_philo *p);
void		thinking(t_philo *p);
void		died(t_philo *p);

//print.c
void		err_msg(void);
void		print_shared(t_shared *shared);
void		print_status(t_philo *p, char *s);
void		print_died(t_philo *p, char *s);

//time.c
long long	get_time_ms(void);
long long	get_elapsed_time(t_philo *p);

#endif
