/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 01:04:48 by tpons             #+#    #+#             */
/*   Updated: 2021/09/03 16:18:58 by tpons            ###   ########.fr       */
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
	while (i < pop)//check this
	{
		temp = old_temp;
		old_temp = old_temp->next;
		free(temp->philosopher);
		free(temp);
		i++;
	}
	//free the last here ? (no)
}

static int		num_length(long n)
{
	int	i;

	i = 1;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char		*fill_string(char *str, int n, int l)
{
	str[--l] = '\0';
	while (n / 10 >= 1)
	{
		str[--l] = (n % 10) + '0';
		n /= 10;
	}
		str[0] = (n % 10) + '0';
	return (str);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		l;

	l = num_length(n);
	if (!(str = malloc(sizeof(char) * l)))
		return (0);
	str = fill_string(str, n, l);
	return (str);
}
