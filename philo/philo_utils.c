/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 01:04:48 by tpons             #+#    #+#             */
/*   Updated: 2021/09/15 17:32:19 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	are_philos_alive(t_philo *philo)
{
	int	i;

	i = 0;
	while ((i++ < philo->params->population) && !(philo->params->dead))
	{
		pthread_mutex_lock(&philo->eating);
		if ((present() - philo->last_meal) > philo->params->t_die)
		{	
			philo->params->dead = 1;
			philo_talks(philo, "is dead");
		}
		pthread_mutex_unlock(&philo->eating);
		philo = philo->next;
	}
}

void	*should_philos_run(void *data)
{
	t_philo *philo;
	int		i;

	philo = (t_philo *)data;
	while (!philo->params->satiated)
	{
		i = 0;
		are_philos_alive(philo);
		if (philo->params->dead)
			break ;
		i = 0;
		while (philo->params->t_meat >= 0 && i++ < philo->params->population
		&& philo->full)
			i++;
		if (i == philo->params->population)
		{
			philo->params->satiated = 1;
			break ;
		}
	}
	return (NULL);
}

void	free_philos(t_philo *head)
{
	int 	i;
	int		pop;
	t_philo *temp;
	t_philo *old_temp;
	
	i = 0;
	pop = head->params->population;
	old_temp = head;
	while (i < pop)
	{
		temp = old_temp;
		old_temp = old_temp->next;
		pthread_join(temp->philosopher, NULL);
		pthread_mutex_destroy(&temp->fork);
		pthread_mutex_destroy(&temp->eating);
		free(temp);
		i++;
	}
}
