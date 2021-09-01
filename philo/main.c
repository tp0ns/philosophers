/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:28:33 by tpons             #+#    #+#             */
/*   Updated: 2021/09/01 11:19:57 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

int		main(int ac, char **av)
{
	t_params	params;
	t_philo		philo;

	if (!init_param(ac, av, &params))
		return (ft_error("Error : Invalid arguments !\n"));
	if (!init_philos(&params, &philo))
		return (ft_error("Error : Problem occured when starting threads !\n"));
	if (!thread(&philo))
	{
		free_philos(&philo);
		return (ft_error("Error : !\n"));
	}

	return (0);
}