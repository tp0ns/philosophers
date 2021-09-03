/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:34:59 by tpons             #+#    #+#             */
/*   Updated: 2021/09/03 16:56:38 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

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
	pthread_mutex_t	*talking;
	/*mutex controlling philos can only talk one at a time*/
}					t_params;

typedef	struct		s_philo
{
	pthread_t		*philosopher;
	/*thread representing the philosopher*/
	int				id;
	/*id of the philosopher*/
	t_params		*params;
	/*global params, same for all philosophers*/
	pthread_mutex_t	*fork;
	/*fork tab representing every fork*/
	struct s_philo	*next;
	/*points to the philosopher to his right*/
}					t_philo;

int					ft_atoi(char *str);
void				ft_putstr_fd(char *str, int fd);

int					init_params(int ac, char **av, t_params *params);
int					check_args(char **av);

int					init_philos(t_params *p, t_philo *head);
t_philo				*new_philo(t_params *p, int id);

void				print_routine(t_philo *philo, char *str);
void				*philo_routine(t_philo *philo);
int					thread(t_philo *philo);

void				free_philos(t_philo *head);
int					ft_exit(char *str);

#endif