/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 11:45:12 by excalibur         #+#    #+#             */
/*   Updated: 2020/10/11 23:10:27 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

# define __SUCCESS 0
# define __COMMAND_ARGUMENTS 1
# define __SIMULATION_MALLOC 2
# define __INIT_FORKS 3
# define __INIT_PHILOSOPHERS 4

struct s_simulation;

typedef struct			s_philosopher
{
	int					number;
	int					number_meal;
	int					is_died;
	int					each_must_eat;
	int					*have_a_death;
	long unsigned		time_to_die;
	long unsigned		time_to_eat;
	long unsigned		time_to_sleep;
	long unsigned		start_time;
	long unsigned		last_time_eated;
	struct s_simulation	*simulation;
	pthread_t			monitor;
	pthread_t			itsme;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*can_write;
	pthread_mutex_t		eating;
}						t_philosopher;

typedef struct			s_simulation
{
	pthread_mutex_t		*can_write;
	pthread_mutex_t		*forks;
	int					*have_a_death;
	int					each_must_eat;
	t_philosopher		*philosophers;
	long unsigned		start_time;
	long unsigned		number_of_philosopher;
	long unsigned		time_to_die;
	long unsigned		time_to_eat;
	long unsigned		time_to_sleep;
}						t_simulation;

/*
** --- philo_one ---
*/
int						create_philosophers_threads(
						t_philosopher *philosophers, int number_of_philosopher);

/*
** --- init ---
*/
t_simulation			*init_simulation(int argc, char **argv);

/*
** --- time ---
*/
long unsigned			get_time_diff(long unsigned a, long unsigned b);
long unsigned			get_timestamp(long unsigned start_time);
long unsigned			get_actual_time();
void					wait_for(long unsigned time);

/*
** --- utils ---
*/
long unsigned			ft_atolu(char *str);
char					*ft_lutoa(long unsigned nbr);
int						ft_strlen(const char *str);
void					print_msg(t_philosopher *phi, char *message);

/*
** --- philosopher ---
*/
void					*routine(void *phi);

/*
** --- monitor ---
*/
void					*monitor_func(void *phi);

/*
** --- error ---
*/
int						error_command_argument(void);
int						error_bad_argument(void);
int						error_init_philosophers(void);
int						error_init_forks(void);

#endif
