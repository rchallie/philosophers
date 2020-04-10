/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: excalibur <excalibur@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 11:45:12 by excalibur         #+#    #+#             */
/*   Updated: 2020/04/10 12:45:20 by excalibur        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>

# define __SUCCESS 0
# define __SIMULATION_MALLOC 1
# define __INIT_FORKS 2
# define __INIT_PHILOSOPHERS 3
# define __HEADERS_THREADS_MALLOC 4
# define __HEADERS_MALLOC 5

struct s_simulation;

typedef struct			s_philosopher
{
	int					number;
	int					number_meal;
	int					is_thinking;
	int					is_eating;
	int					is_on_eat;
	int					is_sleeping;
	int					take_fork_l;
	int					take_fork_r;
	pthread_t			monitor;
	pthread_t			stomack;
	pthread_t			itsme;
	struct timeval		last_time_eated;
	struct s_simulation	*simulation;
}						t_philosopher;

typedef struct			s_simulation
{
	struct timeval		start_time;
	sem_t				*can_write;
	sem_t				*forks;
	pid_t				*philosophers_pids;
	long unsigned		number_of_philosopher;
	long unsigned		time_to_die;
	long unsigned		time_to_eat;
	long unsigned		time_to_sleep;
	int					each_must_eat;
}						t_simulation;

typedef	struct			s_header
{
	pid_t				*pids;
	long unsigned		number;
	long unsigned		nbr_philosopher;
}						t_header;

long unsigned			get_time_diff(struct timeval a, struct timeval b);
long unsigned			get_timestamp(struct timeval start_time);
void					wait_for(struct timeval start, long unsigned time);

long unsigned			ft_atolu(char *str);
char					*ft_lutoa(long unsigned nbr);
int						ft_strlen(char *str);

void					*routine(void *phi);

void					*monitor_func(void *phi);

int						wait_for_end(t_simulation *simulation);
void					*header_routine(void *raw);

#endif
