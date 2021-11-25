#include "philo.h"

void	get_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->fork[LEFT]]);
	if (!philo->info->end)
		print_action(philo, STATUS_GET_FORK);
	pthread_mutex_lock(&philo->info->forks[philo->fork[RIGHT]]);
	if (!philo->info->end)
		print_action(philo, STATUS_GET_FORK);
}

void	eating(t_philo *philo)
{
	philo->last_eat = get_time();
	philo->eating = 1;
	if (!philo->info->end)
		print_action(philo, STATUS_EATING);
	ft_sleep(philo->info->time_to_eat, CHECK_MS);
	philo->eat_count += 1;
	philo->eating = 0;
}

void	put_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->info->forks[philo->fork[LEFT]]);
	pthread_mutex_unlock(&philo->info->forks[philo->fork[RIGHT]]);
}

void	sleeping(t_philo *philo)
{
	if (!philo->info->end)
		print_action(philo, STATUS_SLEEPING);
	ft_sleep(philo->info->time_to_sleep, CHECK_MS);
}

void	print_action(t_philo *philo, int status)
{
	int	time;

	pthread_mutex_lock(philo->info->print);
	time = get_time() - philo->info->start_time;
	if (!philo->info->end)
	{
		if (status == STATUS_GET_FORK)
			printf("%-5dms %d has taken a fork\n", time, philo->number + 1);
		else if (status == STATUS_EATING)
			printf("%-5dms %d is eating\n", time, philo->number + 1);
		else if (status == STATUS_SLEEPING)
			printf("%-5dms %d is sleeping\n", time, philo->number + 1);
		else if (status == STATUS_THINKING)
			printf("%-5dms %d is thinking\n", time, philo->number + 1);
	}
	pthread_mutex_unlock(philo->info->print);
}
