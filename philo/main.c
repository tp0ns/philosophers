/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:28:33 by tpons             #+#    #+#             */
/*   Updated: 2021/09/15 16:45:01 by tpons            ###   ########.fr       */
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
	t_params	*params;
	t_philo		*philo;

	params = init_params(ac, av);
	if (!params)
		return (ft_error("Error : Invalid arguments !\n"));
	philo = init_philos(params);
	if (!philo)
	{
		free(params);
		pthread_mutex_destroy(&params->talking);
		return (ft_error("Error : Problem occured when starting threads !\n"));
	}
	if (!thread(philo))
	{
		free_philos(philo);
		free(params);
		return (ft_error("Error : Can't initialize thread\n"));
	}
	free_philos(philo);
	free(params);
	return (0);
}