
#include "philo.h"

static int	kill_philo(t_info *info, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < info->philo_nums)
	{
		pthread_mutex_unlock(&info->forks[i]);
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	free_all(info, philos);
	return (0);
}

static int	print_end(t_info *info, t_philo *philos, t_philo *philo, int status)
{
	int	time;

	info->end = 1;
	pthread_mutex_lock(info->print);
	time = get_time() - info->start_time;
	if (status == STATUS_DIED)
		printf("%-5dms %d died!\n", time, philo->number + 1);
	else if (status == STATUS_FINISHED)
		printf("%-5dms program has finished!\n", time);
	pthread_mutex_unlock(info->print);
	return (kill_philo(info, philos));
}

int	start_monitor(t_info *info, t_philo *philos)
{
	int	starve_time;
	int	full_philos;
	int	i;

	while (1)
	{
		full_philos = 0;
		i = 0;
		while (i < info->philo_nums)
		{
			starve_time = get_time() - philos[i].last_eat;
			if (info->must_eat != -1 && philos[i].eat_count >= info->must_eat)
				full_philos += 1;
			if (!philos[i].eating && starve_time >= info->time_to_die)
				return (print_end(info, philos, &philos[i], STATUS_DIED));
			if (full_philos == info->philo_nums)
				return (print_end(info, philos, &philos[i], STATUS_FINISHED));
			i++;
		}
	}
	return (0);
}
