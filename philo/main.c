/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:28:33 by tpons             #+#    #+#             */
/*   Updated: 2021/08/31 20:48:29 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		philo_routine()
{
	;
}

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
	
	return (0);
}