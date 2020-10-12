/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 16:30:33 by excalibur         #+#    #+#             */
/*   Updated: 2020/10/12 16:19:22 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_three.h"

int			wait_for_end(
	t_simulation *simulation
)
{
	int				status;
	int				status_value;
	unsigned long	i;

	i = 0;
	while (i < simulation->number_of_philosopher)
	{
		waitpid(-1, &status, 0);
		if ((WIFEXITED(status) || WIFSIGNALED(status)))
		{
			if ((status_value = WEXITSTATUS(status)) == 0)
			{
				while (i < simulation->number_of_philosopher)
				{
					if (i != simulation->number_of_philosopher)
						kill(simulation->philos_pid[i], SIGTERM);
					i++;
				}
				break ;
			}
			else if (status_value == 1)
				i++;
		}
	}
	return (__SUCCESS);
}

pid_t		*create_philosophers_fork(
	t_philosopher *phi,
	int number_of_philosopher
)
{
	int		i;
	pid_t	*philos_pid;

	i = -1;
	if (!(philos_pid = malloc(sizeof(pid_t) * number_of_philosopher)))
		return (NULL);
	memset(philos_pid, 0, sizeof(pid_t) * number_of_philosopher);
	while (++i < (int)number_of_philosopher)
	{
		if (!(i % 2))
			fork_philos(phi, philos_pid, i);
		usleep(70);
	}
	i = -1;
	while (++i < (int)number_of_philosopher)
	{
		if (i % 2)
			fork_philos(phi, philos_pid, i);
		usleep(70);
	}
	return (philos_pid);
}

/*
** @brief Free simulations datas malloced.
**
** @param sim a pointer to the simulation.
*/

void		free_simulation(
	t_simulation *sim
)
{
	long unsigned i;

	i = 0;
	while (i < sim->number_of_philosopher)
	{
		sem_close(sim->philosophers[i].eating);
		(sim->philosophers[i].eating_name)
			? free(sim->philosophers[i].eating_name) : 0;
		i++;
	}
	sem_close(sim->can_write);
	sem_close(sim->forks);
	sem_unlink("/forks");
	sem_unlink("/canwrite");
	(sim->have_a_death) ? free(sim->have_a_death) : 0;
	(sim->philosophers) ? free(sim->philosophers) : 0;
	(sim->philos_pid) ? free(sim->philos_pid) : 0;
	(sim) ? free(sim) : 0;
}

static int	check_arguments(int argc, char **argv)
{
	int i;
	int j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i] && argv[i][j])
		{
			if (!(argv[i][j] >= 48 && argv[i][j] <= 57))
				return (__COMMAND_ARGUMENTS);
			j++;
		}
		i++;
	}
	return (__SUCCESS);
}

/*
** @brief philo_three of Philosophers project
** from 42School. Basicaly the dining philosopher
** problem, with obligation like use semaphore,
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
** (malloc error or semaphore initialisation).
*/

int			main(
	int argc,
	char **argv
)
{
	t_simulation	*simulation;
	long unsigned	i;
	int				rtn;

	i = 0;
	rtn = 0;
	if (argc < 5 || argc > 6)
		return (error_command_argument());
	else if (check_arguments(argc, argv) == __COMMAND_ARGUMENTS)
		return (error_bad_argument());
	sem_unlink("/forks");
	sem_unlink("/canwrite");
	simulation = init_simulation(argc, argv);
	if (!simulation->philosophers)
		return (error_init_philosophers());
	if (!simulation->forks)
		return (error_init_forks());
	while (i < simulation->number_of_philosopher)
		pthread_join(simulation->philosophers[i++].monitor, NULL);
	if ((rtn = wait_for_end(simulation)) != __SUCCESS)
		return (rtn);
	free_simulation(simulation);
	return (__SUCCESS);
}
