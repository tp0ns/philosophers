/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 13:38:58 by tpons             #+#    #+#             */
/*   Updated: 2021/09/13 22:54:53 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			check_args(int ac, char **av)
{
	int i;
	int j;

	i = 1;
	j = 0;
	if (ac != 5 && ac != 6)
		return (0);
	while (i < ac)
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
	return (1);
}

t_params	*init_params(int ac, char **av)
{
	t_params *params;

	params = malloc(sizeof(t_params));
	if (!params)
		return (0);
	if (check_args(ac, av))
	{
		params->t_meat = -1;
		if (ac == 6)
			params->t_meat = ft_atoi(av[5]);
		params->population = ft_atoi(av[1]);
		params->t_die = ft_atoi(av[2]);
		params->t_eat = ft_atoi(av[3]);
		params->t_sleep = ft_atoi(av[4]);
		params->dead = 0;
		params->satiated = 0;
		if (pthread_mutex_init(&params->talking, NULL))
			return (0);
		if (params->population <= 0 || params->t_die <= 0 ||
		params->t_eat <= 0 || params->t_sleep <= 0)
			return (0);
	}
	else 
		return (0);
	return (params);
}

t_philo		*new_philo(t_params *p, int id)//problem here
{
	t_philo *new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (new_philo == NULL)
		return (0);
	new_philo->id = id + 1;
	new_philo->params = p;
	if (pthread_mutex_init(&new_philo->fork, NULL))
		return (0);
	new_philo->eating = 0;
	new_philo->meals = 0;
	new_philo->full = 0;
	new_philo->last_meal = present();
	return (new_philo);
}
// new_philo->philosopher = malloc(sizeof(pthread_t));
// if (!new_philo->philosopher)
// 	return (0);

t_philo		*init_philos(t_params *p)
{
	int		i;
	t_philo	*head;
	t_philo	*temp;
	t_philo	*old_temp;

	i = 1;
	head = new_philo(p, 0);
	old_temp = head;
	while (i < p->population && old_temp)
	{
		temp = new_philo(p, i);
		i++;
		old_temp->next = temp;
		if (i == p->population)
			temp->next = head;
		old_temp = temp;
	}
	if (p->population == 1)
		head->next = NULL;
	if (!old_temp)
		return (0);
	return (head);
}
