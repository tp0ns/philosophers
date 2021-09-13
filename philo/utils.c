/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:56:29 by tpons             #+#    #+#             */
/*   Updated: 2021/09/13 22:27:09 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			ft_atoi(char *str)
{
	int		i;
	long	sum;

	sum = 0;
	i = -1;
	while (str[++i])
		sum = (sum * 10) + (str[i] - 48);
	return (sum);
}

void		ft_putstr_fd(char* str, int fd)
{
	int i;

	i = 0;
	if (fd > 0 && str)
	{
		while(str[i])
			i++;
		write(fd, str, i);
	}
}

long int	present(void)
{
	long int			time;
	struct timeval		actual_time;

	time = 0;
	if (gettimeofday(&actual_time, NULL) == -1)
		ft_error("Coudn't retrieve time of the day\n");
	time = (actual_time.tv_sec * 1000) + (actual_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_ms)
{
	long int	start;

	start = 0;
	start = present();
	while ((present() - start) < time_ms)
		usleep(time_ms / 10);
}
