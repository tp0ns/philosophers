/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:14:45 by tpons             #+#    #+#             */
/*   Updated: 2021/09/08 20:43:32 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_routine(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->params->talking);	
	printf("%d %s", philo->id, str);
	pthread_mutex_unlock(&philo->params->talking);
}

void	*philo_routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	// while (philos_alive())
	// {
	pthread_mutex_lock(&philo->fork);
	print_routine(philo, "has taken Left fork");
	pthread_mutex_lock(&philo->next->fork);
	print_routine(philo, "has taken Right fork");
	print_routine(philo, "is eating.");
	usleep(philo->params->hungry);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	// }
	return (0);
}

int		thread(t_philo *head)
{
	int		i;
	t_philo *philo;

	i = 0;
	philo = head;
	while (philo && i < philo->params->population)
	{
		pthread_create(philo->philosopher, NULL, philo_routine, philo);
		philo = philo->next;
		i++;
	}
	return (1);
}
