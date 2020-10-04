/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:18:48 by excalibur         #+#    #+#             */
/*   Updated: 2020/10/04 03:06:44 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"



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
	int right = (philosopher->number)
		% philosopher->simulation->number_of_philosopher;
	int left = philosopher->number - 1;

	pthread_mutex_lock(
		&philosopher->simulation->forks[left]);
	print_msg(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->simulation->forks[right]);
	print_msg(philosopher, "has taken a fork");
	philosopher->last_time_eated = get_actual_time();
	print_msg(philosopher, "eating");
	if (philosopher->simulation->have_a_death != 1)
		wait_for(philosopher->simulation->time_to_eat);
	pthread_mutex_unlock(
		&philosopher->simulation->forks[left]);
	pthread_mutex_unlock(
		&philosopher->simulation->forks[right]);
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
	philosopher->last_time_eated = get_actual_time();
	while (42 && philosopher->simulation->have_a_death == 0)
	{
		eat(philosopher);
		print_msg(philosopher, "sleeping");
		if (philosopher->simulation->have_a_death == 1)
			break;
		usleep(philosopher->simulation->time_to_sleep * 1000);
		print_msg(philosopher, "thinking");
	}
	return (NULL);
}
