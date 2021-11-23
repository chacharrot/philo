/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonlee <jiwonlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 21:23:41 by jiwonlee          #+#    #+#             */
/*   Updated: 2021/07/07 19:19:27 by jiwonlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define LEFT 0
# define RIGHT 1

# define ERROR_ARGUMENT 0
# define ERROR_MALLOC 1
# define ERROR_MUTEX 2
# define ERROR_PTHREAD 3

# define STATUS_GET_FORK 0
# define STATUS_EATING 1
# define STATUS_SLEEPING 2
# define STATUS_THINKING 3

# define STATUS_DIED 4
# define STATUS_FINISHED 5

# define CHECK_MICRO 5
# define CHECK_MS 100

typedef struct s_info
{
	int				end;
	int				start_time;
	int				philo_nums;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
}					t_info;

typedef struct s_philo
{
	int				number;
	int				fork[2];
	int				last_eat;
	int				eat_count;
	int				eating;
	pthread_t		thread;
	t_info			*info;
}					t_philo;

int					init_info(t_info *info, char **av);
int					init_philo(t_info *info, t_philo *philos);
int					start_monitor(t_info *info, t_philo *philos);

void				get_fork(t_philo *philo);
void				eating(t_philo *philo);
void				put_fork(t_philo *philo);
void				sleeping(t_philo *philo);
void				print_action(t_philo *philo, int status);

int					print_error(int error);
long long			ft_atol(char *str);
int					free_all(t_info *info, t_philo *philos);
int					check_num(char *str);
int					get_time(void);
void				ft_sleep(int time, int check);

#endif
