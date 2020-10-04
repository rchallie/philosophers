/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 11:45:12 by excalibur         #+#    #+#             */
/*   Updated: 2020/10/04 03:08:30 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

#include <stdio.h>

# define __SUCCESS 0
# define __SIMULATION_MALLOC 1
# define __INIT_FORKS 2
# define __INIT_PHILOSOPHERS 3

struct s_simulation;

typedef struct			s_philosopher
{
	int					number;
	int					number_meal;
	int 				is_died;
	pthread_t			monitor;
	pthread_t			itsme;
	long unsigned		last_time_eated;
	struct s_simulation	*simulation;
}						t_philosopher;

typedef struct			s_simulation
{
	long unsigned		start_time;
	pthread_mutex_t		can_write;
	int					have_a_death;
	pthread_mutex_t		*forks;
	t_philosopher		*philosophers;
	long unsigned		number_of_philosopher;
	long unsigned		time_to_die;
	long unsigned		time_to_eat;
	long unsigned		time_to_sleep;
	int					each_must_eat;
}						t_simulation;

long unsigned	get_time_diff(
	long unsigned a,
	long unsigned b
);
long unsigned	get_timestamp(
	long unsigned
);
long unsigned get_actual_time();
void					wait_for(long unsigned time);

long unsigned			ft_atolu(char *str);
char					*ft_lutoa(long unsigned nbr);
int						ft_strlen(char *str);

void					*routine(void *phi);

void					*monitor_func(void *phi);

 void		print_msg(
	t_philosopher *phi,
	char *message
);

#endif
