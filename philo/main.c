/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:28:33 by tpons             #+#    #+#             */
/*   Updated: 2021/11/03 20:04:29 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_params	*params;
	t_philo		*philo;

	params = init_params(ac, av);
	if (!params)
		return (ft_error("Error : Invalid arguments !\n"));
	philo = init_philos(params);
	if (!philo)
	{
		free_params(params);
		return (ft_error("Error : Problem occured when starting threads !\n"));
	}
	if (!thread(philo))
	{
		free_philos(philo);
		free_params(params);
		return (ft_error("Error : Can't initialize thread\n"));
	}
	free_philos(philo);
	free_params(params);
	return (0);
}
