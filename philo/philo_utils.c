/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 01:04:48 by tpons             #+#    #+#             */
/*   Updated: 2021/11/16 12:22:54 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_is_alone(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	philo_talks(philo, "has taken a fork");
	ft_usleep(philo->params->t_die);
	pthread_mutex_unlock(&philo->fork);
	philo_talks(philo, "died");
}

void	check_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->eating);
	if ((present() - philo->last_meal) > philo->params->t_die)
	{
		philo_talks(philo, "died");
		safe_change(philo->params->race_d, &philo->params->dead, 1);
	}
	pthread_mutex_unlock(&philo->eating);
}

void	*is_philos_alive(void *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)data;
	i = 0;
	while (!safe_check(philo->params->race_d, philo->params->dead))
	{
		if (philo->id == 1)
			i = 0;
		if (safe_check(philo->race_f, philo->full))
			i++;
		else
			check_alive(philo);
		if (i >= philo->params->population)
			break ;
		philo = philo->next;
	}
	return (NULL);
}

int	safe_check(pthread_mutex_t check, int value)
{
	int	i;

	pthread_mutex_lock(&check);
	i = value;
	pthread_mutex_unlock(&check);
	return (i);
}

void	safe_change(pthread_mutex_t change, int *value, int def)
{
	pthread_mutex_lock(&change);
	*value = def;
	pthread_mutex_unlock(&change);
}
