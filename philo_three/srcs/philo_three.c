/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: excalibur <excalibur@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 16:30:33 by excalibur         #+#    #+#             */
/*   Updated: 2020/04/10 12:45:49 by excalibur        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_three.h"

/*
**	@brief Initialise the philosophers for the
**	simulation.
**
** @param sim the pointer to the simulation
** struct.
** @param number_of_philosopher if the number of
** philosopher in the simulation.
** @return a pointer to the philosopher array.
** If an error append during mallocs, a null pointer
** will be returned.
*/

static pid_t			*init_philosophers(
	t_simulation *sim,
	long unsigned number_of_philosopher
)
{
	long unsigned		i;
	t_philosopher		philosopher;
	int					chill_process;
	pid_t				*philo_pid;

	i = 0;
	if (!(philo_pid = malloc(sizeof(pid_t) * number_of_philosopher)))
		return (NULL);
	memset(philo_pid, 0, sizeof(pid_t) * number_of_philosopher);
	while (i < number_of_philosopher)
	{
		philosopher = (t_philosopher){.number = i + 1, .simulation = sim};
		if ((chill_process = fork()) < 0)
			exit(999);
		if (chill_process == 0)
			routine(&philosopher);
		else
			philo_pid[i] = chill_process;
		usleep(100);
		i++;
	}
	return (philo_pid);
}

/*
** @brief Init the simulation and all its data.
**
** @param argc the number pasted in the command
** line.
** @param argv the arguments pasted in the command
** line. (See main for description of each).
** @return a pointer to the simulations datas structure.
*/

static t_simulation		*init_simulation(
	int argc,
	char **argv
)
{
	t_simulation		*simulation;
	struct timeval		start_time;
	sem_t				can_write;

	gettimeofday(&start_time, NULL);
	sem_init(&can_write, 0, 1);
	if (!(simulation = malloc(sizeof(t_simulation))))
		return (NULL);
	memset(simulation, 0, sizeof(t_simulation));
	simulation->start_time = start_time;
	simulation->can_write = sem_open("/write",
				O_CREAT | O_EXCL, 0644, 1);
	simulation->number_of_philosopher = ft_atolu(argv[1]);
	simulation->forks = sem_open("/forks",
				O_CREAT | O_EXCL, 0644, ft_atolu(argv[1]));
	simulation->time_to_die = ft_atolu(argv[2]);
	simulation->time_to_eat = ft_atolu(argv[3]);
	simulation->time_to_sleep = ft_atolu(argv[4]);
	simulation->each_must_eat = -1;
	if (argc == 6)
		simulation->each_must_eat = ft_atolu(argv[5]);
	simulation->philosophers_pids =
		init_philosophers(simulation, ft_atolu(argv[1]));
	return (simulation);
}

/*
** @brief Free simulations datas malloced.
**
** @param sim a pointer to the simulation.
*/

void					free_simulation(
	t_simulation *sim
)
{
	long unsigned i;

	i = 0;
	sem_close(sim->forks);
	sem_close(sim->can_write);
	free(sim);
}

/*
** @brief philo_one of Philosophers project
** from 42School. Basicaly the dining philosopher
** problem, with obligation like use semaphores,
** philosophers can't speak between them, time of
** death, defined sleeping time, and the simulation
** is ended with the death of an philosopher or
** if each philosopher ate enought.
**
** @param argc the number of arguments pasted from
** command line.
** @param argv : 0 the program name. 1 the number of
** philosopher in the simulation. 2 the time to die, if
** a philosopher don't start to eat during this time
** the philosopher die and the simulation is stopped. 3
** the time to eat. 4 the time to sleep. 5 (Optionnal)
** the number of time each philosopher must eat, when all
** the philosopher ate this amount, the simulation is
** stopped. All time are in milliseconds.
** @return __SUCCESS if the simulation ended propely.
** __SIMULATION_MALLOC if the malloc of simulation
** datas return NULL, __INIT_PHILOSOPHERS if the
** philosophers datas had an error (malloc error)
** __INIT_FORKS if the forks datas had an error
** (malloc error or semaphores initialisation).
*/

int						main(
	int argc,
	char **argv
)
{
	t_simulation	*simulation;
	long unsigned	i;
	char			*ended;
	int				rtn;

	i = 0;
	sem_unlink("/forks");
	sem_unlink("/write");
	ended = "Simulation ended\n";
	simulation = init_simulation(argc, argv);
	if ((rtn = wait_for_end(simulation)) != __SUCCESS)
		return (rtn);
	write(1, ended, ft_strlen(ended));
	free_simulation(simulation);
	return (__SUCCESS);
}
