/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 13:38:58 by tpons             #+#    #+#             */
/*   Updated: 2021/08/31 22:53:33 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		check_args(char **av)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (av[i])
	{
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	if (i != 5 || i != 6)
		return (0);
	return (1);
}

int		init_params(int ac, char **av, t_params *params)
{
	if (check_args(av))
	{
		params->satiated = -1;
		if (ac == 6)
			params->satiated = ft_atoi(av[5]);
		params->population = ft_atoi(av[1]);
		params->longevity = ft_atoi(av[2]);
		params->hungry = ft_atoi(av[3]);
		params->sleepy = ft_atoi(av[4]);
		if (params->population <= 0 || params->longevity <= 0 ||
		params->hungry <= 0 || params->sleepy <= 0)
			return (0);
	}
	else 
		return (0);
	return (1);
}

t_philo	*new_philo(t_params *p, int id)
{
	t_philo new_philo;

	new_philo.philosopher = malloc(sizeof(pthread_t));
	if (!new_philo.philosopher)
		return (0);//error
	new_philo.id = id;
	new_philo.params = p;
	pthread_mutex_init(new_philo.fork, NULL);
	return (&new_philo);
}

int		init_philos(t_params *p, t_philo *head)
{
	int		i;
	t_philo	*temp;
	t_philo	*old_temp;

	i = 1;
	old_temp = head;
	head->philosopher = malloc(sizeof(pthread_t));
	if (!head->philosopher)
		return (0);
	head->id = 0;
	head->params = p;
	pthread_mutex_init(head->fork, NULL);
	while (i < p->population && old_temp)
	{
		temp = new_philo(p, i);
		i++;
		if (i < p->population)
			old_temp->next = temp;
		else
			old_temp->next = head;
		old_temp = temp;
	}
	if (!old_temp)
		return (0);
	return (1);
} //how to handle last philo ? 
