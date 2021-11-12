/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:14:45 by tpons             #+#    #+#             */
/*   Updated: 2021/11/04 15:57:50 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_talks(t_philo *philo, char *str)
{
	if (!safe_check(philo->params->race_d, philo->params->dead))
	{
		pthread_mutex_lock(&philo->params->talking);
		ft_putnbr_fd((int)(present() - philo->params->start), 1);
		write(1, " ", 1);
		ft_putnbr_fd(philo->id, 1);
		write(1, " ", 1);
		ft_putstr_fd(str, 1);
		write(1, "\n", 1);
		// printf("%ld %d %s\n", (present() - philo->params->start),
		// 	philo->id, str);
		pthread_mutex_unlock(&philo->params->talking);
	}
	else
		return (1);
	return (0);
}

int	philo_eats(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	philo_talks(philo, "has taken a fork");
	pthread_mutex_lock(&philo->next->fork);
	philo_talks(philo, "has taken a fork");
	pthread_mutex_lock(&philo->eating);
	philo->last_meal = present();
	pthread_mutex_unlock(&philo->eating);
	philo_talks(philo, "is eating");
	ft_usleep(philo->params->t_eat);
	if (philo->params->t_meat >= 0 && ++philo->meals >= philo->params->t_meat)
	{
		safe_change(philo->race_f, &philo->full, 1);
		return (1);
	}
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	return (0);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(philo->params->t_eat / 10);
	while (!safe_check(philo->params->race_d, philo->params->dead))
	{
		if (philo_eats(philo))
			break ;
		philo_talks(philo, "is sleeping");
		ft_usleep(philo->params->t_sleep);
		philo_talks(philo, "is thinking");
	}
	return (NULL);
}

int	thread(t_philo *philo)
{
	int			i;

	i = 0;
	philo->params->start = present();
	if (philo->params->population == 1)
		philo_is_alone(philo);
	else
	{
		if (pthread_create(&philo->params->alive_check, NULL, is_philos_alive,
				philo) != 0)
			return (0);
		while (philo && i++ < philo->params->population)
		{
			if (pthread_create(&philo->philosopher, NULL, philo_routine, philo)
				!= 0)
				return (0);
			philo = philo->next;
		}
		pthread_join(philo->params->alive_check, NULL);
	}
	return (1);
}
