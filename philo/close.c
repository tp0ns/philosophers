/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:52:39 by tpons             #+#    #+#             */
/*   Updated: 2021/11/03 21:02:01 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_params(t_params *params)
{
	pthread_mutex_destroy(&params->talking);
	pthread_mutex_destroy(&params->race_d);
	free(params);
}

void	free_init_philos(t_philo *philo)
{
	t_philo	*next_philo;

	if (philo == NULL)
		return ;
	next_philo = philo->next;
	while (next_philo != NULL)
	{
		pthread_mutex_destroy(&philo->eating);
		pthread_mutex_destroy(&philo->fork);
		pthread_mutex_destroy(&philo->race_f);
		free(philo);
		philo = next_philo;
		next_philo = philo->next;
	}
	pthread_mutex_destroy(&philo->eating);
	pthread_mutex_destroy(&philo->fork);
	pthread_mutex_destroy(&philo->race_f);
	free(philo);
}

void	free_philos(t_philo *philo)
{
	int		i;
	int		pop;
	t_philo	*next_philo;

	i = 0;
	pop = philo->params->population;
	while ((pop > 1) && (i++ < pop))
	{
		pthread_join(philo->alive_check, NULL);
		pthread_join(philo->philosopher, NULL);
		philo = philo->next;
	}
	i = 0;
	while (i++ < pop)
	{
		next_philo = philo->next;
		pthread_mutex_destroy(&philo->fork);
		pthread_mutex_destroy(&philo->eating);
		pthread_mutex_destroy(&philo->race_f);
		free(philo);
		philo = next_philo;
	}
}

int	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}
