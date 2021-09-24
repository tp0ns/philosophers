/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:34:59 by tpons             #+#    #+#             */
/*   Updated: 2021/09/23 19:18:46 by tpons            ###   ########.fr       */
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
	/*number of philosophers*/
	long int		population;
	/*time to die*/
	long int		t_die;
	/*time to eat*/
	long int		t_eat;
	/* time to sleep*/
	long int		t_sleep;
	/*number of times each philosopher must eat*/
	int				t_meat;
	/*Flag up when all philosophers are satiated*/
	int				satiated;
	/*mutex controlling philos can only talk one at a time*/
	pthread_mutex_t	talking;
	/*Indicate time of first meal*/
	long int		start;
	/*Flag up when a philosopher is dead*/
	int				dead;
}					t_params;

typedef	struct		s_philo
{
	/*thread representing the philosopher*/
	pthread_t		philosopher;
	/*id of the philosopher*/
	int				id;
	/*global params, same for all philosophers*/
	t_params		*params;
	/*represent the number of meal the philosopher had*/
	int				meals;
	/*indicates that  (meals > params->t_meat)*/
	int				full;
	/*Hour of last meal*/
	long int		last_meal;
	/*Mutex when philosopher is eating*/
	int				eating;
	/*Mutex representing fork*/
	pthread_mutex_t	fork;
	/*points to the philosopher to his right*/
	struct s_philo	*next;
}					t_philo;

int					ft_atoi(char *str);
void				ft_putstr_fd(char *str, int fd);
long int			present(void);
void				ft_usleep(long int time_ms);

t_params			*init_params(int ac, char **av);
int					check_args(int ac, char **av);

t_philo				*init_philos(t_params *p);
t_philo				*new_philo(t_params *p, int id);

void				philo_talks(t_philo *philo, char *str);
void				philo_eats(t_philo *philo);
void				philo_routine(t_philo *philo);
void				*philo_launch(void *philo);
int					thread(t_philo *philo);

void				are_philos_alive(t_philo *philo);
void				*should_philos_run(void *philo);
void				free_philos(t_philo *head);

int					ft_error(char *str);

#endif