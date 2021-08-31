/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 13:38:58 by tpons             #+#    #+#             */
/*   Updated: 2021/08/31 16:04:26 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		check_args(char **av)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (av[i])
	{
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	if (i != 5 || i != 6)
		return (0);
	return (1);
}

int		init_params(int ac, char **av, t_params *params)
{
	if (check_args(av))
	{
		params->satiated = -1;
		if (ac == 6)
			params->satiated = ft_atoi(av[5]);
		params->population = ft_atoi(av[1]);
		params->longevity = ft_atoi(av[2]);
		params->hungry = ft_atoi(av[3]);
		params->sleepy = ft_atoi(av[4]);
		if (params->population <= 0 || params->longevity <= 0 ||
		params->hungry <= 0 || params->sleepy <= 0)
			return (0);
	}
	else 
		return (0);
	return (1);
}
