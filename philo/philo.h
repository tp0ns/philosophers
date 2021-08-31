/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:34:59 by tpons             #+#    #+#             */
/*   Updated: 2021/08/31 21:34:49 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef	struct		s_philo
{
	pthread_t		philosopher;
	/*thread representing the philosopher*/
	int				id;
	/*id of the philosopher*/
	t_params		*params;
	/*global params, same for all philosophers*/
	pthread_mutex_t	*fork;
	/*fork tab representing every fork*/
	t_philo			*next;
	/*points to the philosopher to his right*/
}					t_philo;

typedef	struct		s_params
{
	int				population;
	/*number of philosophers*/
	int				longevity;
	/*time to die*/
	int				hungry;
	/*time to eat*/
	int				sleepy;
	/* time to sleep*/
	int				satiated;
	/*number of times each philosopher must eat*/
}					t_params;

int					ft_atoi(char *str);
void				ft_putstr_fd(char *str, int fd);
int					ft_exit(char *str);

int					init_params(int ac, char **av, t_params *params);
int					check_args(char **av);

int					init_philos(t_params *p, t_philo *head);
t_philo				*new_philo(t_params *p, int id);

#endif