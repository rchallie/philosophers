/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 11:45:12 by excalibur         #+#    #+#             */
/*   Updated: 2020/10/12 16:19:11 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <semaphore.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>

# define __SUCCESS 0
# define __COMMAND_ARGUMENTS 1
# define __SIMULATION_MALLOC 2
# define __INIT_FORKS 3
# define __INIT_PHILOSOPHERS 4
# define __HEADERS_THREADS_MALLOC 5
# define __HEADERS_MALLOC 6

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
	sem_t				*forks;
	sem_t				*can_write;
	sem_t				*eating;
	char				*eating_name;
}						t_philosopher;

typedef struct			s_simulation
{
	sem_t				*can_write;
	sem_t				*forks;
	pid_t				*philos_pid;
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
pid_t					*create_philosophers_fork(t_philosopher *phi,
						int number_of_philosopher);

/*
** --- init ---
*/
t_simulation			*init_simulation(int argc, char **argv);
char					*get_sem_name(int i);
int						init_sems(t_philosopher *philosophers, int i);
void					fork_philos(t_philosopher *phi, pid_t *philos_pid,
						int i);

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
