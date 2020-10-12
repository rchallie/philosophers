/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 21:26:23 by rchallie          #+#    #+#             */
/*   Updated: 2020/10/11 23:20:18 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_two.h"

static void		init_phi_set_infos(
	t_philosopher *philosophers,
	t_simulation *sim,
	int i
)
{
	philosophers[i] = (t_philosopher){.number = i + 1, .simulation = sim,
	.last_time_eated = get_actual_time(), .forks = sim->forks,
	.each_must_eat = sim->each_must_eat, .time_to_die = sim->time_to_die,
	.time_to_eat = sim->time_to_eat, .time_to_sleep = sim->time_to_sleep,
	.have_a_death = sim->have_a_death, .start_time = sim->start_time,
	.can_write = sim->can_write};
}

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

t_philosopher	*init_philosophers(
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
	i = 0;
	while (i < number_of_philosopher)
	{
		init_phi_set_infos(philosophers, sim, i);
		if (init_sems(philosophers, i))
			return (NULL);
		i++;
	}
	if (create_philosophers_threads(philosophers, number_of_philosopher))
		return (NULL);
	i = -1;
	while (++i < number_of_philosopher)
	{
		pthread_create(&philosophers[i].monitor, NULL,
			(void*)monitor_func, (void*)&philosophers[i]);
	}
	return (philosophers);
}

/*
** @brief Init the forks for the simulation.
**
** @param number_of_philosopher the number
**	of philosopher in the simulation.
** @return a pointer to the sempahores (forks) array.
** If an error append during mallocs or sempahores
** initialisation, a null pointer will be returned.
*/

static sem_t	*init_forks(
	long unsigned number_of_philosopher
)
{
	sem_t			*forks;

	if ((forks = sem_open("/forks",
		O_CREAT, S_IRWXU, number_of_philosopher)) == SEM_FAILED)
	{
		sem_unlink("/forks");
		return (sem_open("/forks",
		O_CREAT, S_IRWXU, number_of_philosopher));
	}
	return (forks);
}

static int		init_sim_allocation(
	sem_t **can_write,
	t_simulation **simulation,
	int **have_a_death
)
{
	if ((*can_write = sem_open("/canwrite", O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
	{
		sem_unlink("/canwrite");
		if ((*can_write =
			sem_open("/canwrite", O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
			return (1);
	}
	if (!(*simulation = malloc(sizeof(t_simulation))))
		return (1);
	memset(*simulation, 0, sizeof(t_simulation));
	if (!(*have_a_death = malloc(sizeof(int))))
		return (1);
	**have_a_death = 0;
	return (0);
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

t_simulation	*init_simulation(
	int argc,
	char **argv
)
{
	t_simulation		*simulation;
	sem_t				*can_write;
	int					*have_a_death;

	simulation = NULL;
	can_write = NULL;
	have_a_death = NULL;
	if (init_sim_allocation(&can_write, &simulation, &have_a_death) == 1)
		return (NULL);
	simulation->have_a_death = have_a_death;
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
	if ((simulation->philosophers =
		init_philosophers(simulation, ft_atolu(argv[1]))) == NULL)
		return (NULL);
	return (simulation);
}
