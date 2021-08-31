/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 01:04:48 by tpons             #+#    #+#             */
/*   Updated: 2021/08/31 16:47:47 by tpons            ###   ########.fr       */
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

void	ft_putstr_fd(char* str, int fd)
{
	int i;

	i = 0;
	if (fd > 0)
	{
		while(str[i] && str)
			i++;
		write(fd, str, i);
	}
}


//int	ft_usleep(coucou)
