/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:34:59 by tpons             #+#    #+#             */
/*   Updated: 2021/11/04 15:07:51 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

/*
**    --Parameters structure--
**
** population : number of philosophers.
** t_die : time it takes for a philosopher to die.
** t_eat : time it takes for a philosopher to eat.
** t_sleep : time it takes for a philosopher to sleep.
** t_meat : minimum number of time a philosopher must eat.
** talking : mutex controlling philos can only talk one at a time.
** start : Indicate time of first meal.
** dead : Flag up when a philosopher is dead.
*/

typedef struct s_params
{
	int				population;
	long int		t_die;
	long int		t_eat;
	long int		t_sleep;
	int				t_meat;
	pthread_mutex_t	talking;
	pthread_mutex_t	race_d;
	long int		start;
	int				dead;
}					t_params;

/*
**	--Philosophers linked list--
**
** philosopher : thread representing the philosopher. 
** id : id of the philosopher. 
** params : global params, same for all philosophers. 
** meals : represent the number of meal the philosopher had. 
** full : flag up if (meals > params->t_meat). 
** last_meal : Hour of last meal. 
** eating : Mutex when philosopher is eating. 
** fork : Mutex representing fork. 
** next : points to the philosopher to his right. 
*/

typedef struct s_philo
{
	pthread_t		philosopher;
	pthread_t		alive_check;
	int				id;
	t_params		*params;
	int				meals;
	int				full;
	long int		last_meal;
	pthread_mutex_t	eating;
	pthread_mutex_t	fork;
	pthread_mutex_t	race_f;
	struct s_philo	*next;
}					t_philo;

int					ft_atoi(char *str);
void				ft_putstr_fd(char *str, int fd);
long int			present(void);
void				ft_usleep(long int time_ms);
int					init_philo_mutex(pthread_mutex_t *a, pthread_mutex_t *b,
						pthread_mutex_t *c);

int					check_args(int ac, char **av);
int					from_args_to_params(t_params *params, int ac, char **av);
t_params			*init_params(int ac, char **av);
t_philo				*new_philo(t_params *p, int id);
t_philo				*init_philos(t_params *p);

int					philo_talks(t_philo *philo, char *str);
void				philo_eats(t_philo *philo);
void				*philo_routine(void *philo);
int					thread(t_philo *philo);

void				philo_is_alone(t_philo *philo);
void				*is_philos_alive(void *data);
int					safe_check(pthread_mutex_t mutex, int value);
void				safe_change(pthread_mutex_t mutex, int *value, int def);

void				free_params(t_params *params);
void				free_philos(t_philo *head);
void				free_init_philos(t_philo *head);
int					ft_error(char *str);

#endif