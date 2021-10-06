/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 01:04:48 by tpons             #+#    #+#             */
/*   Updated: 2021/10/05 14:50:25 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_is_alone(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	philo_talks(philo, "has taken a fork");
	ft_usleep(philo->params->t_die);
	pthread_mutex_unlock(&philo->fork);
	philo_talks(philo, "is dead");
}

void	are_philos_alive(t_philo *philo)
{
	int	i;

	i = 0;
	while ((i++ < philo->params->population) && !(philo->params->dead))
	{
		pthread_mutex_lock(&philo->eating);
		if (((present() - philo->last_meal) > philo->params->t_die))
		{
			philo->params->dead = 1;
			pthread_mutex_lock(&philo->params->talking);
			printf("%-5ld | Philo %d %s.\n", (present() - philo->params->start),
				philo->id, "is dead");
			pthread_mutex_unlock(&philo->params->talking);
		}
		pthread_mutex_unlock(&philo->eating);
		philo = philo->next;
	}
}

void	*should_philos_run(void *data)
{
	t_philo	*philo;
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
			philo = philo->next;
		if (i >= philo->params->population)
		{
			philo->params->satiated = 1;
			break ;
		}
	}
	return (NULL);
}

void	free_init_philos(t_philo *head)
{
	t_philo	*philo;
	t_philo	*next_philo;

	if (head == NULL)
		return ;
	philo = head;
	next_philo = philo->next;
	while (next_philo != NULL)
	{
		pthread_mutex_destroy(&philo->eating);
		pthread_mutex_destroy(&philo->fork);
		free(philo);
		philo = next_philo;
		next_philo = philo->next;
	}
	pthread_mutex_destroy(&philo->eating);
	pthread_mutex_destroy(&philo->fork);
	free(philo);
}

void	free_philos(t_philo *head)
{
	int		i;
	int		pop;
	t_philo	*temp;
	t_philo	*next_temp;

	i = 0;
	pop = head->params->population;
	temp = head;
	while (i < pop)
	{
		pthread_join(temp->philosopher, NULL);
		temp = temp->next;
		i++;
	}
	i = 0;
	temp = head;
	while (i < pop)
	{
		next_temp = temp->next;
		pthread_mutex_destroy(&temp->fork);
		pthread_mutex_destroy(&temp->eating);
		free(temp);
		temp = next_temp;
		i++;
	}
}
