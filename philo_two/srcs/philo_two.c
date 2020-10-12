/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 16:30:33 by excalibur         #+#    #+#             */
/*   Updated: 2020/10/11 23:07:53 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_two.h"

int			create_philosophers_threads(
	t_philosopher *philosophers,
	int number_of_philosopher
)
{
	int i;

	i = -1;
	while (++i < number_of_philosopher)
	{
		if (!(i % 2))
			if (pthread_create(&philosophers[i].itsme, NULL,
				(void*)routine, (void*)&philosophers[i]))
				return (1);
		usleep(70);
	}
	i = -1;
	while (++i < number_of_philosopher)
	{
		if (i % 2)
			if (pthread_create(&philosophers[i].itsme, NULL,
				(void*)routine, (void*)&philosophers[i]))
				return (1);
		usleep(70);
	}
	return (0);
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
** @brief philo_two of Philosophers project
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

	i = 0;
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
	i = 0;
	while (i < simulation->number_of_philosopher)
		pthread_join(simulation->philosophers[i++].itsme, NULL);
	free_simulation(simulation);
	return (__SUCCESS);
}
