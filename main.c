/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonlee <jiwonlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 21:15:20 by jiwonlee          #+#    #+#             */
/*   Updated: 2021/07/07 19:32:24 by jiwonlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_all(t_info *info, t_philo *philos)
{
	int	i;

	i = 0;
	if (info->forks)
	{
		while (i < info->philo_nums)
			pthread_mutex_destroy(&info->forks[i++]);
		free(info->forks);
	}
	if (info->print)
	{
		pthread_mutex_destroy(info->print);
		free(info->print);
	}
	if (philos)
		free(philos);
	return (0);
}

int	print_error(int error)
{
	if (error == ERROR_ARGUMENT)
		printf("argument error\n");
	else if (error == ERROR_MALLOC)
		printf("malloc error\n");
	else if (error == ERROR_MUTEX)
		printf("mutex error\n");
	else if (error == ERROR_PTHREAD)
		printf("pthread error\n");
	return (1);
}

static int	check_arg(int ac, char **av)
{
	int		i;

	if (ac < 5 || ac > 6)
		return (print_error(ERROR_ARGUMENT));
	i = 1;
	while (av[i])
	{
		if (check_num(av[i]) == 1)
			return (print_error(ERROR_ARGUMENT));
		if (INT_MIN > ft_atol(av[i]) || ft_atol(av[i]) > INT_MAX)
			return (print_error(ERROR_ARGUMENT));
		i++;
	}
	if (ft_atol(av[1]) < 1)
		return (print_error(ERROR_ARGUMENT));
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;
	t_philo	*philos;

	if (check_arg(ac, av))
		return (0);
	memset(&info, 0, sizeof(t_info));
	philos = malloc(sizeof(t_philo) * ft_atol(av[1]));
	if (!philos)
		return (print_error(ERROR_MALLOC));
	if (init_info(&info, av) == 1)
		return (free_all(&info, philos));
	if (init_philo(&info, philos) == 1)
		return (free_all(&info, philos));
	return (start_monitor(&info, philos));
}
