/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:14:45 by tpons             #+#    #+#             */
/*   Updated: 2021/10/05 14:52:00 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_talks(t_philo *philo, char *str)
{
	if (!philo->params->dead && !philo->params->satiated)
	{
		pthread_mutex_lock(&philo->params->talking);
		printf("%-5ld | Philo %d %s.\n", (present() - philo->params->start),
			philo->id, str);
		pthread_mutex_unlock(&philo->params->talking);
	}
}

void	philo_eats(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	philo_talks(philo, "has taken a fork");
	pthread_mutex_lock(&philo->next->fork);
	philo_talks(philo, "has taken a fork");
	pthread_mutex_lock(&philo->eating);
	philo_talks(philo, "is eating");
	philo->last_meal = present();
	if (!philo->params->dead || !philo->params->satiated)
	{
		ft_usleep(philo->params->t_eat);
		pthread_mutex_unlock(&philo->eating);
		philo->meals++;
		if (philo->params->t_meat >= 0
			&& (philo->meals >= philo->params->t_meat))
			philo->full = 1;
	}
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	philo_routine(t_philo *philo)
{
	while (!philo->params->dead && philo->params->satiated != 1)
	{
		philo_eats(philo);
		if (philo->params->dead || philo->params->satiated)
			break ;
		philo_talks(philo, "is sleeping");
		ft_usleep(philo->params->t_sleep);
		if (philo->params->dead || philo->params->satiated)
			break ;
		philo_talks(philo, "is thinking");
	}
}

void	*philo_launch(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(philo->params->t_eat / 10);
	philo_routine(philo);
	return (NULL);
}

int	thread(t_philo *head)
{
	int			i;
	t_philo		*philo;
	pthread_t	alive_check;

	i = 0;
	philo = head;
	philo->params->start = present();
	if (philo->params->population == 1)
		philo_is_alone(philo);
	else
	{
		if (pthread_create(&(alive_check), NULL, should_philos_run, philo) != 0)
			return (0);
		while (philo && i++ < philo->params->population)
		{
			if (pthread_create(&(philo->philosopher), NULL, philo_launch, philo)
				!= 0)
				return (0);
			if (philo->params->population != 1)
				philo = philo->next;
		}
		pthread_join(alive_check, NULL);
	}
	return (1);
}
