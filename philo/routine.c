/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:14:45 by tpons             #+#    #+#             */
/*   Updated: 2021/09/10 18:18:51 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_talks(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->params->talking);	
	printf("Philo %d %s", philo->id, str);
	pthread_mutex_unlock(&philo->params->talking);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	philo_talks(philo, "has taken Left fork.\n");
	pthread_mutex_lock(&philo->next->fork);
	philo_talks(philo, "has taken Right fork.\n");
	//change last meal hour
	//mutex for is eating
	philo_talks(philo, "is eating.\n");
	//unlock it
	ft_usleep(philo->params->t_eat);
	
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	*philo_routine(void *data) 
{
	
	t_philo *philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(philo->params->t_eat / 10);
	while(1)
		philo_eat(philo);
	return (NULL);
}

int		thread(t_philo *head)
{
	int		i;
	t_philo *philo;

	i = 0;
	philo = head;
	while (philo && i < philo->params->population)
	{
		if (pthread_create(&(philo->philosopher), NULL, philo_routine, philo) != 0)
			return (0);
		philo = philo->next;
		i++;
	}
	return (1);
}
