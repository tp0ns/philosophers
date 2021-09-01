/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:14:45 by tpons             #+#    #+#             */
/*   Updated: 2021/09/01 16:08:08 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_routine(char *str, int id)
{

}

void	philo_routine(t_philo *philo)
{
	while (philos_alive())
	{
		pthread_mutex_lock(philo->params->talking);
		print_routine("", philo->id);
		pthread_mutex_unlock(philo->params->talking);
	}
}

	int		thread(t_philo *philo)
{
	int		i;
	// t_philo *head;

	i = 0;
	while (i < philo->params->population)
	{
		pthread_create(philo->philosopher, NULL, philo_routine, philo);
		philo = philo->next;
		i++;
	}
		return (0);
	return (1);
}
