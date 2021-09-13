/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 01:04:48 by tpons             #+#    #+#             */
/*   Updated: 2021/09/13 23:31:28 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*are_philos_alive(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (((present() - philo->last_meal) > philo->params->t_die)
		&& !philo->eating)
			break;
		philo = philo->next;
	}
	philo->params->dead = 1;
	philo_talks(philo, "is dead");
	return (NULL);
}

void	*are_philos_hungry(void *data)
{
	t_philo *philo;
	int		full_count;

	philo = (t_philo *)data;
	full_count = 0;
	while (1)
	{
		full_count = 0;
		while (philo->full)
		{
			full_count++;
			philo = philo->next;
		}
		if (!philo->full && (philo->meals >= philo->params->t_meat))
			philo->full = 1;
		if (full_count >= philo->params->population)
			break ;
		philo = philo->next;
	}
	philo->params->satiated = 1;
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
		free(temp);
		i++;
	}
}
