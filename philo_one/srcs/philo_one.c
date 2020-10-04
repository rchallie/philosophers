/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 16:30:33 by excalibur         #+#    #+#             */
/*   Updated: 2020/10/04 03:18:09 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

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

static t_philosopher	*init_philosophers(
	t_simulation *sim,
	long unsigned number_of_philosopher
)
{
	long unsigned		i;
	t_philosopher		*philosophers;

	i = 0;
	if (!(philosophers = malloc(sizeof(t_philosopher) * number_of_philosopher))
		|| !sim->forks)
		return (NULL);
	memset(philosophers, 0, sizeof(t_philosopher) * number_of_philosopher);
	while (i < number_of_philosopher)
	{
		philosophers[i] = (t_philosopher){.number = i + 1, .simulation = sim};
		pthread_create(&philosophers[i].itsme, NULL,
			(void*)routine, (void*)&philosophers[i]);
		usleep(50);
		i++;
	}
	i = 0;
	while (i < number_of_philosopher)
	{
		pthread_create(&philosophers[i].monitor, NULL,
			(void*)monitor_func, (void*)&philosophers[i]);
		i++;
	}
	return (philosophers);
}

/*
** @brief Init the forks for the simulation.
**
** @param number_of_philosopher the number
**	of philosopher in the simulation.
** @return a pointer to the mutex (forks) array.
** If an error append during mallocs or mutexs
** initialisation, a null pointer will be returned.
*/

static pthread_mutex_t	*init_forks(
	long unsigned number_of_philosopher
)
{
	long unsigned		i;
	pthread_mutex_t		*forks;

	i = 0;
	if (!(forks = malloc(sizeof(pthread_mutex_t) * number_of_philosopher)))
		return (NULL);
	memset(forks, 0, sizeof(pthread_mutex_t) * number_of_philosopher);
	while (i < number_of_philosopher)
		if (pthread_mutex_init(&forks[i++], NULL))
			return (NULL);
	return (forks);
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

# include <stdio.h>

static t_simulation		*init_simulation(
	int argc,
	char **argv
)
{
	t_simulation		*simulation;
	pthread_mutex_t		can_write;

	pthread_mutex_init(&can_write, NULL);
	if (!(simulation = malloc(sizeof(t_simulation))))
		return (NULL);
	memset(simulation, 0, sizeof(t_simulation));
	simulation->have_a_death = 0;
	simulation->can_write = can_write;
	simulation->forks = init_forks(ft_atolu(argv[1]));
	simulation->number_of_philosopher = ft_atolu(argv[1]);
	simulation->time_to_die = ft_atolu(argv[2]);
	simulation->time_to_eat = ft_atolu(argv[3]);
	simulation->time_to_sleep = ft_atolu(argv[4]);
	simulation->each_must_eat = -1;
	if (argc == 6)
		simulation->each_must_eat = ft_atolu(argv[5]);
	simulation->start_time = get_actual_time();
	simulation->philosophers = init_philosophers(simulation, ft_atolu(argv[1]));
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
	while (i < sim->number_of_philosopher)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	free(sim->philosophers);
	free(sim->forks);
	free(sim);
}

/*
** @brief philo_one of Philosophers project
** from 42School. Basicaly the dining philosopher
** problem, with obligation like use mutex,
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
** (malloc error or mutex initialisation).
*/

int						main(
	int argc,
	char **argv
)
{
	t_simulation	*simulation;
	long unsigned	i;
	char			*ended;

	i = 0;
	ended = "Simulation ended\n";
	simulation = init_simulation(argc, argv);
	if (!simulation->philosophers)
		return (__INIT_PHILOSOPHERS);
	if (!simulation->forks)
		return (__INIT_FORKS);
	while (i < simulation->number_of_philosopher)
		pthread_join(simulation->philosophers[i++].monitor, NULL);
	i = 0;
	while (i < simulation->number_of_philosopher)
		pthread_join(simulation->philosophers[i++].itsme, NULL);
	pthread_mutex_destroy(&simulation->can_write);
	// write(1, ended, ft_strlen(ended));
	free_simulation(simulation);
	return (__SUCCESS);
}
