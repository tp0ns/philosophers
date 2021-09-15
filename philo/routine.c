/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:14:45 by tpons             #+#    #+#             */
/*   Updated: 2021/09/15 17:23:13 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_talks(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->params->talking);	
	printf("%ld | Philo %d %s.\n", (present() - philo->params->start), philo->id, str);
	pthread_mutex_unlock(&philo->params->talking);
}

void	philo_routine(t_philo *philo)
{
	while (!philo->params->dead && (philo->params->satiated <= 0))
	{
		pthread_mutex_lock(&philo->fork);
		philo_talks(philo, "has taken a fork");
		pthread_mutex_lock(&philo->next->fork);
		philo_talks(philo, "has taken a fork");
		pthread_mutex_lock(&philo->eating);
		philo_talks(philo, "is eating");
		philo->last_meal = present();
		ft_usleep(philo->params->t_eat);
		pthread_mutex_unlock(&philo->eating);
		philo->meals++;
		if (philo->params->t_meat >= 0 && (philo->meals >= philo->params->t_meat))
			philo->full = 1;
		if (philo->params->t_meat >= 0 && philo->params->satiated)
			break ;
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		philo_talks(philo, "is sleeping");
		ft_usleep(philo->params->t_sleep);
		philo_talks(philo, "is thinking");
	}
}

void	*philo_launch(void *data) 
{
	t_philo *philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(philo->params->t_eat / 10);
	philo_routine(philo);
	return (NULL);
}

int		thread(t_philo *head)
{
	int			i;
	t_philo 	*philo;
	pthread_t	alive_check;

	i = 0;
	philo = head;
	philo->params->start = present();
	if (pthread_create(&(alive_check), NULL, should_philos_run, philo) != 0)
		return (0);
	while (philo && i++ < philo->params->population)
	{
		if (pthread_create(&(philo->philosopher), NULL, philo_launch, philo) != 0)
			return (0);
		philo = philo->next;
	}
	pthread_join(alive_check, NULL);
	return (1);
}
