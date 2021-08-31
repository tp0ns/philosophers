/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 01:04:48 by tpons             #+#    #+#             */
/*   Updated: 2021/08/31 22:39:40 by tpons            ###   ########.fr       */
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

void	free_philos(t_philo *head)
{
	t_philo *temp;
	t_philo *old_temp;
	
	old_temp = head;
	while (old_temp != NULL)
	{
		temp = old_temp;
		old_temp = old_temp->next;
		if (old_temp == head)
			old_temp = NULL;
		else	
			free(temp);
	}
}

//int	ft_usleep(coucou)
