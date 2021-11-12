/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:56:29 by tpons             #+#    #+#             */
/*   Updated: 2021/11/04 15:08:49 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	long	sum;

	sum = 0;
	i = -1;
	while (str[++i])
		sum = (sum * 10) + (str[i] - 48);
	return (sum);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n < 10)
	{
		c = n + '0';
		write(fd, &c, 1);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		c = (n % 10) + '0';
		write(fd, &c, 1);
	}
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (fd > 0 && str)
	{
		while (str[i])
			i++;
		write(fd, str, i);
	}
}

long int	present(void)
{
	struct timeval		actual_time;

	if (gettimeofday(&actual_time, NULL) == -1)
		ft_error("Coudn't retrieve time of the day\n");
	return ((actual_time.tv_sec * 1000) + (actual_time.tv_usec / 1000));
}

void	ft_usleep(long int time_ms)
{
	long int	start;

	start = 0;
	start = present();
	while ((present() - start) < time_ms)
		usleep(1);
}

int	init_philo_mutex(pthread_mutex_t *a, pthread_mutex_t *b,
pthread_mutex_t *c)
{
	if (pthread_mutex_init(a, NULL) != 0)
		return (1);
	if (pthread_mutex_init(b, NULL) != 0)
	{
		pthread_mutex_destroy(a);
		return (1);
	}
	if (pthread_mutex_init(c, NULL) != 0)
	{
		pthread_mutex_destroy(a);
		pthread_mutex_destroy(b);
		return (1);
	}
	return (0);
}
