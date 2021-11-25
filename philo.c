
#include "philo.h"

int	init_info(t_info *info, char **av)
{
	int	i;

	info->end = 0;
	info->start_time = get_time();
	info->philo_nums = ft_atol(av[1]);
	info->time_to_die = ft_atol(av[2]);
	info->time_to_eat = ft_atol(av[3]);
	info->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		info->must_eat = ft_atol(av[5]);
	else
		info->must_eat = -1;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->philo_nums);
	if (!info->forks)
		return (print_error(ERROR_MALLOC));
	info->print = malloc(sizeof(pthread_mutex_t));
	if (!info->print)
		return (print_error(ERROR_MALLOC));
	i = 0;
	while (i < info->philo_nums)
		if (pthread_mutex_init(&info->forks[i++], NULL))
			return (print_error(ERROR_MUTEX));
	if (pthread_mutex_init(info->print, NULL))
		return (print_error(ERROR_MUTEX));
	return (0);
}

static void	*philo_action(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	if (philo->number % 2 == 1)
		ft_sleep(50 * philo->number, CHECK_MICRO);
	while (!philo->info->end)
	{
		get_fork(philo);
		eating(philo);
		put_fork(philo);
		sleeping(philo);
		if (!philo->info->end)
			print_action(philo, STATUS_THINKING);
	}
	return (philo_void);
}

int	init_philo(t_info *info, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < info->philo_nums)
	{
		philos[i].number = i;
		philos[i].fork[LEFT] = i;
		philos[i].fork[RIGHT] = (i + 1) % info->philo_nums;
		philos[i].last_eat = get_time();
		philos[i].eat_count = 0;
		philos[i].eating = 0;
		philos[i].info = info;
		if (pthread_create(&philos[i].thread, NULL, &philo_action, \
					(void *)&philos[i]))
			return (ERROR_PTHREAD);
		i++;
	}
	return (0);
}
