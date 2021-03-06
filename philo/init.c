/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 13:38:58 by tpons             #+#    #+#             */
/*   Updated: 2021/11/04 15:07:36 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

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

int	from_args_to_params(t_params *params, int ac, char **av)
{
	params->t_meat = -1;
	if (ac == 6)
		params->t_meat = ft_atoi(av[5]);
	params->population = ft_atoi(av[1]);
	params->t_die = ft_atoi(av[2]);
	params->t_eat = ft_atoi(av[3]);
	params->t_sleep = ft_atoi(av[4]);
	params->dead = 0;
	if (pthread_mutex_init(&params->talking, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&params->race_d, NULL) != 0)
	{
		pthread_mutex_destroy(&params->talking);
		return (1);
	}
	if (params->population <= 0 || params->population > 200 || params->t_die
		<= 60 || params->t_eat <= 60 || params->t_sleep <= 60)
		return (1);
	return (0);
}

t_params	*init_params(int ac, char **av)
{
	t_params	*params;

	params = malloc(sizeof(t_params));
	if (!params)
		return (0);
	if (!check_args(ac, av)
		|| from_args_to_params(params, ac, av))
	{
		free(params);
		return (0);
	}
	return (params);
}

t_philo	*new_philo(t_params *p, int id)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (new_philo == NULL)
		return (0);
	new_philo->id = id + 1;
	new_philo->params = p;
	new_philo->meals = 0;
	new_philo->full = 0;
	new_philo->last_meal = present();
	if (init_philo_mutex(&new_philo->fork, &new_philo->eating,
			&new_philo->race_f))
	{
		free(new_philo);
		return (0);
	}
	new_philo->next = NULL;
	return (new_philo);
}

t_philo	*init_philos(t_params *p)
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
		old_temp = temp;
		if (!old_temp)
			break ;
		if (i == p->population)
			temp->next = head;
	}
	if (!old_temp)
	{
		free_init_philos(head);
		return (0);
	}
	return (head);
}
