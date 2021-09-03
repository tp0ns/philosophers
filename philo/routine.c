/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:14:45 by tpons             #+#    #+#             */
/*   Updated: 2021/09/03 16:56:32 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_routine(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->params->talking);
	printf("%s %d.", str, philo->id);
	pthread_mutex_unlock(philo->params->talking);
}

void	*philo_routine(t_philo *philo)
{
	// while (philos_alive())
	// {
		pthread_mutex_lock(philo->fork);
		print_routine(philo, "has taken Left fork");
		pthread_mutex_lock(philo->next->fork);
		print_routine(philo, "has taken Right fork");
		print_routine(philo, "is eating.");
		usleep(philo->params->hungry);
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->next->fork);
	// }
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
