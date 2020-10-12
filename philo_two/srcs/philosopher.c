/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:18:48 by excalibur         #+#    #+#             */
/*   Updated: 2020/10/11 20:23:30 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_two.h"

/*
** @brief Philosopher eat. Get forks.
** eat for time_to_eat and leave them.
**
** @param philosopher a pointer to the
** philosopher.
*/

static void		eat(
	t_philosopher *philosopher
)
{
	sem_wait(philosopher->forks);
	print_msg(philosopher, "has taken a fork\n");
	sem_wait(philosopher->forks);
	print_msg(philosopher, "has taken a fork\n");
	if (*philosopher->have_a_death != 1)
	{
		sem_wait(philosopher->eating);
		print_msg(philosopher, "eating\n");
		philosopher->last_time_eated = get_actual_time();
		wait_for(philosopher->time_to_eat);
		sem_post(philosopher->eating);
	}
	sem_post(philosopher->forks);
	sem_post(philosopher->forks);
	philosopher->number_meal++;
}

/*
** @brief the routine of a philosopher.
** He will thinking, eating, sleeping.
** If another philosopher is dead or he
** have ate enought, he will be
** stopped.
**
** @param phi a pointer to the philosopher.
** (it's a void pointer because it's the routine
** called by thread creation function).
** @return NULL.
*/

void			*routine(
	void *phi
)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher*)phi;
	while (42 && *philosopher->have_a_death == 0)
	{
		eat(philosopher);
		if (*philosopher->have_a_death == 1
			|| (philosopher->each_must_eat != -1 && philosopher->number_meal
			>= philosopher->each_must_eat))
		{
			philosopher->is_died = 1;
			break ;
		}
		print_msg(philosopher, "sleeping\n");
		if (*philosopher->have_a_death == 1)
			break ;
		wait_for(philosopher->time_to_sleep);
		print_msg(philosopher, "thinking\n");
	}
	return (NULL);
}
