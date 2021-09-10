/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:14:45 by tpons             #+#    #+#             */
/*   Updated: 2021/09/10 17:53:43 by tpons            ###   ########.fr       */
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
	philo_talks(philo, "is eating.\n");
	ft_usleep(philo->params->t_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	*philo_routine(void *data) 
{
	
	t_philo *philo;

	philo = (t_philo *)data;
	write(2, "hi\n", 3);
	// if (philo->id % 2 == 0)
	// {
			// usleep(15000);// ft_usleep(philo->params->t_eat / 10);
			// printf("coucou pair\n");
	// }
	// while(1)
		// philo_eat(philo);
	// else
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
		if (pthread_create(philo->philosopher, NULL, philo_routine, philo) != 0)
			return (0);
		philo = philo->next;
		i++;
	}
	return (1);
}
