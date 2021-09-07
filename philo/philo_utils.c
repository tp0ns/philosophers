/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 01:04:48 by tpons             #+#    #+#             */
/*   Updated: 2021/09/07 16:10:10 by tpons            ###   ########.fr       */
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
	if (fd > 0 && str)
	{
		while(str[i])
			i++;
		write(fd, str, i);
	}
}

//int	ft_usleep(coucou)

void	free_philos(t_philo *head)
{
	int 	i;
	int		pop;
	t_philo *temp;
	t_philo *old_temp;
	
	i = 0;
	pop = head->params->population;
	old_temp = head;
	while (i < pop)
	{
		temp = old_temp;
		old_temp = old_temp->next;
		free(temp->philosopher);
		free(temp);
		i++;
	}
}
