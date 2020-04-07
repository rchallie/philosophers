/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: excalibur <excalibur@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 11:45:12 by excalibur         #+#    #+#             */
/*   Updated: 2020/04/07 23:26:43 by excalibur        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

#ifndef __SUCCESS
	# define __SUCCESS 0
#endif

#ifndef __SIMULATION_MALLOC
	# define __SIMULATION_MALLOC 1
#endif

#ifndef __INIT_FORKS
	# define __INIT_FORKS 2
#endif

#ifndef __INIT_PHILOSOPHERS
	# define __INIT_PHILOSOPHERS 3
#endif

typedef struct          s_simulation t_simulation;

typedef struct          s_philosopher
{
	int                 number;
	int                 number_meal;
	int                 is_thinking;
	int                 is_eating;
	int                 is_on_eat;
	int                 is_sleeping;
	int                 take_fork_l;
	int                 take_fork_r;
	pthread_t           monitor;
	pthread_t           stomack;
	pthread_t           itsme;
	struct timeval      last_time_eated;
	t_simulation        *simulation;
}                       t_philosopher;

typedef struct          s_simulation
{
	struct timeval      start_time;
	pthread_mutex_t     can_write;
	int                 have_a_death;
	pthread_mutex_t     *forks;
	t_philosopher       *philosophers;
	long unsigned       number_of_philosopher;
	long unsigned       time_to_die;
	long unsigned       time_to_eat;
	long unsigned       time_to_sleep;
	int                 each_must_eat;
}                       t_simulation;

long unsigned           get_time_diff(struct timeval a, struct timeval b);
long unsigned           get_timestamp(struct timeval start_time);
void            		wait_for(struct timeval start, long unsigned time);

long unsigned           ft_atolu(char *str);
char*                   ft_lutoa(long unsigned nbr);
int                     ft_strlen(char *str);

void                    *routine(void *phi);

void*                   monitor_func(void *phi);

# endif