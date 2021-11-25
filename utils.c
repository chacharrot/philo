#include "philo.h"

static double	get_micro_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 100000 + tv.tv_usec);
}

void	ft_sleep(int time, int check)
{
	double	start;
	double	now;

	if (time == 0)
		return ;
	if (check == CHECK_MS)
	{
		start = get_time();
		now = 0;
		while (now == 0 || now - start < time)
		{
			usleep(CHECK_MS);
			now = get_time();
		}
	}
	else if (check == CHECK_MICRO)
	{
		start = get_micro_time();
		now = 0;
		while (now == 0 || now - start < time)
		{
			usleep(CHECK_MICRO);
			now = get_micro_time();
		}
	}
}

long long	ft_atol(char *str)
{
	long long	num;
	int			i;

	num = 0;
	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ('0' <= str[i] && str[i] <= '9'))
		num = num * 10 + (str[i++] - '0');
	return (num);
}

int	check_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
