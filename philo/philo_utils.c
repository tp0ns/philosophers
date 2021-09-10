/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 01:04:48 by tpons             #+#    #+#             */
/*   Updated: 2021/09/10 16:31:06 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		free(temp->philosopher);
		free(temp);
		i++;
	}
}
